#ifndef _CEFFECT_DRAWINGSWORD_H_
#define _CEFFECT_DRAWINGSWORD_H_

#include "CEffect.h"

class CSound;

class CEffect_DrawingSword : public CEffect
{
private:
	Qusy::Position m_effectPos;

	CBitmap* m_effectSprite[3];
	CTextureShader* m_effectShader[2];

	CObject_Num* m_num;

	float m_sustainmentTime;
	CTime* m_effectTimer;
	CTime* m_hitTimer;

	CSound* m_sound[2];

	int m_attackNum;
	float m_attackTiming;
	int m_damage;

	bool m_bText;
	bool m_bAttack;
public:
	CEffect_DrawingSword();
	CEffect_DrawingSword(const CEffect_DrawingSword&);
	~CEffect_DrawingSword();

	virtual void Initialize();
	virtual void Shutdown();

	virtual void Reset();
	virtual void SetDamage(int num, int totalDamage);
	virtual bool GetAlive();

	virtual void Update();
	virtual void Render();
};

#endif