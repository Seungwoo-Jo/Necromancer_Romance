#ifndef _CMONSTER_SHOA2_H_
#define _CMONSTER_SHOA2_H_

class CTime;

#include "CMonster.h"

class CMonster_Shoa2 : public CMonster
{
private:

public:
	CMonster_Shoa2();
	~CMonster_Shoa2();

	virtual void Initialize();

	int skill_1();
	int skill_2();

	virtual void Update();
	virtual int UseSkill(int num);
};

#endif