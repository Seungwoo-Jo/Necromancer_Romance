#ifndef _CCARD_EADRIC_H_
#define _CCARD_EADRIC_H_

#include "CCard.h"

class CCard_Eadric : public CCard
{
private:

public:
	CCard_Eadric();
	~CCard_Eadric();

	virtual void Initialize();
	virtual void Shutdown();
	virtual void PowerUp();

	virtual int skill_1();
	virtual int skill_2();
	virtual int skill_3();
	virtual int UseSkill(int num);
};

#endif