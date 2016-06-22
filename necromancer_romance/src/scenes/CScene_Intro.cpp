// ..\framework
#include "..\framework\CDirect3d.h"
#include "..\framework\CInput.h"
#include "..\framework\common.h"
#include "..\framework\CFont.h"
#include "..\framework\CTime.h"

// ..\managers
#include "..\managers\CObjectManager.h"
#include "..\managers\CSceneManager.h"

// ..\objects
#include "..\objects\CObject_Logo.h"

// ..\scenes
#include "CScene_Intro.h"

CScene_Intro::CScene_Intro()
{
	m_logo = NULL;
	m_sceneTimer = NULL;
}

CScene_Intro::CScene_Intro(const CScene_Intro& scene)
{
}

CScene_Intro::~CScene_Intro()
{
}

void CScene_Intro::Initialize()
{
	// 446 82
	int x, y;
	CDirect3D::GetDirect3D()->GetScreenSize(x, y);
	m_logo = new CObject_Logo();
	m_logo->Initalize(370, 185, 100);
	CObjectManager::getObjectManager()->AddObject(static_cast<CObject*>(m_logo));

	m_sceneTimer = new CTime();
	m_sceneTimer->SetTimer(3.0f, false);
}

void CScene_Intro::Shutdown()
{
	if(m_sceneTimer != NULL)
	{
		m_sceneTimer->StopTimer();
		SAFE_DELETE(m_sceneTimer);
	}

	CObjectManager::getObjectManager()->RemoveAllObjects();
}

void CScene_Intro::Update(CInput* input)
{
	float remainTime = m_sceneTimer->RemainTime();
	if(remainTime <= 2.0f) {
		m_logo->setOpacity(remainTime/2);
	}
	CObjectManager::getObjectManager()->UpdateAllObjects(input);

	if(m_sceneTimer->RemainTime() <= 0) {
		CSceneManager::getSceneManager()->SetScene(SCENE::PRELOAD);
	}
}

void CScene_Intro::Render()
{
	CObjectManager::getObjectManager()->RenderAllObjects();
}