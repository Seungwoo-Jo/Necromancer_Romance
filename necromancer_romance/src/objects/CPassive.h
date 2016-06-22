#ifndef _CEFFECT_H_
#define _CEFFECT_H_

class CBitmap;
class CTextureShader;
class CTime;

class CPassive
{
private:

public:
	CPassive();
	CPassive(const CPassive&);
	~CPassive();

	virtual void Initialize();
	virtual void Shutdown();

	virtual void Reset();
	virtual void SetDamage(int num, int totalDamage);
	virtual bool GetAlive();

	virtual void Update();
	virtual void Render();

};

#endif