#ifndef _CSCENE_CREDIT_H_
#define _CSCENE_CREDIT_H_

#include "CScene.h"

class CObject_Background;
class CFont;
class CTime;

class CScene_Credit : public CScene
{
private:
	CObject_Background* m_background;
	CFont*	m_Text;
	CTime*	m_fadeTimer;
	bool m_bFadeIn;

public:
	CScene_Credit();
	CScene_Credit(const CScene_Credit&);
	~CScene_Credit();

	virtual void Initialize();
	virtual void Shutdown();

	virtual void Update(CInput*);
	virtual void Render();
};

#endif