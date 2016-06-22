#ifndef _CSCENE_TITLE_H_
#define _CSCENE_TITLE_H_

#include "CScene.h"

class CObject_Background;
class CObject_MainButton;
class CFont;
class CTime;
class CSound;

class CScene_Title : public CScene
{
private:
	CObject_Background* m_background;
	CObject_MainButton* m_mainButton;
	CFont*	m_Text;
	CTime*	m_fadeTimer;
	CSound* m_bgm;

	bool m_bFadeIn;

public:
	CScene_Title();
	CScene_Title(const CScene_Title&);
	~CScene_Title();

	virtual void Initialize();
	virtual void Shutdown();

	virtual void Update(CInput*);
	virtual void Render();
};

#endif