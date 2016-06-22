#ifndef _COBJECT_CARDGAUGE_H_
#define _COBJECT_CARDGAUGE_H_

#include "CObject.h"

class CBitmap;
class CTextureShader;
class CFont;
class CCard;

class CObject_Cardgauge : public CObject
{
private:
	CBitmap* m_hpBar;
	CTextureShader* m_shader[2];
	CCard* m_useCard;

	CFont* m_hpText;
	CFont* m_apText;

public:
	CObject_Cardgauge();
	CObject_Cardgauge(const CObject_Cardgauge&);
	~CObject_Cardgauge();

	void Initalize(CCard*);
	void Shutdown();

	virtual void Update(CInput*);
	virtual void Render();
	void Render(int, int);

	void SetCard(CCard*);
};

#endif