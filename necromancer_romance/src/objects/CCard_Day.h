#ifndef _CCARD_DAY_H_
#define _CCARD_DAY_H_

#include "CCard.h"

class CCard_Day : public CCard
{
private:

public:
	CCard_Day();
	~CCard_Day();

	virtual void Initialize();
	virtual void Shutdown();
	virtual void PowerUp();

	virtual int skill_1();
	virtual int skill_2();
	virtual int skill_3();;
	virtual int UseSkill(int num);
};

#endif