#ifndef _CCARD_AYRIN_H_
#define _CCARD_AYRIN_H_

#include "CCard.h"

class CCard_Ayrin : public CCard
{
private:

public:
	CCard_Ayrin();
	~CCard_Ayrin();

	virtual void Initialize();
	virtual void Shutdown();
	virtual void PowerUp();

	virtual int skill_1();
	virtual int skill_2();
	virtual int skill_3();
	int UseSkill(int num);
};

#endif