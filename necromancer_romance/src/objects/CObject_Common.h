#ifndef _COBJECT_COMMON_H_
#define _COBJECT_COMMON_H_

#include "CObject.h"

class CBitmap;
class CTextureShader;

class CObject_Common : public CObject
{
private:
	CBitmap* m_common;
	CTextureShader* m_shader;

public:
	CObject_Common();
	CObject_Common(const CObject_Common&);
	~CObject_Common();

	void Initalize(int, int, int, float, float, WCHAR*);
	void Shutdown();

	virtual void Update(CInput*);
	virtual void Render();
	Qusy::Rect GetRect();
	CBitmap* GetBitmap();
};

#endif