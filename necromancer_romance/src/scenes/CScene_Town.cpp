// ..\framework
#include "..\framework\CInput.h"
#include "..\framework\common.h"
#include "..\framework\CFont.h"
#include "..\framework\CTime.h"
#include "..\framework\CSound.h"

// ..\managers
#include "..\managers\CNero.h"
#include "..\managers\CObjectManager.h"
#include "..\managers\CSceneManager.h"
#include "..\managers\CCardManager.h"
#include "..\managers\CScriptManager.h"

// ..\objects
#include "..\objects\CCard.h"
#include "..\objects\CObject_Background.h"
#include "..\objects\CObject_Scout.h"
#include "..\objects\CObject_MemberChange.h"
#include "..\objects\CObject_ChangeButton.h"
#include "..\objects\CObject_FieldButton.h"
#include "..\objects\CObject_InnButton.h"
#include "..\objects\CObject_TalkWindow.h"

// ..\scenes
#include "CScene_Town.h"

CScene_Town::CScene_Town()
{
	m_background = NULL;

	m_Text = NULL;
	m_bgm = NULL;
	m_sound_Move = NULL;
	m_fadeTimer = NULL;
	m_bFadeIn = true;

	m_scriptNum = 0;

	m_nextSceneNum = 0;
	m_bTalkOn = false;
	m_bScriptReset = true;
}

CScene_Town::CScene_Town(const CScene_Town& scene)
{
}

CScene_Town::~CScene_Town()
{
}

void CScene_Town::Initialize()
{
	m_background = new CObject_Background();
	m_background->Initalize(0, 0, 100, L"res/background/town_back.png");
	CObjectManager::getObjectManager()->AddObject(static_cast<CObject*>(m_background));

	m_fieldButton = new CObject_FieldButton();
	m_fieldButton->Initalize(0, 0, 15);
	//CObjectManager::getObjectManager()->AddObject(static_cast<CObject*>(m_fieldButton));
	
	m_innButton = new CObject_InnButton();
	m_innButton->Initalize(0, 0, 15);
	//CObjectManager::getObjectManager()->AddObject(static_cast<CObject*>(m_innButton));


	m_bgm = new CSound();
	m_bgm->Initialize("res/sound/BGM/Town.mp3");
	m_bgm->Loop(true);

	m_sound_Move = new CSound();
	m_sound_Move->Initialize("res/sound/se/move.wav");
	m_sound_Move->Loop(false);

	m_Text = new CFont();
	m_Text->Initialize(L"나눔바른고딕");

	m_fadeTimer = new CTime();
	m_fadeTimer->SetTimer(1.0f, false);

	CScriptManager::getSkillManager()->AddScript(0, L"하, 이것 참 편리하다니까!\n돈으로 사람 목숨을 살 수 있다니.\n어쩌다 이 지경까지 돼버린 걸까?");
	CScriptManager::getSkillManager()->AddScript(1, L"먼 옛날, 신과 인간 사이에 일어난 전쟁을 알고 있어?\n나도 그 때 맞서 싸웠지만 역부족이었지.\n결과적으로 인구의 2/3이 죽게 돼. 그야말로 인류의 위기라고나 할까.");
	CScriptManager::getSkillManager()->AddScript(2, L"존속의 위기를 느낀 인류는, 집단최면이라도 걸린 것처럼\n수 많은 자식을 낳았어. 인구는 회복하지만\n되려 한참 초괴해버렸어.");
	CScriptManager::getSkillManager()->AddScript(3, L"그 여파로 생명이 경시되고, 중심 경제는 무너지고...\n배금주의가 만영하고... 돈으로 목숨까지 바치는 용병은\n이렇게 탄생한거야.");
	CScriptManager::getSkillManager()->AddScript(4, L"뭐야, 역사적인 대학살이라면 나도 잘 알고 있다고.\n... 혹시 사람시절의 나도 그 때 죽어버린 걸까?");
	CScriptManager::getSkillManager()->AddScript(5, L"난들 아냐");

	CScriptManager::getSkillManager()->AddScript(10, L"자, 준비는 끝났다.\n부활의 의식을 시작하지.");
	CScriptManager::getSkillManager()->AddScript(11, L"아, 뭐. 열심히 해보라고.");
	CScriptManager::getSkillManager()->AddScript(12, L"......");
	CScriptManager::getSkillManager()->AddScript(13, L"............");
	CScriptManager::getSkillManager()->AddScript(14, L"하하하......");
	CScriptManager::getSkillManager()->AddScript(15, L"실패...라고? 아냐, 거행은 완벽했어...");
	CScriptManager::getSkillManager()->AddScript(16, L"이게 뭐야... 안 되잖아?");
	CScriptManager::getSkillManager()->AddScript(17, L"하하하하하하!!! 멋져, 불발했잖아! 터졌다고!\n이제 더는 없는 영혼이 날아가버렸다고!");
	CScriptManager::getSkillManager()->AddScript(18, L"도대체... 어찌된...");
	CScriptManager::getSkillManager()->AddScript(19, L"이봐 이봐 네로!!! 쇼아를 죽이고 나서\n'가장 강한' 인간은 네가 되어 버린 것 아냐??");
	CScriptManager::getSkillManager()->AddScript(20, L"지금 이 상황이 대체 뭐겠어!\n책이 맞는다면 네가 자살하는 수 밖에!!");
	CScriptManager::getSkillManager()->AddScript(21, L"애초부터 말이 안됐던 거야!\n그 책에 적힌 건 앞뒤가 맞지 않는\n허무맹랑한 소리라고!");
	CScriptManager::getSkillManager()->AddScript(22, L"그럼 난 지금껏 뭘 위해...");
	CScriptManager::getSkillManager()->AddScript(23, L"그래도 그녀의 복수는 갚았잖아?\n그걸론 만족 못 하는 거야?");
	CScriptManager::getSkillManager()->AddScript(24, L"큭... 방법은 더 있을 거다.\n지금부터 다시 찾아보겠어.");
	CScriptManager::getSkillManager()->AddScript(25, L"네로, 좀 더 근본적인 해결책이 있다곤 생각 안 해?");
	CScriptManager::getSkillManager()->AddScript(26, L"신을 죽여라.");
	CScriptManager::getSkillManager()->AddScript(27, L"부활마법을 금지시키고 있는 건 신.\n신을 죽이면 제약이 풀린다.\n넌 원래 부활마법을 사용할 수 있지. 안 그래?");
	CScriptManager::getSkillManager()->AddScript(28, L"이젠 될 대로 되라지...");
	CScriptManager::getSkillManager()->AddScript(29, L"바로 그거야! 아주 좋은 자세라고.");
	CScriptManager::getSkillManager()->AddScript(30, L"하지만 전쟁 이후 신은 한 번도 이 땅에 내려오지 않았어.\n어떻게 찾지?");
	CScriptManager::getSkillManager()->AddScript(31, L"있잖아, 내가 왠지 모르게 걔가 있을만한 곳을 알 것 같거든?\n특별히 안내해준다 이거야.");

	m_talkWindow = new CObject_TalkWindow();
	m_talkWindow->Initalize();

	m_scriptNum = 0;
	m_bTalkOn = false;
	m_bScriptReset = true;
}

void CScene_Town::Shutdown()
{
	if(m_fieldButton != NULL)
	{
		m_fieldButton->Shutdown();
		SAFE_DELETE(m_fieldButton);
	}
	if(m_innButton != NULL)
	{
		m_innButton->Shutdown();
		SAFE_DELETE(m_innButton);
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
	if(m_sound_Move != NULL)
	{
		m_sound_Move->Release();
		SAFE_DELETE(m_sound_Move);
	}

	m_bFadeIn = true;

	m_nextSceneNum = -1;
	CScriptManager::getSkillManager()->ClearMap();
	CObjectManager::getObjectManager()->RemoveAllObjects();
}

void CScene_Town::Update(CInput* input)
{
	m_input = input;
	CObjectManager::getObjectManager()->UpdateAllObjects(input);

	if(!CNero::getNero()->GetStoryProgress(STORY::STORY05))
	{
		m_innButton->Update(input);
		m_fieldButton->Update(input);
	}

	input->GetMousePoint(m_mouse.posX, m_mouse.posY);

	
	if(CNero::getNero()->GetStoryProgress(STORY::STORY05))
	{
		int NumberOfLines = 6;
		if(m_scriptNum < NumberOfLines && m_scriptNum >= 0)
		{
			m_bTalkOn = true;
			if(m_bScriptReset)
			{
				switch(m_scriptNum)
				{
				case 0:	m_talkWindow->Reset(m_scriptNum, CARD::JOHN);		break;
				case 1:	m_talkWindow->Reset(m_scriptNum, CARD::NERO);		break;
				case 2:	m_talkWindow->Reset(m_scriptNum, CARD::NERO);		break;
				case 3: m_talkWindow->Reset(m_scriptNum, CARD::NERO);		break;
				case 4:	m_talkWindow->Reset(m_scriptNum, CARD::JOHN);		break;
				case 5: m_talkWindow->Reset(m_scriptNum, CARD::NERO);		break;
				default:													break;
				}
				m_bScriptReset = false;
			}
		}

		if(input->IsLButtonUp()) {
			m_scriptNum++;
			m_bScriptReset = true;
		}
		if(m_scriptNum >= NumberOfLines)
		{
			CNero::getNero()->OffStoryProgress(STORY::STORY05);
			m_scriptNum = 0;
			m_bTalkOn = false;
		}
	}

	if(CNero::getNero()->GetStoryProgress(STORY::STORY13))
	{
		int NumberOfLines = 22;
		if(m_scriptNum < NumberOfLines && m_scriptNum >= 0)
		{
			m_bTalkOn = true;
			if(m_bScriptReset)
			{
				switch(m_scriptNum)
				{
				case 10:	m_talkWindow->Reset(m_scriptNum, CARD::NERO);		break;
				case 11:	m_talkWindow->Reset(m_scriptNum, CARD::JOHN);		break;
				case 12:	m_talkWindow->Reset(m_scriptNum, CARD::NERO);		break;
				case 13:	m_talkWindow->Reset(m_scriptNum, CARD::NERO);		break;
				case 14:	m_talkWindow->Reset(m_scriptNum, CARD::JOHN);		break;
				case 15:	m_talkWindow->Reset(m_scriptNum, CARD::NERO);		break;
				case 16:	m_talkWindow->Reset(m_scriptNum, CARD::NERO);		break;
				case 17:	m_talkWindow->Reset(m_scriptNum, CARD::JOHN);		break;
				case 18:	m_talkWindow->Reset(m_scriptNum, CARD::NERO);		break;
				case 19:	m_talkWindow->Reset(m_scriptNum, CARD::JOHN);		break;
				case 20:	m_talkWindow->Reset(m_scriptNum, CARD::JOHN);		break;
				case 21:	m_talkWindow->Reset(m_scriptNum, CARD::JOHN);		break;
				case 22:	m_talkWindow->Reset(m_scriptNum, CARD::NERO);		break;
				case 23:	m_talkWindow->Reset(m_scriptNum, CARD::JOHN);		break;
				case 24:	m_talkWindow->Reset(m_scriptNum, CARD::NERO);		break;
				case 25:	m_talkWindow->Reset(m_scriptNum, CARD::JOHN);		break;
				case 26:	m_talkWindow->Reset(m_scriptNum, CARD::JOHN);		break;
				case 27:	m_talkWindow->Reset(m_scriptNum, CARD::JOHN);		break;
				case 28:	m_talkWindow->Reset(m_scriptNum, CARD::NERO);		break;
				case 29:	m_talkWindow->Reset(m_scriptNum, CARD::JOHN);		break;
				case 30:	m_talkWindow->Reset(m_scriptNum, CARD::NERO);		break;
				case 31:	m_talkWindow->Reset(m_scriptNum, CARD::JOHN);		break;
				default:														break;
				}
				m_bScriptReset = false;
			}
		}

		if(input->IsLButtonUp()) {
			m_scriptNum++;
			m_bScriptReset = true;
		}
		if(m_scriptNum >= NumberOfLines)
		{
			CNero::getNero()->OffStoryProgress(STORY::STORY05);
			m_scriptNum = 0;
			m_bTalkOn = false;
		}
	}
	if(!m_bTalkOn)
	{
		if(m_fadeTimer->GetTimer() && m_bFadeIn)
		{
			if(m_innButton->IsBtnUp())
			{
				m_sound_Move->Play();
				m_fadeTimer->SetTimer(1.0f, false);
				m_bFadeIn = false;

				m_nextSceneNum = SCENE::INN;
				CNero::getNero()->m_numInn++;
				goto end;
			}

			if(m_fieldButton->IsBtnUp())
			{
				m_sound_Move->Play();
				m_fadeTimer->SetTimer(1.0f, false);
				m_bFadeIn = false;

				m_nextSceneNum = SCENE::FIELD;
				if(CNero::getNero()->m_numOut == 0) {
					CNero::getNero()->SetStoryProgress(STORY::STORY03);
				}
				CNero::getNero()->m_numOut++;
				goto end;
			}
		}
	}
end:
	if(m_fadeTimer->GetTimer() && !m_bFadeIn) {
		CSceneManager::getSceneManager()->SetScene(m_nextSceneNum);
	}

	m_bgm->Play();

}

void CScene_Town::Render()
{
	float opacity = 0.0f;
	if(m_bFadeIn) {
		opacity = 1.0f - (m_fadeTimer->RemainTime()/m_fadeTimer->GetSetTime());
	}
	else {
		opacity = (m_fadeTimer->RemainTime()/m_fadeTimer->GetSetTime());
	}

	if(opacity == 1.0f)
	{
		CObjectManager::getObjectManager()->RenderAllObjects();
		m_bgm->Volume(1.0f);

		if(CNero::getNero()->GetStoryProgress(STORY::STORY05))
		{
			if(m_bTalkOn)
			{
				m_talkWindow->Update(m_input);
				m_talkWindow->Render();
			}
		}
		else
		{
			m_innButton->Render();
			m_fieldButton->Render();
		}
	}
	else {
		CObjectManager::getObjectManager()->RenderAllObjects(opacity);
		m_bgm->Volume(opacity);
	}
}