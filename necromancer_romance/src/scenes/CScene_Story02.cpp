// ..\framework
#include "..\framework\CInput.h"
#include "..\framework\common.h"
#include "..\framework\CFont.h"
#include "..\framework\CTime.h"
#include "..\framework\CSound.h"

// ..\managers
#include "..\managers\CNero.h"
#include "..\managers\CCardManager.h"
#include "..\managers\CObjectManager.h"
#include "..\managers\CSceneManager.h"
#include "..\managers\CScriptManager.h"

// ..\objects
#include "..\objects\CCard.h"
#include "..\objects\CObject_Background.h"
#include "..\objects\CObject_TalkWindow.h"

// ..\scenes
#include "CScene_Story02.h"

CScene_Story02::CScene_Story02()
{
	m_background = NULL;

	m_Text = NULL;
	m_bgm = NULL;

	m_fadeTimer = NULL;
	m_bFadeIn = true;

	m_nextSceneNum = -1;
	m_scriptNum = 0;
}

CScene_Story02::CScene_Story02(const CScene_Story02& scene)
{
}

CScene_Story02::~CScene_Story02()
{
}

void CScene_Story02::Initialize()
{
	m_background = new CObject_Background();
	m_background->Initalize(0, 0, 100, L"res/background/town_back.png");
	CObjectManager::getObjectManager()->AddObject(static_cast<CObject*>(m_background));

	m_bgm = new CSound();
	m_bgm->Initialize("res/sound/BGM/Town.mp3");
	m_bgm->Loop(true);

	m_Text = new CFont();
	m_Text->Initialize(L"나눔바른고딕");

	m_fadeTimer = new CTime();
	m_fadeTimer->SetTimer(1.0f, false);

	CScriptManager::getSkillManager()->AddScript(0, L"그 자식 기똥차게 세잖아?\n진짜 두 번 죽을뻔했다니까!");
	CScriptManager::getSkillManager()->AddScript(1, L"확실히 둘이선 어림도 없겠어.\n용병을 고용하는 편이 낫겠는걸?");
	CScriptManager::getSkillManager()->AddScript(2, L"좋은 생각이잖아!\n목숨따윈 얼마든지 돈으로 사버리자고.");
	CScriptManager::getSkillManager()->AddScript(3, L"다시 숲으로 돌아가 남자를 쫓으면서,\n도중에 얻는 돈으로 용병을 고용한다\n이것이 앞으로의 행동방침이 되겠어.");
	CScriptManager::getSkillManager()->AddScript(4, L"그 남자를 죽인다고 해서 이미 죽은 여자를 살릴 수 있겠어?\n부활마법은 사라진 지 오래라고!");
	CScriptManager::getSkillManager()->AddScript(5, L"네크로맨서의 고서에는\n세상에서 가장 강한 인간의 영혼이 필요하다더군.");
	CScriptManager::getSkillManager()->AddScript(6, L"농밀한 영혼만 있다면 틀림없이\n네크로맨서의 마법이 그녀를...");
	CScriptManager::getSkillManager()->AddScript(7, L"그만!!! 좋아 좋아, 일단 가자고.\n곰팡내 나는 네 순애보는 못 들어주겠으니까.");

	m_talkWindow = new CObject_TalkWindow();
	m_talkWindow->Initalize();
	m_talkWindow->Reset(0, CARD::JOHN);

	m_scriptNum = 0;
}

void CScene_Story02::Shutdown()
{
	if(m_talkWindow != NULL)
	{
		m_talkWindow->Shutdown();
		SAFE_DELETE(m_talkWindow);
	}
	if(m_Text != NULL)
	{
		m_Text->Shutdown();
		SAFE_DELETE(m_Text);
	}
	if(m_fadeTimer != NULL)
	{
		m_fadeTimer->StopTimer();
		SAFE_DELETE(m_fadeTimer);
	}
	if(m_bgm != NULL)
	{
		m_bgm->Release();
		SAFE_DELETE(m_bgm);
	}

	m_bFadeIn = true;

	m_nextSceneNum = -1;
	CNero::getNero()->OffStoryProgress(STORY::STORY02);
	CNero::getNero()->SetStoryProgress(STORY::STORY03);
	CScriptManager::getSkillManager()->ClearMap();
	CObjectManager::getObjectManager()->RemoveAllObjects();
}

void CScene_Story02::Update(CInput* input)
{
	m_input = input;
	CObjectManager::getObjectManager()->UpdateAllObjects(input);

	input->GetMousePoint(m_mouse.posX, m_mouse.posY);


	if(input->IsLButtonUp()) 
	{
		m_scriptNum++;

		if(m_scriptNum < 8 && m_scriptNum != -1)
		{
			switch(m_scriptNum)
			{
			case 0:	/*0번은 초기화에서 설정*/							break;
			case 1:	m_talkWindow->Reset(m_scriptNum, CARD::NERO);		break;
			case 2:	m_talkWindow->Reset(m_scriptNum, CARD::JOHN);		break;
			case 3: m_talkWindow->Reset(m_scriptNum, CARD::NERO);		break;
			case 4:	m_talkWindow->Reset(m_scriptNum, CARD::JOHN);		break;
			case 5: m_talkWindow->Reset(m_scriptNum, CARD::NERO);		break;
			case 6: m_talkWindow->Reset(m_scriptNum, CARD::NERO);		break;
			case 7: m_talkWindow->Reset(m_scriptNum, CARD::JOHN);		break;
			default:													break;
			}
	
		}
	}

	if(m_scriptNum >= 8 && m_scriptNum != -1)
	{
		m_scriptNum = -1;
		m_fadeTimer->SetTimer(0.5f, false);
		m_bFadeIn = false;
		m_nextSceneNum = SCENE::TOWN;
	}


	
	if(m_fadeTimer->GetTimer() && !m_bFadeIn) {
		CSceneManager::getSceneManager()->SetScene(m_nextSceneNum);
	}

	m_bgm->Play();


	if(input->IsKeyDown(VK_ESCAPE))
	{
		if(m_fadeTimer->GetTimer())
		{
			m_fadeTimer->SetTimer(0.5f, false);
			m_bFadeIn = false;
			m_nextSceneNum = SCENE::TOWN;
		}
	}

}

void CScene_Story02::Render()
{
	float opacity = 0.0f;
	if(m_bFadeIn) {
		opacity = 1.0f - (m_fadeTimer->RemainTime()/m_fadeTimer->GetSetTime());
	}
	else {
		opacity = (m_fadeTimer->RemainTime()/m_fadeTimer->GetSetTime());
	}

	if(opacity == 1.0f) {
		CObjectManager::getObjectManager()->RenderAllObjects();
		m_bgm->Volume(1.0f);

		m_talkWindow->Update(m_input);
		m_talkWindow->Render();
	}
	else {
		CObjectManager::getObjectManager()->RenderAllObjects(opacity);
		m_bgm->Volume(opacity);
	}
}