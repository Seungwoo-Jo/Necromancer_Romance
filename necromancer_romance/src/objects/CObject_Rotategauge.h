#ifndef _COBJECT_ROTATEGAUGE_H_
#define _COBJECT_ROTATEGAUGE_H_

#include "CObject.h"

class CBitmap;
class CTextureShader;

class CObject_Rotategauge : public CObject
{
private:
	CBitmap* m_barBack;
	CBitmap* m_spBar;
	CTextureShader* m_shader[2];

	float m_remainTime;
public:
	CObject_Rotategauge();
	CObject_Rotategauge(const CObject_Rotategauge&);
	~CObject_Rotategauge();

	void Initalize();
	void Shutdown();

	virtual void Update(CInput*);
	virtual void Render();

	void SetRemainTime(float);
};

#endif