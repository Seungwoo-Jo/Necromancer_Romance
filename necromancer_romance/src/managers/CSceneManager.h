#ifndef _CSCENE_MANAGER_H_
#define _CSCENE_MANAGER_H_

// INCLUDES //
#include <map>
#include "..\scenes\CScene.h"


// ENUM //
enum SCENE
{
	INTRO		= 0,
	PRELOAD,
	TITLE,
	TOWN,
	INN,
	FIELD,
	CREDIT,
	STORY1,
	STORY2,
};

// Class name: CSceneManager //
class CSceneManager
{
private:
	CScene* m_nowScene;
	static CSceneManager* s_sceneManager;
	
	std::map<unsigned int, CScene*>* m_sceneMap;
	std::map<unsigned int, CScene*>::iterator it;

	unsigned int m_setSceneNum;

	CSceneManager();
	CSceneManager(const CSceneManager&);

public:
	~CSceneManager();

	static CSceneManager* getSceneManager()
	{
		if(s_sceneManager == NULL) {
			s_sceneManager = new CSceneManager;
			s_sceneManager->Initialize();
		}
		return s_sceneManager;
	}

	bool Initialize();
	bool Shutdown();

	bool AddScene(unsigned int, CScene*);

	CScene* GetNowScene();
	void SetScene(unsigned int);
	bool ChangeScene();

};
#endif