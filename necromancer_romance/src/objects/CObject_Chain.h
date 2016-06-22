#ifndef _COBJECT_CHAIN_H_
#define _COBJECT_CHAIN_H_

class CBitmap;
class CTextureShader;
class CTime;
class CSound;

#include "CObject.h"

class CObject_Chain : public CObject
{
private:
	CBitmap* m_chainStart;
	CBitmap* m_chainMove;
	CTextureShader* m_chainShader;
	CTime* m_moveTimer;

	CSound* m_sound_ChainStart;
	CSound* m_sound_ChainMove;

	bool m_bMove;

public:
	CObject_Chain();
	CObject_Chain(const CObject_Chain&);
	~CObject_Chain();

	void Initialize();
	virtual void Shutdown();

	virtual void Update(CInput*);
	virtual void Render();

	void Reset();

	void Move();
};


#endif