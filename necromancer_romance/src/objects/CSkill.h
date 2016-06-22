#ifndef _CSKILL_H_
#define _CSKILL_H_

class CCard;
class CMonster;

#define TOTAL_CARD_SKILL	4
#define TOTAL_MONSTER_SKILL	3
#define TOTAL_SKILL			7

enum SKILL
{
	CARD_SKILL_01 = 0,
	CARD_SKILL_02,
	CARD_SKILL_03,
	NERO_CHANGE,

	MONSTER_SKILL_01,
	MONSTER_SKILL_02,
	MONSTER_SKILL_03,
};

class CSkill
{
private:
	unsigned int m_idNum;
	int m_damage;
	int m_useAp;
	wchar_t m_skillName[16];

public:
	CSkill();
	CSkill(const CSkill&);
	~CSkill();

	virtual void Initialize();

	unsigned int getIdNum();
	void setIdNum(unsigned int);

	wchar_t* getSkillName();
	void setSkillName(wchar_t[]);

	virtual void UseSkill(CCard*);
	virtual void UseSkill(CMonster*);
	virtual void UseSkillToMonster(CCard*, CMonster*);
	virtual void UseSkillToCard(CMonster*, CCard*);
};

#endif