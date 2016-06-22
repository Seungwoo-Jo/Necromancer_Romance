#ifndef _CCARD_IRON_H_
#define _CCARD_IRON_H_

#include "CCard.h"

class CCard_Iron : public CCard
{
private:

public:
	CCard_Iron();
	~CCard_Iron();

	virtual void Initialize();
	virtual void Shutdown();
	virtual void PowerUp();

	virtual int skill_1();
	virtual int skill_2();
	virtual int skill_3();
	virtual int UseSkill(int num);
};

#endif