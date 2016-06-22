#ifndef _COBJECT_INNBUTTON_H_
#define _COBJECT_INNBUTTON_H_

#include "CObject.h"

class CBitmap;
class CTextureShader;
class CTime;

class CObject_InnButton : public CObject
{
private:
	CBitmap* m_button;
	CTextureShader* m_shader;

	CBitmap* m_notice;
	CTextureShader* m_noticeShader;

	CInput* m_input;
	CTime* m_fadeTimer;

	bool m_bFocus;
	bool m_bClick;

public:
	CObject_InnButton();
	CObject_InnButton(const CObject_InnButton&);
	~CObject_InnButton();

	void Initalize(int, int, int);
	void Shutdown();

	virtual void Update(CInput*);
	virtual void Render();

	bool IsBtnUp();
	Qusy::Rect GetButtonRect();
};

#endif