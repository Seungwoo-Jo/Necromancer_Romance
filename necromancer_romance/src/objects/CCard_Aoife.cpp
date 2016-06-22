#include "..\framework\CBitmap.h"
#include "..\framework\CTextureShader.h"

#include "..\managers\CNero.h"
#include "..\managers\CSkillManager.h"
#include "..\managers\CBattleManager.h"

#include "..\objects\CSkill.h"
#include "..\objects\CMonster.h"

#include "CCard_Aoife.h"
#include "CEffect_Hack.h"
#include "CEffect_Chop.h"
#include "CEffect_SpeechBubble.h"

CCard_Aoife::CCard_Aoife()
{
	Initialize();
}

CCard_Aoife::~CCard_Aoife()
{

}

void CCard_Aoife::Initialize()
{
	m_cardImage = new CBitmap();
	m_cardShader = new CTextureShader();
	m_blackShader = new CTextureShader();
	m_sepiaShader = new CTextureShader();
	m_hitShader = new CTextureShader();
	m_turnShader = new CTextureShader();

	m_skillEffect[0] = new CEffect_Chop();
	m_skillEffect[0]->Initialize();
	m_skillEffect[1] = new CEffect_Hack();
	m_skillEffect[1]->Initialize();
	m_skillEffect[2] = new CEffect_Hack();
	m_skillEffect[2]->Initialize();

	m_speechBubble = new CEffect_SpeechBubble();
	m_speechBubble->Initialize();

	m_cardImage->Initialize(L"res/cards/card_aoife.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	m_cardShader->Initialize(NULL, NULL);
	m_blackShader->Initialize(NULL, L"shader/BlackShader.ps");
	m_sepiaShader->Initialize(NULL, L"shader/SepiaShader.ps");
	m_hitShader->Initialize(NULL, L"shader/RedShader.ps");
	m_turnShader->Initialize(NULL, L"shader/TurnShader.ps");

	WCHAR name[6] = {NULL,};
	lstrcpy(name, L"아이페");
	setCardName(name);
	setIdNum(9);
	setTeamNum(3);
	setStat(250, 0, 17, 17, 50, 12, 15);
	setType(CARDTYPE::SPEAR);
	setSpdText(L"느림");
	lstrcpy(m_skill1Name, L"내려 찍기");
	lstrcpy(m_skill2Name, L"집중");
	lstrcpy(m_skill3Name, L"결투");
	m_useAp[0] = 2;
	m_useAp[1] = 5;
	m_useAp[2] = 8;

	setHit(false);
}

void CCard_Aoife::Shutdown()
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

void CCard_Aoife::PowerUp()
{
	float hpRatio = (float)getStat().m_hp / (float)getStat().m_maxHp;
	float apRatio = (float)getStat().m_ap / (float)getStat().m_maxAp;
	int maxHp = getStat().m_maxHp	+ 45;
	int maxAp = getStat().m_maxAp	+ 1;
	int atk = getStat().m_atk		+ 18;
	int def = getStat().m_def		+ 4;
	int spd = getStat().m_spd;
	//int hp = (int)((float)maxHp * hpRatio);
	//int ap = (int)((float)maxAp * apRatio);
	int hp = maxHp;
	int ap = maxAp;


	setStat(maxHp, hp, maxAp, ap, atk, def, spd);
}

int CCard_Aoife::skill_1()
{
	int i = 0;
	Stat temp = getStat();
	CMonster* tempMonster = CBattleManager::getBattleManager()->GetMonster();
	float damage = (temp.m_atk - tempMonster->getStat().m_def) * 1.1f;
	
	if(getStat().m_ap - m_useAp[0] >= 0) {
		setAp(getStat().m_ap - m_useAp[0]);
		
		m_skillEffect[0]->Reset();
		m_skillEffect[0]->SetDamage(1, damage);
		CBattleManager::getBattleManager()->EffectPush(m_skillEffect[0]);
		
		m_speechBubble->SetSlot(getIdNum());
		m_speechBubble->Reset(L"야호!!!");
		CBattleManager::getBattleManager()->EffectPush(static_cast<CEffect*>(m_speechBubble));

		return static_cast<int>(damage);
	}
	else {
		return -10;
	}
}

int CCard_Aoife::skill_2()
{
	int i = 1;
	Stat temp = getStat();
	CMonster* tempMonster = CBattleManager::getBattleManager()->GetMonster();
	float damage = (temp.m_atk - tempMonster->getStat().m_def) * 1.7f;
	
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

int CCard_Aoife::skill_3()
{
	int i = 2;
	Stat temp = getStat();
	CMonster* tempMonster = CBattleManager::getBattleManager()->GetMonster();
	float damage = (temp.m_atk - tempMonster->getStat().m_def) * 2.3f;
	tempMonster->setAp(tempMonster->getStat().m_ap + 80);
	if(getStat().m_ap - m_useAp[i] >= 0) {
		setAp(getStat().m_ap - m_useAp[i]);
		
		//m_skillEffect[0]->Reset();
		//m_skillEffect[0]->SetDamage(1, damage);
		//CBattleManager::getBattleManager()->EffectPush(m_skillEffect[0]);
		
		return static_cast<int>(damage);
	}
	else {
		return -10;
	}
}

int CCard_Aoife::UseSkill(int num)
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