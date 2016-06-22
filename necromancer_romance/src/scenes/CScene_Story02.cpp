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
	m_Text->Initialize(L"�����ٸ����");

	m_fadeTimer = new CTime();
	m_fadeTimer->SetTimer(1.0f, false);

	CScriptManager::getSkillManager()->AddScript(0, L"�� �ڽ� ������� ���ݾ�?\n��¥ �� �� �������ߴٴϱ�!");
	CScriptManager::getSkillManager()->AddScript(1, L"Ȯ���� ���̼� ��� ���ھ�.\n�뺴�� ����ϴ� ���� ���ڴ°�?");
	CScriptManager::getSkillManager()->AddScript(2, L"���� �������ݾ�!\n������� �󸶵��� ������ ������ڰ�.");
	CScriptManager::getSkillManager()->AddScript(3, L"�ٽ� ������ ���ư� ���ڸ� �����鼭,\n���߿� ��� ������ �뺴�� ����Ѵ�\n�̰��� �������� �ൿ��ħ�� �ǰھ�.");
	CScriptManager::getSkillManager()->AddScript(4, L"�� ���ڸ� ���δٰ� �ؼ� �̹� ���� ���ڸ� �츱 �� �ְھ�?\n��Ȱ������ ����� �� �������!");
	CScriptManager::getSkillManager()->AddScript(5, L"��ũ�θǼ��� ������\n���󿡼� ���� ���� �ΰ��� ��ȥ�� �ʿ��ϴٴ���.");
	CScriptManager::getSkillManager()->AddScript(6, L"����� ��ȥ�� �ִٸ� Ʋ������\n��ũ�θǼ��� ������ �׳ฦ...");
	CScriptManager::getSkillManager()->AddScript(7, L"�׸�!!! ���� ����, �ϴ� ���ڰ�.\n���γ� ���� �� ���ֺ��� �� ����ְ����ϱ�.");

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
			case 0:	/*0���� �ʱ�ȭ���� ����*/							break;
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