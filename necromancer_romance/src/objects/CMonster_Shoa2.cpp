#include "..\framework\CBitmap.h"
#include "..\framework\CTextureShader.h"

#include "..\managers\CNero.h"
#include "..\managers\CSkillManager.h"
#include "..\managers\CBattleManager.h"

#include "CCard.h"
#include "CEffect_Claw.h"
#include "CMonster_Shoa2.h"

CMonster_Shoa2::CMonster_Shoa2()
{
}

CMonster_Shoa2::~CMonster_Shoa2()
{
}

void CMonster_Shoa2::Initialize()
{
	CBitmap* tempBitmap = new CBitmap();
	CTextureShader* tempShader = new CTextureShader();
	CTextureShader* hitShader = new CTextureShader();
	tempBitmap->Initialize(L"res/monsters/monster_shoa.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	tempShader->Initialize(NULL, NULL);
	hitShader->Initialize(NULL, L"shader/RedShader.ps");

	m_skillEffect[0] = new CEffect_Claw();
	m_skillEffect[1] = new CEffect_Claw();
	m_skillEffect[2] = new CEffect_Claw();

	m_skillEffect[0]->Initialize();
	m_skillEffect[1]->Initialize();
	m_skillEffect[2]->Initialize();

	m_bTargeting = false;

	setIdNum(101);
	setStat(300, 300, 25, 10, 0);
	setArmorType(ARMOR::SKIN);

	setHit(false);

	setMonsterImage(tempBitmap);
	setMonsterShader(tempShader);
	setMonsterRedShader(hitShader);
}

int CMonster_Shoa2::skill_1()
{
	if(getMyTurn())
	{
		Stat temp = getStat();
		CCard* targetCard = CNero::getNero()->GetPartyCardWithSlot(getTarget());
		while(targetCard == NULL) {
			int targetNum = rand()%4;
			targetCard = CNero::getNero()->GetPartyCardWithSlot(targetNum);
			setTarget(targetNum);
		}
		m_bTargeting = false;
		float damage = (temp.m_atk - targetCard->getStat().m_def) * 1.00f;
		if(damage < 0) {
			damage = 0;
		}
		m_skillEffect[0]->Reset();
		m_skillEffect[0]->SetDamage(getTarget(), static_cast<int>(damage));
		CBattleManager::getBattleManager()->EffectPush(m_skillEffect[0]);
		setTurnTimer(5.0f);
		return static_cast<int>(damage);
	}
	if(!m_bTargeting)
	{
		m_bTargeting = true;
		CCard* targetCard = CNero::getNero()->GetPartyCardWithSlot(getTarget());
		while(targetCard == NULL)
		{
			int targetNum = rand()%4;
			targetCard = CNero::getNero()->GetPartyCardWithSlot(targetNum);
			setTarget(targetNum);
		}
	}
	return -100;
}

int CMonster_Shoa2::skill_2()
{
	if(getMyTurn())
	{
		Stat temp = getStat();
		CCard* targetCard = CNero::getNero()->GetPartyCardWithSlot(getTarget());
		while(targetCard == NULL) {
			int targetNum = rand()%4;
			targetCard = CNero::getNero()->GetPartyCardWithSlot(targetNum);
			setTarget(targetNum);
		}
		m_bTargeting = false;
		float damage = (temp.m_atk - targetCard->getStat().m_def) * 1.5f;
		if(damage < 0) {
			damage = 0;
		}
		m_skillEffect[1]->Reset();
		m_skillEffect[1]->SetDamage(getTarget(), static_cast<int>(damage));
		CBattleManager::getBattleManager()->EffectPush(m_skillEffect[1]);
		setTurnTimer(10.0f);
		return static_cast<int>(damage);
	}
	if(!m_bTargeting)
	{
		m_bTargeting = true;
		CCard* targetCard = CNero::getNero()->GetPartyCardWithSlot(getTarget());
		while(targetCard == NULL)
		{
			int targetNum = rand()%4;
			targetCard = CNero::getNero()->GetPartyCardWithSlot(targetNum);
			setTarget(targetNum);
		}
	}
	return -100;
}

void CMonster_Shoa2::Update()
{

}

int CMonster_Shoa2::UseSkill(int num)
{
	if(num == 0) {
		return skill_1();
	}
	else if(num == 1) {
		return skill_2();
	}
	return 0;
}