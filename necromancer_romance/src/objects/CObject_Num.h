#ifndef _COBJECT_NUM_H_
#define _COBJECT_NUM_H_

#include "CObject.h"

class CBitmap;
class CTextureShader;

class CObject_Num : public CObject
{
private:
	CBitmap* m_numberImage[5];
	CTextureShader* m_numberShader[5];

	int m_num[5];
	int m_numLength;

public:
	CObject_Num();
	CObject_Num(const CObject_Num&);
	~CObject_Num();

	void Initialize();
	void Shutdown();

	virtual void Update(CInput*);
	virtual void Render();

	void SetNum(int num);
};

#endif