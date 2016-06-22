#ifndef _CCARD_RENE_H_
#define _CCARD_RENE_H_

#include "CCard.h"

class CCard_Rene : public CCard
{
private:

public:
	CCard_Rene();
	~CCard_Rene();

	virtual void Initialize();
	virtual void Shutdown();
	virtual void PowerUp();

	virtual int skill_1();
	virtual int skill_2();
	virtual int skill_3();
	virtual int UseSkill(int num);
};

#endif