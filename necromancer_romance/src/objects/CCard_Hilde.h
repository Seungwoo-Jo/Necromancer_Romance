#ifndef _CCARD_HILDE_H_
#define _CCARD_HILDE_H_

#include "CCard.h"

class CCard_Hilde : public CCard
{
private:

public:
	CCard_Hilde();
	~CCard_Hilde();

	virtual void Initialize();
	virtual void Shutdown();
	virtual void PowerUp();

	virtual int skill_1();
	virtual int skill_2();
	virtual int skill_3();
	virtual int UseSkill(int num);
};

#endif