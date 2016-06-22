#include "..\framework\CBitmap.h"
#include "..\framework\CTextureShader.h"

#include "..\managers\CNero.h"
#include "..\managers\CSkillManager.h"
#include "..\managers\CBattleManager.h"

#include "CCard.h"
#include "CEffect_Claw.h"
#include "CMonster_Wolfrider.h"

CMonster_Wolfrider::CMonster_Wolfrider()
{
}

CMonster_Wolfrider::~CMonster_Wolfrider()
{
}

void CMonster_Wolfrider::Initialize()
{
	CBitmap* tempBitmap = new CBitmap();
	CTextureShader* tempShader = new CTextureShader();
	CTextureShader* hitShader = new CTextureShader();
	tempBitmap->Initialize(L"res/monsters/monster_wolfrider.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	tempShader->Initialize(NULL, NULL);
	hitShader->Initialize(NULL, L"shader/RedShader.ps");

	m_skillEffect[0] = new CEffect_Claw();
	m_skillEffect[1] = new CEffect_Claw();
	m_skillEffect[2] = new CEffect_Claw();

	m_skillEffect[0]->Initialize();
	m_skillEffect[1]->Initialize();
	m_skillEffect[2]->Initialize();

	m_bTargeting = false;

	setIdNum(1);
	setStat(250, 250, 30, 2, 0);
	setArmorType(ARMOR::LIGHT);

	setHit(false);

	setMonsterImage(tempBitmap);
	setMonsterShader(tempShader);
	setMonsterRedShader(hitShader);
}

int CMonster_Wolfrider::skill_1()
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
		float damage = (temp.m_atk - targetCard->getStat().m_def) * 0.8f;
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

int CMonster_Wolfrider::skill_2()
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
		float damage = (temp.m_atk - targetCard->getStat().m_def) * 1.2f;
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

void CMonster_Wolfrider::Update()
{
	CCard* targetCard = CNero::getNero()->GetPartyCardWithSlot(getTarget());
	
	while (targetCard == NULL)
	{
		int targetNum = rand() % 4;
		targetCard = CNero::getNero()->GetPartyCardWithSlot(targetNum);
		setTarget(targetNum);
	}
}

int CMonster_Wolfrider::UseSkill(int num)
{
	if(num == 0) {
		return skill_1();
	}
	else if(num == 1) {
		return skill_2();
	}
	return 0;
}