#ifndef _COBJECT_MONSTERGAUGE_H_
#define _COBJECT_MONSTERGAUGE_H_

#include "CObject.h"

class CBitmap;
class CTextureShader;
class CMonster;

class CObject_Monstergauge : public CObject
{
private:
	CBitmap* m_barBack;
	CBitmap* m_hpBar;
	CBitmap* m_spBar;
	CBitmap* m_timer;
	CTextureShader* m_shader[4];

	CBitmap* m_type[5];
	CTextureShader* m_typeShader;
	CMonster* m_useMonster;

public:
	CObject_Monstergauge();
	CObject_Monstergauge(const CObject_Monstergauge&);
	~CObject_Monstergauge();

	void Initalize(CMonster*);
	void Shutdown();

	virtual void Update(CInput*);
	virtual void Render();

	void setMonster(CMonster*);
};

#endif