#ifndef _COBJECT_MAINBUTTON_H_
#define _COBJECT_MAINBUTTON_H_

#include "CObject.h"

class CBitmap;
class CTextureShader;
class CTime;
class CSound;

class CObject_MainButton : public CObject
{
private:
	CBitmap* m_start;
	CBitmap* m_credit;
	CBitmap* m_quit;
	CBitmap* m_back[3];
	CTextureShader* m_shader[6];

	CTime* m_timer[3];

	float m_opacity[3];
	int m_bClick[3];
	int m_focus;
	bool m_bNext;

public:
	CObject_MainButton();
	CObject_MainButton(const CObject_MainButton&);
	~CObject_MainButton();

	void Initalize(int, int, int);
	void Shutdown();

	virtual void Update(CInput*);
	virtual void Render();
	int GetClickButton();
};

#endif