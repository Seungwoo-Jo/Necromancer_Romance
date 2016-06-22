#ifndef _CSCENE_INTRO_H_
#define _CSCENE_INTRO_H_

#include "CScene.h"

class CObject_Logo;
class CTime;

class CScene_Intro : public CScene
{
private:
	CObject_Logo* m_logo;
	CTime*	m_sceneTimer;

public:
	CScene_Intro();
	CScene_Intro(const CScene_Intro&);
	~CScene_Intro();

	virtual void Initialize();
	virtual void Shutdown();

	virtual void Update(CInput*);
	virtual void Render();
};

#endif