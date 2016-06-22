#ifndef _CSCENE_TOWN_H_
#define _CSCENE_TOWN_H_

#include "CScene.h"


class CObject_Background;
class CObject_Scout;
class CObject_MemberChange;
class CObject_ChangeButton;
class CObject_FieldButton;
class CObject_InnButton;
class CObject_TalkWindow;
class CFont;
class CTime;
class CSound;


class CScene_Town : public CScene
{
private:
	CObject_Background* m_background;

	CObject_FieldButton* m_fieldButton;
	CObject_InnButton* m_innButton;
	CObject_TalkWindow* m_talkWindow;
	CFont*	m_Text;
	CSound* m_bgm;
	CSound* m_sound_Move;
	CTime*	m_fadeTimer;
	CInput* m_input;

	Qusy::Point m_mouse;
	bool m_bFadeIn;
	bool m_bTalkOn;
	bool m_bScriptReset;

	int m_scriptNum;
	int m_nextSceneNum;

public:
	CScene_Town();
	CScene_Town(const CScene_Town&);
	~CScene_Town();

	virtual void Initialize();
	virtual void Shutdown();

	virtual void Update(CInput*);
	virtual void Render();
};

#endif