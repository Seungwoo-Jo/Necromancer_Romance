#ifndef _CMONSTER_WAREWOLF_H_
#define _CMONSTER_WAREWOLF_H_

class CTime;

#include "CMonster.h"

class CMonster_Warewolf : public CMonster
{
private:

public:
	CMonster_Warewolf();
	~CMonster_Warewolf();

	virtual void Initialize();

	int skill_1();
	int skill_2();

	virtual void Update();
	virtual int UseSkill(int num);
};

#endif