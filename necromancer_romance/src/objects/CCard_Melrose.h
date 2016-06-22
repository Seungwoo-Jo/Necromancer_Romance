#ifndef _CCARD_MELROSE_H_
#define _CCARD_MELROSE_H_

#include "CCard.h"

class CCard_Melrose : public CCard
{
private:

public:
	CCard_Melrose();
	~CCard_Melrose();

	virtual void Initialize();
	virtual void Shutdown();
	virtual void PowerUp();

	virtual int skill_1();
	virtual int skill_2();
	virtual int skill_3();
	virtual int UseSkill(int num);
};

#endif