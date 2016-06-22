#ifndef _CMONSTER_GOD_H_
#define _CMONSTER_GOD_H_

class CTime;

#include "CMonster.h"

class CMonster_God : public CMonster
{
private:

public:
	CMonster_God();
	~CMonster_God();

	virtual void Initialize();

	int skill_1();
	int skill_2();

	virtual void Update();
	virtual int UseSkill(int num);
};

#endif