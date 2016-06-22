#ifndef _COBJECT_LOGO_H_
#define _COBJECT_LOGO_H_

#include "CObject.h"

class CBitmap;
class CTextureShader;

class CObject_Logo : public CObject
{
private:
	CBitmap* m_logo;
	CTextureShader* m_shader;

public:
	CObject_Logo();
	CObject_Logo(const CObject_Logo&);
	~CObject_Logo();

	void Initalize(int, int, int);
	void Shutdown();

	virtual void Update(CInput*);
	virtual void Render();
};

#endif