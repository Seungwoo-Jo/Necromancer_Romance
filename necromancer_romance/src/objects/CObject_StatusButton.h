#ifndef _COBJECT_STATUSBUTTON_H_
#define _COBJECT_STATUSBUTTON_H_

#include "CObject.h"

class CBitmap;
class CTextureShader;

class CObject_StatusButton : public CObject
{
private:
	CBitmap* m_common;
	CTextureShader* m_shader;

public:
	CObject_StatusButton();
	CObject_StatusButton(const CObject_StatusButton&);
	~CObject_StatusButton();

	void Initalize(int, int, int, float, float, WCHAR*);
	void Shutdown();

	virtual void Update(CInput*);
	virtual void Render();
	Qusy::Rect GetRect();
};

#endif