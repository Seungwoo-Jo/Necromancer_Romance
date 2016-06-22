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
	m_Text->Initialize(L"�����ٸ����");

	m_fadeTimer = new CTime();
	m_fadeTimer->SetTimer(1.0f, false);

	CScriptManager::getSkillManager()->AddScript(0, L"��, �̰� �� ���ϴٴϱ�!\n������ ��� ����� �� �� �ִٴ�.\n��¼�� �� ������� �Ź��� �ɱ�?");
	CScriptManager::getSkillManager()->AddScript(1, L"�� ����, �Ű� �ΰ� ���̿� �Ͼ ������ �˰� �־�?\n���� �� �� �¼� �ο����� �������̾���.\n��������� �α��� 2/3�� �װ� ��. �׾߸��� �η��� ������ �ұ�.");
	CScriptManager::getSkillManager()->AddScript(2, L"������ ���⸦ ���� �η���, �����ָ��̶� �ɸ� ��ó��\n�� ���� �ڽ��� ���Ҿ�. �α��� ȸ��������\n�Ƿ� ���� �ʱ��ع��Ⱦ�.");
	CScriptManager::getSkillManager()->AddScript(3, L"�� ���ķ� ������ ��õǰ�, �߽� ������ ��������...\n������ǰ� �����ϰ�... ������ ������� ��ġ�� �뺴��\n�̷��� ź���Ѱž�.");
	CScriptManager::getSkillManager()->AddScript(4, L"����, �������� ���л��̶�� ���� �� �˰� �ִٰ�.\n... Ȥ�� ��������� ���� �� �� �׾���� �ɱ�?");
	CScriptManager::getSkillManager()->AddScript(5, L"���� �Ƴ�");

	CScriptManager::getSkillManager()->AddScript(10, L"��, �غ�� ������.\n��Ȱ�� �ǽ��� ��������.");
	CScriptManager::getSkillManager()->AddScript(11, L"��, ��. ������ �غ����.");
	CScriptManager::getSkillManager()->AddScript(12, L"......");
	CScriptManager::getSkillManager()->AddScript(13, L"............");
	CScriptManager::getSkillManager()->AddScript(14, L"������......");
	CScriptManager::getSkillManager()->AddScript(15, L"����...���? �Ƴ�, ������ �Ϻ��߾�...");
	CScriptManager::getSkillManager()->AddScript(16, L"�̰� ����... �� ���ݾ�?");
	CScriptManager::getSkillManager()->AddScript(17, L"������������!!! ����, �ҹ����ݾ�! �����ٰ�!\n���� ���� ���� ��ȥ�� ���ư����ȴٰ�!");
	CScriptManager::getSkillManager()->AddScript(18, L"����ü... �����...");
	CScriptManager::getSkillManager()->AddScript(19, L"�̺� �̺� �׷�!!! ��Ƹ� ���̰� ����\n'���� ����' �ΰ��� �װ� �Ǿ� ���� �� �Ƴ�??");
	CScriptManager::getSkillManager()->AddScript(20, L"���� �� ��Ȳ�� ��ü ���ھ�!\nå�� �´´ٸ� �װ� �ڻ��ϴ� �� �ۿ�!!");
	CScriptManager::getSkillManager()->AddScript(21, L"���ʺ��� ���� �ȵƴ� �ž�!\n�� å�� ���� �� �յڰ� ���� �ʴ�\n�㹫�Ͷ��� �Ҹ����!");
	CScriptManager::getSkillManager()->AddScript(22, L"�׷� �� ���ݲ� �� ����...");
	CScriptManager::getSkillManager()->AddScript(23, L"�׷��� �׳��� ������ �����ݾ�?\n�װɷ� ���� �� �ϴ� �ž�?");
	CScriptManager::getSkillManager()->AddScript(24, L"Ū... ����� �� ���� �Ŵ�.\n���ݺ��� �ٽ� ã�ƺ��ھ�.");
	CScriptManager::getSkillManager()->AddScript(25, L"�׷�, �� �� �ٺ����� �ذ�å�� �ִٰ� ���� �� ��?");
	CScriptManager::getSkillManager()->AddScript(26, L"���� �׿���.");
	CScriptManager::getSkillManager()->AddScript(27, L"��Ȱ������ ������Ű�� �ִ� �� ��.\n���� ���̸� ������ Ǯ����.\n�� ���� ��Ȱ������ ����� �� ����. �� �׷�?");
	CScriptManager::getSkillManager()->AddScript(28, L"���� �� ��� �Ƕ���...");
	CScriptManager::getSkillManager()->AddScript(29, L"�ٷ� �װž�! ���� ���� �ڼ����.");
	CScriptManager::getSkillManager()->AddScript(30, L"������ ���� ���� ���� �� ���� �� ���� �������� �ʾҾ�.\n��� ã��?");
	CScriptManager::getSkillManager()->AddScript(31, L"���ݾ�, ���� ���� �𸣰� �°� �������� ���� �� �� ���ŵ�?\nƯ���� �ȳ����ش� �̰ž�.");

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