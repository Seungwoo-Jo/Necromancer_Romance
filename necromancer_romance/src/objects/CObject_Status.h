#ifndef _COBJECT_STATUS_H_
#define _COBJECT_STATUS_H_

#include "CObject.h"

class CBitmap;
class CTextureShader;
class CObject_Cardgauge;
class CCard;
class CTime;
class CFont;

class CObject_Status : public CObject
{
private:
	CBitmap* m_status;
	CBitmap* m_story;
	CTextureShader* m_shader[2];
	
	CBitmap* m_type[5];
	CTextureShader* m_typeShader;

	CBitmap* m_powerUp;
	CTextureShader* m_powerUpShader;
	
	CObject_Cardgauge* m_gauge;

	CCard* m_card;

	CTime* m_timer;
	CFont* m_text;

	Qusy::Rect m_firstSize;
	Qusy::Rect m_finalSize;
	Qusy::Rect m_currentRect;

	bool m_bStatus;
	bool m_bOpen;

public:
	CObject_Status();
	CObject_Status(const CObject_Status&);
	~CObject_Status();

	void Initalize(CCard*);
	void Shutdown();

	virtual void Update(CInput*);
	virtual void Render();

	void setCard(CCard*);
	CCard* getCard();
	void setOpen(bool);
	bool getOpen();
};

#endif