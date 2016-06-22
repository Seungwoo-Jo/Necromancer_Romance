#ifndef _CMONSTER_MAID_H_
#define _CMONSTER_MAID_H_

class CTime;

#include "CMonster.h"

class CMonster_Maid : public CMonster
{
private:

public:
	CMonster_Maid();
	~CMonster_Maid();

	virtual void Initialize();

	int skill_1();
	int skill_2();

	virtual void Update();
	virtual int UseSkill(int num);
};

#endif