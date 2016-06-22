#include "..\framework\CBitmap.h"
#include "..\framework\CTextureShader.h"

#include "..\managers\CNero.h"
#include "..\managers\CSkillManager.h"
#include "..\managers\CBattleManager.h"

#include "..\objects\CSkill.h"
#include "..\objects\CMonster.h"

#include "CCard_Iron.h"
#include "CEffect_Hack.h"

CCard_Iron::CCard_Iron()
{
	Initialize();
}

CCard_Iron::~CCard_Iron()
{

}

void CCard_Iron::Initialize()
{
	m_cardImage = new CBitmap();
	m_cardShader = new CTextureShader();
	m_blackShader = new CTextureShader();
	m_sepiaShader = new CTextureShader();
	m_hitShader = new CTextureShader();
	m_turnShader = new CTextureShader();

	m_skillEffect[0] = new CEffect_Hack();
	m_skillEffect[0]->Initialize();
	m_skillEffect[1] = new CEffect_Hack();
	m_skillEffect[1]->Initialize();
	m_skillEffect[2] = new CEffect_Hack();
	m_skillEffect[2]->Initialize();

	m_cardImage->Initialize(L"res/cards/card_iron.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	m_cardShader->Initialize(NULL, NULL);
	m_blackShader->Initialize(NULL, L"shader/BlackShader.ps");
	m_sepiaShader->Initialize(NULL, L"shader/SepiaShader.ps");
	m_hitShader->Initialize(NULL, L"shader/RedShader.ps");
	m_turnShader->Initialize(NULL, L"shader/TurnShader.ps");

	WCHAR name[6] = {NULL,};
	lstrcpy(name, L"아이언");
	setCardName(name);
	setIdNum(6);
	setTeamNum(2);
	setStat(150, 0, 21, 21, 28, 9, 11);
	setType(CARDTYPE::BLUNT);
	setSpdText(L"보통");
	lstrcpy(m_skill1Name, L"스윙");
	lstrcpy(m_skill2Name, L"스미싱");
	lstrcpy(m_skill3Name, L"다이캐스팅");
	m_useAp[0] = 2;
	m_useAp[1] = 4;
	m_useAp[2] = 6;

	setHit(false);
}

void CCard_Iron::Shutdown()
{
	if(m_cardImage != NULL) {
		m_cardImage->Shutdown();
		SAFE_DELETE(m_cardImage);
	}
	if(m_cardShader != NULL) {
		m_cardShader->Shutdown();
		SAFE_DELETE(m_cardShader);
	}
	if(m_blackShader != NULL) {
		m_blackShader->Shutdown();
		SAFE_DELETE(m_blackShader);
	}
	if(m_sepiaShader != NULL) {
		m_sepiaShader->Shutdown();
		SAFE_DELETE(m_sepiaShader);
	}
	if(m_hitShader != NULL) {
		m_hitShader->Shutdown();
		SAFE_DELETE(m_hitShader);
	}
	for(int i=0; i<3; i++)
	{
		if(m_skillEffect[i] != NULL) {
			m_skillEffect[i]->Shutdown();
			SAFE_DELETE(m_skillEffect[i]);
		}
	}
}

void CCard_Iron::PowerUp()
{
	float hpRatio = (float)getStat().m_hp / (float)getStat().m_maxHp;
	float apRatio = (float)getStat().m_ap / (float)getStat().m_maxAp;
	int maxHp = getStat().m_maxHp	+ 60;
	int maxAp = getStat().m_maxAp	+ 1;
	int atk = getStat().m_atk		+ 12;
	int def = getStat().m_def		+ 2;
	int spd = getStat().m_spd;
	//int hp = (int)((float)maxHp * hpRatio);
	//int ap = (int)((float)maxAp * apRatio);
	int hp = maxHp;
	int ap = maxAp;

	setStat(maxHp, hp, maxAp, ap, atk, def, spd);
}

int CCard_Iron::skill_1()
{
	int i = 0;
	Stat temp = getStat();
	CMonster* tempMonster = CBattleManager::getBattleManager()->GetMonster();
	float damage = (temp.m_atk - tempMonster->getStat().m_def) * 1.0f;
	
	if(getStat().m_ap - m_useAp[i] >= 0) {
		setAp(getStat().m_ap - m_useAp[i]);
		
		m_skillEffect[0]->Reset();
		m_skillEffect[0]->SetDamage(1, damage);
		CBattleManager::getBattleManager()->EffectPush(m_skillEffect[0]);
		
		return static_cast<int>(damage);
	}
	else {
		return -10;
	}
}

int CCard_Iron::skill_2()
{
	int i = 1;
	Stat temp = getStat();
	CMonster* tempMonster = CBattleManager::getBattleManager()->GetMonster();
	float damage = (temp.m_atk - tempMonster->getStat().m_def) * 1.8f;

	if(getStat().m_ap - m_useAp[i] >= 0) {
		setAp(getStat().m_ap - m_useAp[i]);
		
		m_skillEffect[0]->Reset();
		m_skillEffect[0]->SetDamage(1, damage);
		CBattleManager::getBattleManager()->EffectPush(m_skillEffect[0]);
		
		return static_cast<int>(damage);
	}
	else {
		return -10;
	}
}

int CCard_Iron::skill_3()
{
	int i = 2;
	Stat temp = getStat();
	CMonster* tempMonster = CBattleManager::getBattleManager()->GetMonster();
	float damage = (temp.m_atk - tempMonster->getStat().m_def) * 2.6f;

	if(getStat().m_ap - m_useAp[i] >= 0) {
		setAp(getStat().m_ap - m_useAp[i]);
		
		m_skillEffect[0]->Reset();
		m_skillEffect[0]->SetDamage(1, damage);
		CBattleManager::getBattleManager()->EffectPush(m_skillEffect[0]);
		
		return static_cast<int>(damage);
	}
	else {
		return -10;
	}
}

int CCard_Iron::UseSkill(int num)
{
	if(num == 0) {
		int damage = skill_1();
		if(damage < 0) {
			damage = 0;
		}
		return damage;
	}
	else if(num == 1) {
		int damage = skill_2();
		if(damage < 0) {
			damage = 0;
		}
		return damage;
	}
	else if(num == 2) {
		int damage = skill_3();
		if(damage < 0) {
			damage = 0;
		}
		return damage;
	}
	return -100;
}