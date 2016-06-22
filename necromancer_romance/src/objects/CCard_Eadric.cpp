#include "..\framework\CBitmap.h"
#include "..\framework\CTextureShader.h"

#include "..\managers\CNero.h"
#include "..\managers\CSkillManager.h"
#include "..\managers\CBattleManager.h"

#include "..\objects\CSkill.h"
#include "..\objects\CMonster.h"

#include "CCard_Eadric.h"
#include "CEffect_Hack.h"
#include "CEffect_IceBoom.h"
#include "CEffect_IceArrow.h"
#include "CEffect_SpeechBubble.h"

CCard_Eadric::CCard_Eadric()
{
	Initialize();
}

CCard_Eadric::~CCard_Eadric()
{

}

void CCard_Eadric::Initialize()
{
	m_cardImage = new CBitmap();
	m_cardShader = new CTextureShader();
	m_blackShader = new CTextureShader();
	m_sepiaShader = new CTextureShader();
	m_hitShader = new CTextureShader();
	m_turnShader = new CTextureShader();

	m_skillEffect[0] = new CEffect_IceBoom();
	m_skillEffect[0]->Initialize();
	m_skillEffect[1] = new CEffect_IceArrow();
	m_skillEffect[1]->Initialize();
	m_skillEffect[2] = new CEffect_Hack();
	m_skillEffect[2]->Initialize();

	m_speechBubble = new CEffect_SpeechBubble();
	m_speechBubble->Initialize();

	m_cardImage->Initialize(L"res/cards/card_eadric.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	m_cardShader->Initialize(NULL, NULL);
	m_blackShader->Initialize(NULL, L"shader/BlackShader.ps");
	m_sepiaShader->Initialize(NULL, L"shader/SepiaShader.ps");
	m_hitShader->Initialize(NULL, L"shader/RedShader.ps");
	m_turnShader->Initialize(NULL, L"shader/TurnShader.ps");

	WCHAR name[6] = {NULL,};
	lstrcpy(name, L"에아드릭");
	setCardName(name);
	setIdNum(11);
	setTeamNum(4);
	setStat(200, 0, 28, 28, 40, 10, 12);
	setType(CARDTYPE::MAGIC);
	setSpdText(L"보통");
	lstrcpy(m_skill1Name, L"얼음 꽃");
	lstrcpy(m_skill2Name, L"서릿발");
	lstrcpy(m_skill3Name, L"한파 회오리");
	m_useAp[0] = 5;
	m_useAp[1] = 7;
	m_useAp[2] = 9;

	setHit(false);
}

void CCard_Eadric::Shutdown()
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

void CCard_Eadric::PowerUp()
{
	float hpRatio = (float)getStat().m_hp / (float)getStat().m_maxHp;
	float apRatio = (float)getStat().m_ap / (float)getStat().m_maxAp;
	int maxHp = getStat().m_maxHp	+ 20;
	int maxAp = getStat().m_maxAp	+ 3;
	int atk = getStat().m_atk		+ 17;
	int def = getStat().m_def		+ 1;
	int spd = getStat().m_spd;
	//int hp = (int)((float)maxHp * hpRatio);
	//int ap = (int)((float)maxAp * apRatio);
	int hp = maxHp;
	int ap = maxAp;

	setStat(maxHp, hp, maxAp, ap, atk, def, spd);
}

int CCard_Eadric::skill_1()
{
	int i=0;
	Stat temp = getStat();
	CMonster* tempMonster = CBattleManager::getBattleManager()->GetMonster();
	float damage = (temp.m_atk - tempMonster->getStat().m_def) * 2.0f;
	
	if(getStat().m_ap - m_useAp[0] >= 0) {
		setAp(getStat().m_ap - m_useAp[0]);
		
		m_skillEffect[0]->Reset();
		m_skillEffect[0]->SetDamage(1, damage);
		CBattleManager::getBattleManager()->EffectPush(m_skillEffect[0]);
		
		m_speechBubble->SetSlot(getIdNum());
		m_speechBubble->Reset(L"얼음 꽃");
		CBattleManager::getBattleManager()->EffectPush(static_cast<CEffect*>(m_speechBubble));

		return static_cast<int>(damage);
	}
	else {
		return -10;
	}
}

int CCard_Eadric::skill_2()
{
	int i=1;
	Stat temp = getStat();
	CMonster* tempMonster = CBattleManager::getBattleManager()->GetMonster();
	float damage = (temp.m_atk - tempMonster->getStat().m_def) * 3.0f;
	
	if(getStat().m_ap - m_useAp[i] >= 0) {
		setAp(getStat().m_ap - m_useAp[i]);
		
		m_skillEffect[1]->Reset();
		m_skillEffect[1]->SetDamage(1, damage);
		CBattleManager::getBattleManager()->EffectPush(m_skillEffect[1]);
		
		m_speechBubble->SetSlot(getIdNum());
		m_speechBubble->Reset(L"서릿발");
		CBattleManager::getBattleManager()->EffectPush(static_cast<CEffect*>(m_speechBubble));

		return static_cast<int>(damage);
	}
	else {
		return -10;
	}
}

int CCard_Eadric::skill_3()
{
	int i=2;
	Stat temp = getStat();
	CMonster* tempMonster = CBattleManager::getBattleManager()->GetMonster();
	float damage = (temp.m_atk - tempMonster->getStat().m_def) * 4.0f;
	
	if(getStat().m_ap - m_useAp[i] >= 0) {
		setAp(getStat().m_ap - m_useAp[i]);
		
		m_skillEffect[2]->Reset();
		m_skillEffect[2]->SetDamage(1, damage);
		CBattleManager::getBattleManager()->EffectPush(m_skillEffect[2]);
		
		m_speechBubble->SetSlot(getIdNum());
		m_speechBubble->Reset(L"베기!");
		CBattleManager::getBattleManager()->EffectPush(static_cast<CEffect*>(m_speechBubble));

		return static_cast<int>(damage);
	}
	else {
		return -10;
	}
}

int CCard_Eadric::UseSkill(int num)
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