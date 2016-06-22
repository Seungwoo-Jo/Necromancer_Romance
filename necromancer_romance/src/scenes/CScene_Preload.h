#ifndef _CSCENE_PRELOAD_H_
#define _CSCENE_PRELOAD_H_

#include "CScene.h"

class CObject_Common;
class CFont;
class CTime;

class CScene_Preload : public CScene
{
private:
	CObject_Common* m_anime;

	CFont*	m_Text;
	CTime*	m_fadeTimer;
	CTime*  m_fakeTimer; // ?!
	bool m_bPreload;
	bool m_bFadeIn;

public:
	CScene_Preload();
	CScene_Preload(const CScene_Preload&);
	~CScene_Preload();

	virtual void Initialize();
	virtual void Shutdown();

	virtual void Update(CInput*);
	virtual void Render();
};

#endif