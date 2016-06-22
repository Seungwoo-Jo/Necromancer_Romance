#include "..\framework\CBitmap.h"
#include "..\framework\CTextureShader.h"
#include "..\framework\CTime.h"

#include "..\managers\CBattleManager.h"
#include "..\managers\CNero.h"

#include "CMonster.h"
#include "CEffect.h"

CMonster::CMonster()
{
	m_idNum = -1;
	for(int i=0; i<3; i++)
	{
		m_skillEffect[i] = nullptr;
	}
	m_monsterImage = nullptr;
	m_monsterShader = nullptr;
	m_hitShader = nullptr;
	m_atkTimer = new CTime();
	m_remainToTimer = 0.0f;
	m_target = rand()%4;
	m_armorType = -1;
}

CMonster::CMonster(const CMonster& monster)
{
}

CMonster::~CMonster()
{
	delete m_atkTimer;
	m_atkTimer = NULL;
}

void CMonster::Initialize()
{
	//empty
}

void CMonster::Shutdown()
{
	m_idNum = -1;

	for(int i=0; i<3; i++)
	{
		if(m_skillEffect[i] != nullptr)
		{
			m_skillEffect[i]->Shutdown();
			SAFE_DELETE(m_skillEffect[i]);
		}
	}
	if(m_monsterImage != nullptr)
	{
		m_monsterImage->Shutdown();
		SAFE_DELETE(m_monsterImage);
	}
	if(m_monsterShader != nullptr)
	{
		m_monsterShader->Shutdown();
		SAFE_DELETE(m_monsterShader);
	}
	if(m_hitShader != nullptr)
	{
		m_hitShader->Shutdown();
		SAFE_DELETE(m_hitShader);
	}
	if(m_atkTimer != nullptr)
	{
		SAFE_DELETE(m_atkTimer);
	}
	m_remainToTimer = 0.0f;
	m_target = rand()%4;
	m_bHit = false;
	m_armorType = -1;
}

unsigned int CMonster::getIdNum()
{
	return m_idNum;
}

void CMonster::setIdNum(unsigned int idNum)
{
	m_idNum = idNum;
}

Stat CMonster::getStat()
{
	return m_monsterStat;
}

void CMonster::setStat(int maxHp, int hp, int atk, int def, int spd)
{
	m_monsterStat.m_maxHp	= maxHp;
	m_monsterStat.m_hp		= hp;
	m_monsterStat.m_maxAp	= 100;
	m_monsterStat.m_ap		= 0;
	m_monsterStat.m_atk		= atk;
	m_monsterStat.m_def		= def;
	m_monsterStat.m_spd		= spd;
}

void CMonster::setHp(int hp)
{
	m_monsterStat.m_hp = hp;
}

void CMonster::setAp(int ap)
{
	m_monsterStat.m_ap = ap;
}

void CMonster::Restore()
{
	Stat temp = getStat();
	setStat(temp.m_maxHp, temp.m_maxHp, temp.m_atk, temp.m_def, 0);
	setAp(0);
	m_atkTimer->StopTimer();
	m_bHit = false;
}

void CMonster::setArmorType(int type)
{
	m_armorType = type;
}

int CMonster::getArmorType()
{
	return m_armorType;
}

CBitmap* CMonster::getMonsterImage()
{
	return m_monsterImage;
}

void CMonster::setMonsterImage(CBitmap* bitmap)
{
	m_monsterImage = bitmap;
}

CTextureShader* CMonster::getMonsterShader()
{
	return m_monsterShader;
}

void CMonster::setMonsterShader(CTextureShader* shader)
{
	m_monsterShader = shader;
}

void CMonster::setMonsterRedShader(CTextureShader* shader)
{
	m_hitShader = shader;
}

void CMonster::MonsterRender(int x, int y, float widthRatio, float heightRatio, float opacity)
{
	m_monsterImage->Render(x, y, 10, widthRatio, heightRatio);
	if(m_bHit) {
		m_hitShader->Render(m_monsterImage->GetTexture(), opacity);
	}
	else {
		m_monsterShader->Render(m_monsterImage->GetTexture(), opacity);
	}
}


void CMonster::setTurnTimer(float time)
{
	m_atkTimer->SetTimer(time, false);
	m_remainToTimer = time;

	do
	{
		m_target = rand()%4;
	}
	while(CNero::getNero()->GetPartyCardWithSlot(m_target) == NULL);
}

bool CMonster::getMyTurn()
{
	return m_atkTimer->GetTimer();
}

float CMonster::getRemainToTurn()
{
	return m_atkTimer->RemainTime();
}

float CMonster::getRemainToTurnRatio()
{
	return (m_atkTimer->RemainTime() / m_atkTimer->GetSetTime());
}

bool CMonster::getHit()
{
	return m_bHit;
}

void CMonster::setHit(bool hit)
{
	m_bHit = hit;
}

void CMonster::setTarget(int slot)
{
	m_target = slot;
}

int CMonster::getTarget()
{
	return m_target;
}

void CMonster::Update()
{
	// virtual func
}

int CMonster::UseSkill(int num)
{
	return 0;
}