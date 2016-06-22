#ifndef _COBJECT_SKILLSELECT_H_
#define _COBJECT_SKILLSELECT_H_

#include "CObject.h"

class CBitmap;
class CTextureShader;
class CFont;
class CCard;

class CObject_Skillselect : public CObject
{
private:
	CBitmap* m_skillButton[4];
	CBitmap* m_skillButtonOver;
	CTextureShader* m_shader;

	CFont* m_skillText;

	bool m_over[4];
public:
	CObject_Skillselect();
	CObject_Skillselect(const CObject_Skillselect&);
	~CObject_Skillselect();

	void Initalize();
	void Shutdown();

	virtual void Update(CInput*);
	virtual void Render();
};

#endif