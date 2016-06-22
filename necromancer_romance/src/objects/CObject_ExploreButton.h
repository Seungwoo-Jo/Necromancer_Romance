#ifndef _COBJECT_EXPLOREBUTTON_H_
#define _COBJECT_EXPLOREBUTTON_H_

#include "CObject.h"

enum RESULT
{
	WON = 0,
	LOST,
	BATTLE,
	TREASURE,
	TRAP,
};

class CInput;
class CFont;
class CTime;
class CBitmap;
class CTextureShader;
class CCard;
class CSound;

class CObject_ExploreButton : public CObject
{
private:
	CBitmap* m_button;
	CTextureShader* m_buttonShader;

	CBitmap* m_buttonIcon[3];
	CTextureShader* m_buttonIconShader[3];

	CBitmap* m_result;
	CTextureShader* m_resultShader;
	
	CBitmap* m_resultMark[5];
	CTextureShader* m_resultMarkShader;

	CCard* m_resultTarget;

	Qusy::Rect m_rect[3];

	CFont* m_text;
	CTime* m_timer;
	CTime* m_resultTimer[5];
	
	CSound* m_sound_Explore;
	CSound* m_sound_Treasure;
	CSound* m_sound_Trap;
	
	CInput* m_input;
	int m_exploreNow;
	int m_exploreMax;
	int m_resultValue;

	int m_select;
	int m_resultNum;
	bool m_bShow;
public:
	CObject_ExploreButton();
	~CObject_ExploreButton();

	void Initialize();
	void Shutdown();

	void Update(CInput*);
	void Render();

	int getSelect();
	void Show(bool);

	
	// 이기면 RESULT::WON
	// 지면    RESULT::LOST
	void setBattleResult(int);
};

#endif