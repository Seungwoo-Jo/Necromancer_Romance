#include "CSkill_ChangeMember.h"

CSkill_ChangeMember::CSkill_ChangeMember()
{
	Initialize();
}

CSkill_ChangeMember::~CSkill_ChangeMember()
{

}

void CSkill_ChangeMember::Initialize()
{
	setIdNum(SKILL::NERO_CHANGE);
	setSkillName(L"파티원 교체");
}

void CSkill_ChangeMember::UseSkill(CCard* card)
{
	
}