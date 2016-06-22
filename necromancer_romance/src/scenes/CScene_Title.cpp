// ..\framework
#include "..\framework\CInput.h"
#include "..\framework\common.h"
#include "..\framework\CFont.h"
#include "..\framework\CTime.h"
#include "..\framework\CSound.h"

// ..\managers
#include "..\managers\CObjectManager.h"
#include "..\managers\CSceneManager.h"

// ..\objects
#include "..\objects\CObject_Background.h"
#include "..\objects\CObject_MainButton.h"

// ..\scenes
#include "CScene_Title.h"

CScene_Title::CScene_Title()
{
	m_background = NULL;
	m_Text = NULL;
	m_fadeTimer = NULL;
	m_bFadeIn	= true;
	m_bgm = NULL;
}

CScene_Title::CScene_Title(const CScene_Title& scene)
{
}

CScene_Title::~CScene_Title()
{
}

void CScene_Title::Initialize()
{
	m_background = new CObject_Background();
	m_background->Initalize(0, 0, 100, L"res/background/title_back.png");
	CObjectManager::getObjectManager()->AddObject(static_cast<CObject*>(m_background));

	m_mainButton = new CObject_MainButton();
	m_mainButton->Initalize(909, 355, 50);

	m_Text = new CFont();
	m_Text->Initialize(L"³ª´®¹Ù¸¥°íµñ");

	m_bgm = new CSound();
	m_bgm->Initialize("res/sound/BGM/Title.mp3");
	m_bgm->Loop(true);


	m_fadeTimer = new CTime();
	m_fadeTimer->SetTimer(1.0f, false);
}

void CScene_Title::Shutdown()
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
	m_bFadeIn = true;

	CObjectManager::getObjectManager()->RemoveAllObjects();
}

void CScene_Title::Update(CInput* input)
{
	CObjectManager::getObjectManager()->UpdateAllObjects(input);
	m_mainButton->Update(input);
	static int clickBtn;

	if(m_fadeTimer->GetTimer() && input->IsLButtonUp())
	{
		clickBtn = m_mainButton->GetClickButton();
		if(clickBtn == 1 || clickBtn == 2 || clickBtn == 3)
		{
			m_fadeTimer->SetTimer(1.0f, false);
			m_bFadeIn = false;
		}
	}

	if(m_fadeTimer->GetTimer() && !m_bFadeIn)
	{
		switch(clickBtn)
		{
		case 1:
			CSceneManager::getSceneManager()->SetScene(SCENE::STORY1);
			break;
		case 2:
			CSceneManager::getSceneManager()->SetScene(SCENE::CREDIT);
			break;
		case 3:
			input->SetDestory(true);
			break;

		default:
			break;
		}
	}

	m_bgm->Play();

}

void CScene_Title::Render()
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
		m_mainButton->Render();
		m_bgm->Volume(1.0f);
	}
	else {
		CObjectManager::getObjectManager()->RenderAllObjects(opacity);
		m_mainButton->setOpacity(opacity);
		m_mainButton->Render();
		m_bgm->Volume(opacity);
	}
}