#ifndef _CMONSTER_ARMORED_H_
#define _CMONSTER_ARMORED_H_

class CTime;

#include "CMonster.h"

class CMonster_Armored : public CMonster
{
private:

public:
	CMonster_Armored();
	~CMonster_Armored();

	virtual void Initialize();

	int skill_1();
	int skill_2();

	virtual void Update();
	virtual int UseSkill(int num);
};

#endif