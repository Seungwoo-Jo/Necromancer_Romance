#ifndef _CSKILL_CHANGEMEMBER_H_
#define _CSKILL_CHANGEMEMBER_H_

#include "CSkill.h"

class CSkill_ChangeMember : public CSkill
{
private:

public:
	CSkill_ChangeMember();
	~CSkill_ChangeMember();

	virtual void Initialize();
	virtual void UseSkill(CCard*);
};

#endif