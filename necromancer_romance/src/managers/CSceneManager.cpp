#include "..\framework\CDirect3d.h"
#include "..\framework\common.h"

#include "CSceneManager.h"

// SCENE HEADER //
#include "..\scenes\CScene_Intro.h"
#include "..\scenes\CScene_Preload.h"
#include "..\scenes\CScene_Title.h"
#include "..\scenes\CScene_Town.h"
#include "..\scenes\CScene_Field.h"
#include "..\scenes\CScene_Inn.h"
#include "..\scenes\CScene_Credit.h"
#include "..\scenes\CScene_Story01.h"
#include "..\scenes\CScene_Story02.h"

CSceneManager* CSceneManager::s_sceneManager = NULL;

CSceneManager::CSceneManager()
{
	m_nowScene = 0;
	m_setSceneNum = -1;
}

CSceneManager::CSceneManager(const CSceneManager& temp)
{
}

CSceneManager::~CSceneManager()
{
}

bool CSceneManager::Initialize()
{
	m_sceneMap = new std::map<UINT, CScene*>;
	m_nowScene = 0;
	m_setSceneNum = -1;
	if(m_sceneMap == NULL)
	{
		return false;
	}
	return true;
}

bool CSceneManager::Shutdown()
{
	if(m_sceneMap == NULL)
	{
		MessageBox(CDirect3D::GetDirect3D()->GetHwnd(), L"CSceneManager::Shutdown()\nm_sceneMap is NULL", L"Error", MB_OK);
		return false;
	}

	m_sceneMap->clear();
	SAFE_DELETE(m_sceneMap);
	SAFE_DELETE(s_sceneManager);
	return true;
}

bool CSceneManager::AddScene(UINT sceneNum, CScene* scene)
{
	if(m_sceneMap == NULL)
	{
		MessageBox(CDirect3D::GetDirect3D()->GetHwnd(), L"CSceneManager::AddScene()\nm_sceneMap is NULL", L"Error", MB_OK);
	}
	if(scene == NULL)
	{
		MessageBox(CDirect3D::GetDirect3D()->GetHwnd(), L"CSceneManager::AddScene()\nscene is NULL", L"Error", MB_OK);
		return false;
	}
	std::pair<std::map<UINT, CScene*>::iterator, bool> result;
	result = m_sceneMap->insert(std::map<UINT, CScene*>::value_type(sceneNum, scene));

	if(!result.second)
	{
		MessageBox(CDirect3D::GetDirect3D()->GetHwnd(), L"CSceneManager::AddScene()\nresult.second is false", L"Error", MB_OK);
	}

	return result.second;
}

CScene* CSceneManager::GetNowScene()
{
	if(m_sceneMap == NULL)
	{
		MessageBox(CDirect3D::GetDirect3D()->GetHwnd(), L"CSceneManager::GetScene()\nm_sceneMap is NULL", L"Error", MB_OK);
	}
	if(m_nowScene == NULL)
	{
		MessageBox(CDirect3D::GetDirect3D()->GetHwnd(), L"CSceneManager::GetScene()\nm_nowScene is NULL", L"Error", MB_OK);
	}
	return m_nowScene;
}

void CSceneManager::SetScene(UINT sceneNum)
{
	m_setSceneNum = sceneNum;
}

bool CSceneManager::ChangeScene()
{
	if(m_setSceneNum != -1)
	{
		bool result = true;
		CScene* tempScene = NULL;
		it = m_sceneMap->find(m_setSceneNum);

		if( it != m_sceneMap->end() ) {
			tempScene = it->second;
		}
		else
		{
			switch(m_setSceneNum)
			{
			case SCENE::INTRO:
				tempScene = new CScene_Intro();
				result = AddScene(m_setSceneNum, tempScene);
				break;
			case SCENE::PRELOAD:
				tempScene = new CScene_Preload();
				result = AddScene(m_setSceneNum, tempScene);
				break;
			case SCENE::TITLE:
				tempScene = new CScene_Title();
				result = AddScene(m_setSceneNum, tempScene);
				break;
			case SCENE::TOWN:
				tempScene = new CScene_Town();
				result = AddScene(m_setSceneNum, tempScene);
				break;
			case SCENE::FIELD:
				tempScene = new CScene_Field();
				result = AddScene(m_setSceneNum, tempScene);
				break;
			case SCENE::INN:
				tempScene = new CScene_Inn();
				result = AddScene(m_setSceneNum, tempScene);
				break;
			case SCENE::CREDIT:
				tempScene = new CScene_Credit();
				result = AddScene(m_setSceneNum, tempScene);
				break;
			case SCENE::STORY1:
				tempScene = new CScene_Story01();
				result = AddScene(m_setSceneNum, tempScene);
				break;
			case SCENE::STORY2:
				tempScene = new CScene_Story02();
				result = AddScene(m_setSceneNum, tempScene);
				break;
			default:
				result = false;
				break;
			}

			if(tempScene == NULL)
			{
				MessageBox(CDirect3D::GetDirect3D()->GetHwnd(), L"CSceneManager::GetScene(UINT)\ntempScene is NULL", L"Error", MB_OK);
				return false;
			}
			if(!result)
			{
				MessageBox(CDirect3D::GetDirect3D()->GetHwnd(), L"CSceneManager::GetScene(UINT)\nresult is false", L"Error", MB_OK);
				return result;
			}
		}

		if(m_nowScene != NULL) {
			m_nowScene->Shutdown();
		}
		m_nowScene = tempScene;
		m_nowScene->Initialize();

		m_setSceneNum = -1;
	}
	return true;
}
