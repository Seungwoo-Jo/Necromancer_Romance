#ifndef _CCARD_AOIFE_H_
#define _CCARD_AOIFE_H_

#include "CCard.h"

class CCard_Aoife : public CCard
{
private:

public:
	CCard_Aoife();
	~CCard_Aoife();

	virtual void Initialize();
	virtual void Shutdown();
	virtual void PowerUp();

	virtual int skill_1();
	virtual int skill_2();
	virtual int skill_3();
	virtual int UseSkill(int num);
};

#endif