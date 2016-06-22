#ifndef _CCARD_MORRIGHU_H_
#define _CCARD_MORRIGHU_H_

#include "CCard.h"

class CCard_Morrighu : public CCard
{
private:

public:
	CCard_Morrighu();
	~CCard_Morrighu();

	virtual void Initialize();
	virtual void Shutdown();
	virtual void PowerUp();

	virtual int skill_1();
	virtual int skill_2();
	virtual int skill_3();
	virtual int UseSkill(int num);
};

#endif