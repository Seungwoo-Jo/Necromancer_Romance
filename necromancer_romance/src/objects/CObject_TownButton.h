#ifndef _COBJECT_TOWNBUTTON_H_
#define _COBJECT_TOWNBUTTON_H_


#include "CObject.h"

class CBitmap;
class CTextureShader;

class CObject_TownButton : public CObject
{
private:
	CBitmap* m_ButtonUp;
	CBitmap* m_ButtonDown;
	CTextureShader* m_shader;
	CInput* m_input;
	bool m_bBtnDown;
	bool m_bBtnUp;

public:
	CObject_TownButton();
	CObject_TownButton(const CObject_TownButton&);
	~CObject_TownButton();

	void Initalize(int, int, int);
	void Shutdown();

	virtual void Update(CInput*);
	virtual void Render();

	bool IsBtnUp();
	Qusy::Rect GetButtonRect();
};

#endif