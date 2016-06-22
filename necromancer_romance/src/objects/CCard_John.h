#ifndef _CCARD_JOHN_H_
#define _CCARD_JOHN_H_

#include "CCard.h"

class CCard_John : public CCard
{
private:

public:
	CCard_John();
	~CCard_John();

	virtual void Initialize();
	virtual void Shutdown();
	virtual void PowerUp();

	virtual int skill_1();
	virtual int skill_2();
	virtual int skill_3();
	virtual int UseSkill(int num);
};

#endif