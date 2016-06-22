// ..\framework
#include "..\framework\CBitmap.h"
#include "..\framework\CTextureShader.h"
#include "..\framework\CInput.h"
#include "..\framework\common.h"
#include "..\framework\CFont.h"
#include "..\framework\CTime.h"
#include "..\framework\CSound.h"

// ..\managers
#include "..\managers\CObjectManager.h"
#include "..\managers\CSceneManager.h"
#include "..\managers\CCardManager.h"
#include "..\managers\CNero.h"

// ..\objects
#include "..\objects\CObject_Background.h"
#include "..\objects\CObject_PartySlot.h"
#include "..\objects\CObject_Scout.h"
#include "..\objects\CObject_MemberChange.h"
#include "..\objects\CObject_TownButton.h"
#include "..\objects\CObject_ChangeButton.h"
#include "..\objects\CObject_ScoutButton.h"

// ..\scenes
#include "CScene_Inn.h"

CScene_Inn::CScene_Inn()
{
	m_background = NULL;
	m_changeWindow = NULL;
	m_townButton = NULL;
	m_changeButton = NULL;
	m_scoutButton = NULL;
	m_Text = NULL;
	m_fadeTimer = NULL;
	m_bgm = NULL;
	m_sound_Select = NULL;
	m_sound_Move = NULL;
	m_bFadeIn	= true;
	m_bScoutWindow = true;
	m_bChangeWindow = true;
	m_nextSceneNum = -1;
}

CScene_Inn::CScene_Inn(const CScene_Inn& scene)
{
}

CScene_Inn::~CScene_Inn()
{
}

void CScene_Inn::Initialize()
{
	m_background = new CObject_Background();
	m_background->Initalize(0, 0, 100, L"res/background/inn_back.png");
	CObjectManager::getObjectManager()->AddObject(static_cast<CObject*>(m_background));

	m_partySlot = new CObject_PartySlot();
	m_partySlot->Initalize();
	CObjectManager::getObjectManager()->AddObject(static_cast<CObject*>(m_partySlot));

	m_scoutWindow = new CObject_Scout();
	m_scoutWindow->Initalize();
	CObjectManager::getObjectManager()->AddObject(static_cast<CObject*>(m_scoutWindow));

	m_changeWindow = new CObject_MemberChange();
	m_changeWindow->Initalize(SCENE::TOWN);
	CObjectManager::getObjectManager()->AddObject(static_cast<CObject*>(m_changeWindow));

	m_townButton = new CObject_TownButton();
	m_townButton->Initalize(260, 426, 15);
	CObjectManager::getObjectManager()->AddObject(static_cast<CObject*>(m_townButton));

	m_scoutButton = new CObject_ScoutButton();
	m_scoutButton->Initalize(542, 426, 15);
	CObjectManager::getObjectManager()->AddObject(static_cast<CObject*>(m_scoutButton));

	m_changeButton = new CObject_ChangeButton();
	m_changeButton->Initalize(824, 426, 15);
	CObjectManager::getObjectManager()->AddObject(static_cast<CObject*>(m_changeButton));

	m_Text = new CFont();
	m_Text->Initialize(L"³ª´®¹Ù¸¥°íµñ");

	m_fadeTimer = new CTime();
	m_fadeTimer->SetTimer(0.85f, false);

	m_bgm = new CSound();
	m_bgm->Initialize("res/sound/bgm/Inn.mp3");
	m_bgm->Loop(true);

	m_sound_Select = new CSound();
	m_sound_Select->Initialize("res/sound/se/select.wav");
	m_sound_Select->Loop(false);

	m_sound_Move = new CSound();
	m_sound_Move->Initialize("res/sound/se/move.wav");
	m_sound_Move->Loop(false);

	m_changeWindow->Show(false);
	m_scoutWindow->Show(false);
}

void CScene_Inn::Shutdown()
{
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
	if(m_sound_Select != NULL)
	{
		m_sound_Select->Release();
		SAFE_DELETE(m_sound_Select);
	}
	if(m_sound_Move != NULL)
	{
		m_sound_Move->Release();
		SAFE_DELETE(m_sound_Move);
	}
	m_bFadeIn = true;
	m_bChangeWindow = false;
	m_bScoutWindow = false;
	m_nextSceneNum = -1;
	CObjectManager::getObjectManager()->RemoveAllObjects();
}

void CScene_Inn::Update(CInput* input)
{
	CObjectManager::getObjectManager()->UpdateAllObjects(input);
	
	input->GetMousePoint(m_mouse.posX, m_mouse.posY);
	
	if(!m_changeWindow->GetStatusOpen())
	{
		if(m_fadeTimer->GetTimer() && input->IsLButtonUp())
		{
			if(Qusy::Collision(m_mouse, m_townButton->GetButtonRect()))
			{
				m_changeWindow->Show(false);
				m_scoutWindow->Show(false);

				m_fadeTimer->SetTimer(0.85f, false);
				m_bFadeIn = false;

				m_sound_Move->Reset();
				m_sound_Move->Play();

				m_sound_Select->Reset();
				m_sound_Select->Play();
			}
		}

		if(m_fadeTimer->GetTimer() && input->IsLButtonUp())
		{
			if(Qusy::Collision(m_mouse, m_scoutButton->GetButtonRect()))
			{
				if(!m_bScoutWindow)
				{
					m_bScoutWindow = true;
					m_scoutWindow->Show(true);
				
					if(m_bChangeWindow) {
						m_bChangeWindow = false;	
						m_changeWindow->Show(false);
					}
				}
				else
				{
					m_bScoutWindow = false;
					m_scoutWindow->Show(false);
				}
				m_sound_Select->Reset();
				m_sound_Select->Play();
			}
			else if(Qusy::Collision(m_mouse, m_changeButton->GetButtonRect()))
			{
				if(!m_bChangeWindow)
				{
					m_bChangeWindow = true;
					m_changeWindow->Show(true);
				
					if(m_bScoutWindow) {
						m_bScoutWindow = false;	
						m_scoutWindow->Show(false);
					}
				}
				else
				{
					m_bChangeWindow = false;
					m_changeWindow->Show(false);
				}
				m_sound_Select->Reset();
				m_sound_Select->Play();
			}
		}
	}
	if(m_fadeTimer->GetTimer() && !m_bFadeIn) {
		CSceneManager::getSceneManager()->SetScene(SCENE::TOWN);
	}

	m_bgm->Play();
}

void CScene_Inn::Render()
{
	float opacity = 0.0f;
	if(m_bFadeIn) {
		opacity = 1.0f - (m_fadeTimer->RemainTime()/m_fadeTimer->GetSetTime());
	}
	else {
		opacity = (m_fadeTimer->RemainTime()/m_fadeTimer->GetSetTime());
	}

	m_changeWindow->acceptSceneOpacity(opacity);

	if(opacity == 1.0f) {
		CObjectManager::getObjectManager()->RenderAllObjects();
	}
	else {
		CObjectManager::getObjectManager()->RenderAllObjects(opacity);
	}
}