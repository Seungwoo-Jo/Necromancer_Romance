#include "..\framework\CBitmap.h"
#include "..\framework\CTextureShader.h"

#include "..\managers\CNero.h"
#include "..\managers\CSkillManager.h"
#include "..\managers\CBattleManager.h"

#include "..\objects\CSkill.h"
#include "..\objects\CMonster.h"

#include "CCard_Nero.h"
#include "CEffect_KeroseneLamp.h"
#include "CEffect_SpeechBubble.h"

CCard_Nero::CCard_Nero()
{
	Initialize();
}

CCard_Nero::~CCard_Nero()
{

}

void CCard_Nero::Initialize()
{
	m_cardImage = new CBitmap();
	m_cardShader = new CTextureShader();
	m_blackShader = new CTextureShader();
	m_sepiaShader = new CTextureShader();
	m_hitShader = new CTextureShader();
	m_turnShader = new CTextureShader();

	m_skillEffect[0] = new CEffect_KeroseneLamp();
	m_skillEffect[0]->Initialize();
	m_skillEffect[1] = new CEffect_KeroseneLamp();
	m_skillEffect[1]->Initialize();
	m_skillEffect[2] = new CEffect_KeroseneLamp();
	m_skillEffect[2]->Initialize();

	m_speechBubble = new CEffect_SpeechBubble();
	m_speechBubble->Initialize();

	m_cardImage->Initialize(L"res/cards/card_nero.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	m_cardShader->Initialize(NULL, NULL);
	m_blackShader->Initialize(NULL, L"shader/BlackShader.ps");
	m_sepiaShader->Initialize(NULL, L"shader/SepiaShader.ps");
	m_hitShader->Initialize(NULL, L"shader/RedShader.ps");
	m_turnShader->Initialize(NULL, L"shader/TurnShader.ps");

	WCHAR name[6] = {NULL,};
	lstrcpy(name, L"네로");
	setCardName(name);
	setIdNum(13);
	setTeamNum(0);
	setStat(150, 150, 20, 20, 80, 7, 10);
	setType(CARDTYPE::MAGIC);
	setSpdText(L"보통");
	lstrcpy(m_skill1Name, L"호롱불");
	lstrcpy(m_skill2Name, L"영혼 폭발");
	lstrcpy(m_skill3Name, L"재정비");
	m_useAp[0] = 3;
	m_useAp[1] = 0;
	m_useAp[2] = 0;

	setHit(false);
}

void CCard_Nero::Shutdown()
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

void CCard_Nero::PowerUp()
{
	float hpRatio = (float)getStat().m_hp / (float)getStat().m_maxHp;
	float apRatio = (float)getStat().m_ap / (float)getStat().m_maxAp;
	int maxHp = getStat().m_maxHp	+ 20;
	int maxAp = getStat().m_maxAp	+ 2;
	int atk = getStat().m_atk		+ 20;
	int def = getStat().m_def		+ 1;
	int spd = getStat().m_spd;
	//int hp = (int)((float)maxHp * hpRatio);
	//int ap = (int)((float)maxAp * apRatio);
	int hp = maxHp;
	int ap = maxAp;

	setStat(maxHp, hp, maxAp, ap, atk, def, spd);
}

int CCard_Nero::skill_1()
{
	int i = 0;
	Stat temp = getStat();
	CMonster* tempMonster = CBattleManager::getBattleManager()->GetMonster();
	float damage = (temp.m_atk - tempMonster->getStat().m_def) * 1.6f;
	
	if(getStat().m_ap - m_useAp[i] >= 0) {
		tempMonster->setAp(tempMonster->getStat().m_ap + 10);
		setAp(getStat().m_ap - m_useAp[i]);
		
		m_skillEffect[0]->Reset();
		m_skillEffect[0]->SetDamage(1, damage);
		CBattleManager::getBattleManager()->EffectPush(m_skillEffect[0]);
		
		m_speechBubble->SetSlot(getIdNum());
		m_speechBubble->Reset(L"타올라라!");
		CBattleManager::getBattleManager()->EffectPush(static_cast<CEffect*>(m_speechBubble));

		return static_cast<int>(damage);
	}
	else {
		return -10;
	}
}

int CCard_Nero::skill_2()
{
	int i = 1;
	Stat temp = getStat();
	CMonster* tempMonster = CBattleManager::getBattleManager()->GetMonster();
	float damage = (temp.m_atk) * 8.0f;

	if(CNero::getNero()->GetSoul() > 0)
	{
		CNero::getNero()->SetSoul(CNero::getNero()->GetSoul()-1);
		tempMonster->setAp(tempMonster->getStat().m_ap + 10);
		if(getStat().m_ap - m_useAp[i] >= 0)
		{
			setAp(getStat().m_ap - m_useAp[i]);
			
			m_skillEffect[1]->Reset();
			m_skillEffect[1]->SetDamage(1, damage);
			CBattleManager::getBattleManager()->EffectPush(m_skillEffect[0]);
		
			return static_cast<int>(damage);
		}
		else {
			return -10;
		}
	}
	return -10;
	
}

int CCard_Nero::skill_3()
{
	int i = 2;
	Stat temp = getStat();
	CMonster* tempMonster = CBattleManager::getBattleManager()->GetMonster();
	float damage = 1;

	if(getStat().m_ap - m_useAp[i] >= 0) {
		tempMonster->setAp(tempMonster->getStat().m_ap + 0);
		setAp(getStat().m_ap - m_useAp[i]);
		
		m_skillEffect[2]->Reset();
		m_skillEffect[2]->SetDamage(1, damage);
		CBattleManager::getBattleManager()->EffectPush(m_skillEffect[0]);
		
		return static_cast<int>(damage);
	}
	else {
		return -10;
	}
}

int CCard_Nero::UseSkill(int num)
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