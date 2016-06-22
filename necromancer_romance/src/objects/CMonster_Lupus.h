#ifndef _CMONSTER_LUPUS_H_
#define _CMONSTER_LUPUS_H_

class CTime;

#include "CMonster.h"

class CMonster_Lupus : public CMonster
{
private:

public:
	CMonster_Lupus();
	~CMonster_Lupus();

	virtual void Initialize();

	int skill_1();
	int skill_2();

	virtual void Update();
	virtual int UseSkill(int num);
};

#endif