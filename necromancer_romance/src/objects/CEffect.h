#ifndef _CEFFECT_H_
#define _CEFFECT_H_

class CBitmap;
class CTextureShader;
class CTime;
class CObject_Num;

class CEffect
{
private:

public:
	CEffect();
	CEffect(const CEffect&);
	~CEffect();

	virtual void Initialize();
	virtual void Shutdown();

	virtual void Reset();
	virtual void SetDamage(int num, int totalDamage);
	virtual bool GetAlive();

	virtual void Update();
	virtual void Render();

};

#endif