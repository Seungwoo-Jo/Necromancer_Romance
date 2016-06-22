#ifndef _CSCENE_FIELD_H_
#define _CSCENE_FIELD_H_

#include "CScene.h"

class CInput;
class CBitmap;
class CTextureShader;
class CObject_Background;
class CObject_Chain;
class CObject_Skillselect;
class CObject_Monstergauge;
class CObject_Target;
class CObject_PartySlot;
class CObject_MemberChange;
class CObject_ExploreBar;
class CObject_ExploreButton;
class CObject_TalkWindow;
class CFont;
class CTime;
class CSound;

class CScene_Field : public CScene
{
private:
	CInput* m_input;
	CBitmap* m_stage1Walk;
	CBitmap* m_stage1BossWalk;
	CBitmap* m_stage2Walk;
	CBitmap* m_stage2BossWalk;
	CTextureShader* m_walkShader;
	CObject_Background* m_stage1Bg;
	CObject_Background* m_stage1BossBg;
	CObject_Background* m_stage2Bg;
	CObject_Background* m_stage2BossBg;
	CObject_Chain* m_chain;
	CObject_PartySlot* m_partySlot;
	CObject_Skillselect* m_skillButton;
	CObject_Monstergauge* m_monsterGauge;
	CObject_MemberChange* m_memberChange;
	CObject_Target*	m_targetMark;
	CObject_ExploreBar* m_exploreBar;
	CObject_ExploreButton* m_exploreBtn;
	CObject_TalkWindow* m_talkWindow;
	CFont*	m_Text;
	CTime*	m_fadeTimer;
	CTime*  m_resultTimer;
	CTime*	m_battleTimer;
	CTime*	m_rotateDelay;
	CTime*	m_walkTimer;
	CSound* m_sound_Move;
	CSound* m_bgm_stage1;
	CSound* m_bgm_stage1_boss;
	CSound* m_bgm_stage2;
	CSound* m_bgm_stage2_boss;

	bool m_bFadeIn;
	bool m_bTalkOn;
	bool m_bScriptReset;
	bool m_bExplore;
	bool m_bBattle;
	bool m_bTresure;
	bool m_bTrap;
	bool m_bWalk;
	bool m_bBossClear;
	int m_scriptNum;
	int m_monsterDamage;
	int m_cardDamage;
	int m_skillNum;

public:
	CScene_Field();
	CScene_Field(const CScene_Field&);
	~CScene_Field();

	virtual void Initialize();
	virtual void Shutdown();

	virtual void Update(CInput*);
	virtual void Render();
};

#endif