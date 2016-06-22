#ifndef _CMONSTER_SHOA_H_
#define _CMONSTER_SHOA_H_

class CTime;

#include "CMonster.h"

class CMonster_Shoa : public CMonster
{
private:

public:
	CMonster_Shoa();
	~CMonster_Shoa();

	virtual void Initialize();

	int skill_1();
	int skill_2();

	virtual void Update();
	virtual int UseSkill(int num);
};

#endif