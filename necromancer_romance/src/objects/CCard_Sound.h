#ifndef _CCARD_SOUND_H_
#define _CCARD_SOUND_H_

#include "CCard.h"

class CCard_Sound : public CCard
{
private:

public:
	CCard_Sound();
	~CCard_Sound();

	virtual void Initialize();
	virtual void Shutdown();
	virtual void PowerUp();

	virtual int skill_1();
	virtual int skill_2();
	virtual int skill_3();
	virtual int UseSkill(int num);
};

#endif