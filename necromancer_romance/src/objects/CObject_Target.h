#ifndef _COBJECT_TARGET_H_
#define _COBJECT_TARGET_H_

#include "CObject.h"

#define PI 3.14159265358979

class CTime;
class CBitmap;
class CTextureShader;
class CBattleManager;

class CObject_Target : public CObject
{
private:
	CBitmap* m_targetMark;
	CTextureShader* m_shader;

	unsigned int m_outputNum;

	CTime* m_spriteTimer;

public:
	CObject_Target();
	CObject_Target(const CObject_Target&);
	~CObject_Target();

	void Initalize(int, int, int);
	void Shutdown();

	virtual void Update(CInput*);
	virtual void Render();

	void setMark();
};

#endif