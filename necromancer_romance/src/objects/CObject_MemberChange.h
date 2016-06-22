#ifndef _COBJECT_MEMBERCHANGE_H_
#define _COBJECT_MEMBERCHANGE_H_

#define PAGE_CARD_NUM	5

#include "CObject.h"

class CBitmap;
class CTextureShader;
class CInput;
class CCard;
class CObject_Common;
class CObject_Status;
class CObject_Cardgauge;

class CObject_MemberChange : public CObject
{
private:
	CInput* m_input;
	CBitmap* m_background;
	CTextureShader* m_shader;
	CObject_Common* m_turn;
	CObject_Status* m_statusWindow;
	CObject_Cardgauge* m_gauge[9];

	CBitmap* m_statusBtn;
	CTextureShader* m_statusBtnShader;
	float m_btnOpacity[4];
	CCard* m_clickCard;
	bool m_bShow;
	int m_pageNow;
	int m_pageMax;
	CCard* m_changeArray[30];
	int m_numOfCard;
	Qusy::Point m_mouse;
	bool m_bDrag[PAGE_CARD_NUM+4];
	bool m_bActivate;

	float m_sceneOpacity;
	int m_srcCard;
	int m_destCard;
	int m_sceneNum;
public:
	CObject_MemberChange();
	CObject_MemberChange(const CObject_MemberChange&);
	~CObject_MemberChange();

	void Initalize(int sceneNum);
	void Shutdown();

	virtual void Update(CInput*);
	virtual void Render();

	void Show(bool);
	void acceptSceneOpacity(float); 
	void removeNull();

	void SetActivate(bool);
	bool GetActivate();

	bool GetStatusOpen();
};

#endif