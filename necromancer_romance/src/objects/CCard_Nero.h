#ifndef _CCARD_NERO_H_
#define _CCARD_NERO_H_

#include "CCard.h"

class CCard_Nero : public CCard
{
private:

public:
	CCard_Nero();
	~CCard_Nero();

	virtual void Initialize();
	virtual void Shutdown();
	virtual void PowerUp();

	virtual int skill_1();
	virtual int skill_2();
	virtual int skill_3();
	virtual int UseSkill(int num);
};

#endif