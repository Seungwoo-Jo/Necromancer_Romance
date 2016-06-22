#ifndef _CMONSTER_SUCCUBUS_H_
#define _CMONSTER_SUCCUBUS_H_

class CTime;

#include "CMonster.h"

class CMonster_Succubus : public CMonster
{
private:

public:
	CMonster_Succubus();
	~CMonster_Succubus();

	virtual void Initialize();

	int skill_1();
	int skill_2();

	virtual void Update();
	virtual int UseSkill(int num);
};

#endif