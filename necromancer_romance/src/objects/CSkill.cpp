#include <string.h>
#include "..\objects\CCard.h"
#include "..\objects\CMonster.h"
#include "CSkill.h"

CSkill::CSkill()
{
}

CSkill::CSkill(const CSkill& skill)
{
}

CSkill::~CSkill()
{
}

void CSkill::Initialize()
{
	//empty
}

unsigned int CSkill::getIdNum()
{
	return m_idNum;
}

void CSkill::setIdNum(unsigned int idNum)
{
	m_idNum = idNum;
}

wchar_t* CSkill::getSkillName()
{
	return m_skillName;
}

void CSkill::setSkillName(wchar_t name[])
{
	wcscpy(m_skillName, name);
	//m_skillName = name;
}

void CSkill::UseSkill(CCard* card)
{
}

void CSkill::UseSkill(CMonster* card)
{
}

void CSkill::UseSkillToMonster(CCard* card, CMonster* monster)
{
	switch(m_idNum)
	{
	case SKILL::CARD_SKILL_01:
		m_damage = card->getStat().m_atk * 1;
		m_useAp = 1;
		break;

	case SKILL::CARD_SKILL_02:
		m_damage = card->getStat().m_atk * 2;
		m_useAp = 2;
		break;

	case SKILL::CARD_SKILL_03:
		m_damage = card->getStat().m_atk * 3;
		m_useAp = 3;
		break;

	default:
		break;
	}
	monster->setHp(monster->getStat().m_hp - m_damage);
	card->setAp(card->getStat().m_ap - m_useAp);
}

void CSkill::UseSkillToCard(CMonster* monster, CCard* card)
{
	switch(m_idNum)
	{
	case SKILL::MONSTER_SKILL_01:
		m_damage = monster->getStat().m_atk * 1;
		break;

	case SKILL::MONSTER_SKILL_02:
		m_damage = monster->getStat().m_atk * 2;
		break;

	case SKILL::MONSTER_SKILL_03:
		m_damage = monster->getStat().m_atk * 3;
		break;

	default:
		break;
	}
	card->setHp(card->getStat().m_hp - m_damage);
}