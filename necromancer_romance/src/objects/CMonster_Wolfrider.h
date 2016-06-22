#ifndef _CMONSTER_WOLFRIDER_H_
#define _CMONSTER_WOLFRIDER_H_

class CTime;

#include "CMonster.h"

class CMonster_Wolfrider : public CMonster
{
private:

public:
	CMonster_Wolfrider();
	~CMonster_Wolfrider();

	virtual void Initialize();

	int skill_1();
	int skill_2();

	virtual void Update();
	virtual int UseSkill(int num);
};

#endif