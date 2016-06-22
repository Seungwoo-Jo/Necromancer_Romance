#ifndef _CSCENE_STORY02_H_
#define _CSCENE_STORY02_H_

#include "CScene.h"


class CObject_Background;
class CObject_TalkWindow;
class CFont;
class CTime;
class CSound;
class CInput;


class CScene_Story02 : public CScene
{
private:
	CObject_Background* m_background;
	CObject_TalkWindow* m_talkWindow;

	CFont*	m_Text;
	CSound* m_bgm;
	CTime*	m_fadeTimer;
	CInput* m_input;

	Qusy::Point m_mouse;
	bool m_bFadeIn;

	int m_scriptNum;
	int m_nextSceneNum;

public:
	CScene_Story02();
	CScene_Story02(const CScene_Story02&);
	~CScene_Story02();

	virtual void Initialize();
	virtual void Shutdown();

	virtual void Update(CInput*);
	virtual void Render();
};

#endif