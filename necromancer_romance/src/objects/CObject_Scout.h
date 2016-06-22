#ifndef _COBJECT_SCOUT_H_
#define _COBJECT_SCOUT_H_

#define PAGE_CARD_NUM	5

#include "CObject.h"

class CBitmap;
class CTextureShader;
class CInput;
class CCard;
class CSound;
class CObject_Common;
class CObject_Cardgauge;
class CFont;

class CObject_Scout : public CObject
{
private:
	CInput* m_input;
	CBitmap* m_scoutWindow;
	CTextureShader* m_scoutWindowShader;
	CBitmap* m_scoutBtn;
	CTextureShader* m_scoutBtnShader;

	CObject_Cardgauge* m_gauge[PAGE_CARD_NUM];
	CCard* m_changeArray[30];
	CFont* m_text;

	CSound* m_sound_Scout;
	Qusy::Point m_mouse;
	int m_scoutNum;
	int m_buyPrice;
	int m_pageNow;
	int m_pageMax;
	bool m_bShow;

	float m_sceneOpacity;

public:
	CObject_Scout();
	CObject_Scout(const CObject_Scout&);
	~CObject_Scout();

	void Initalize();
	void Shutdown();

	virtual void Update(CInput*);
	virtual void Render();

	void acceptSceneOpacity(float);
	void Show(bool);
	void removeNull();
};

#endif