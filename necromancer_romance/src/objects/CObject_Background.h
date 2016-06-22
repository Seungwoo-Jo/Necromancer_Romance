#ifndef _COBJECT_BACKGROUND_H_
#define _COBJECT_BACKGROUND_H_

#include "CObject.h"

class CBitmap;
class CTextureShader;

class CObject_Background : public CObject
{
private:
	CBitmap* m_background;
	CTextureShader* m_shader;

public:
	CObject_Background();
	CObject_Background(const CObject_Background&);
	~CObject_Background();

	void Initalize(int, int, int, WCHAR*);
	void Shutdown();

	virtual void Update(CInput*);
	virtual void Render();
};

#endif