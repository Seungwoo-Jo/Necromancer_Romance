// ..\framework
#include "..\framework\CInput.h"
#include "..\framework\common.h"
#include "..\framework\CFont.h"
#include "..\framework\CTime.h"

// ..\managers
#include "..\managers\CObjectManager.h"
#include "..\managers\CSceneManager.h"

// ..\objects
#include "..\objects\CObject_Background.h"

// ..\scenes
#include "CScene_Credit.h"

CScene_Credit::CScene_Credit()
{
	m_background = NULL;
	m_Text = NULL;
	m_fadeTimer = NULL;
	m_bFadeIn	= true;
}

CScene_Credit::CScene_Credit(const CScene_Credit& scene)
{
}

CScene_Credit::~CScene_Credit()
{
}

void CScene_Credit::Initialize()
{
	m_background = new CObject_Background();
	m_background->Initalize(0, 0, 100, L"res/background/credit_back.png");
	CObjectManager::getObjectManager()->AddObject(static_cast<CObject*>(m_background));

	m_Text = new CFont();
	m_Text->Initialize(L"³ª´®¹Ù¸¥°íµñ");

	m_fadeTimer = new CTime();
	m_fadeTimer->SetTimer(1.0f, false);
}

void CScene_Credit::Shutdown()
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
	m_bFadeIn = true;

	CObjectManager::getObjectManager()->RemoveAllObjects();
}

void CScene_Credit::Update(CInput* input)
{
	CObjectManager::getObjectManager()->UpdateAllObjects(input);

	if(m_fadeTimer->GetTimer() && input->IsRButtonUp())
	{
		m_fadeTimer->SetTimer(1.0f, false);
		m_bFadeIn = false;
	}
	if(m_fadeTimer->GetTimer() && !m_bFadeIn)
	{
		CSceneManager::getSceneManager()->SetScene(SCENE::TITLE);
	}
	
}

void CScene_Credit::Render()
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
	}
	else {
		CObjectManager::getObjectManager()->RenderAllObjects(opacity);
	}
}