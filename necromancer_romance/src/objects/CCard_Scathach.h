#ifndef _CCARD_SCATHACH_H_
#define _CCARD_SCATHACH_H_

#include "CCard.h"

class CCard_Scathach : public CCard
{
private:

public:
	CCard_Scathach();
	~CCard_Scathach();

	virtual void Initialize();
	virtual void Shutdown();
	virtual void PowerUp();

	virtual int skill_1();
	virtual int skill_2();
	virtual int skill_3();
	virtual int UseSkill(int num);
};

#endif