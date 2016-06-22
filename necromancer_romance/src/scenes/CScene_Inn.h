#ifndef _CSCENE_INN_H_
#define _CSCENE_INN_H_

#include "CScene.h"


class CObject_Background;
class CObject_PartySlot;
class CObject_Scout;
class CObject_MemberChange;
class CObject_TownButton;
class CObject_ChangeButton;
class CObject_ScoutButton;
class CFont;
class CTime;
class CSound;

class CScene_Inn : public CScene
{
private:
	CObject_Background* m_background;
	CObject_PartySlot* m_partySlot;
	CObject_Scout* m_scoutWindow;
	CObject_MemberChange* m_changeWindow;
	CObject_TownButton* m_townButton;
	CObject_ChangeButton* m_changeButton;
	CObject_ScoutButton* m_scoutButton;
	CFont*	m_Text;
	CTime*	m_fadeTimer;

	CSound* m_bgm;
	CSound* m_sound_Select;
	CSound* m_sound_Move;

	Qusy::Point m_mouse;
	bool m_bFadeIn;
	bool m_bScoutWindow;
	bool m_bChangeWindow;
	int m_nextSceneNum;


public:
	CScene_Inn();
	CScene_Inn(const CScene_Inn&);
	~CScene_Inn();

	virtual void Initialize();
	virtual void Shutdown();

	virtual void Update(CInput*);
	virtual void Render();
};

#endif