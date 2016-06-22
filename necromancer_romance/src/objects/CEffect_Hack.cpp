#include "..\framework\CBitmap.h"
#include "..\framework\CTextureShader.h"
#include "..\framework\CTime.h"
#include "..\framework\CSound.h"

#include "CMonster.h"
#include "..\managers\CBattleManager.h"

#include "CObject_Num.h"
#include "CEffect_Hack.h"

CEffect_Hack::CEffect_Hack()
{
	m_effectSprite		= nullptr;
	m_effectShader		= nullptr;
	m_num				= nullptr;
	m_sustainmentTime	= 0.0f;
	m_effectTimer		= nullptr;
	m_hitTimer			= nullptr;
	m_sound				= nullptr;
	m_attackNum			= 0;
	m_attackTiming		= 0.0f;
	m_bText				= false;
	m_bAttack			= false;
}

CEffect_Hack::CEffect_Hack(const CEffect_Hack& eft)
{
}

CEffect_Hack::~CEffect_Hack()
{
}

void CEffect_Hack::Initialize()
{
	m_effectPos.setPosition(0, 0, 0);
	m_sustainmentTime = 550;
	m_attackNum = 1;
	m_attackTiming = 0.1f;
	m_damage = 0;

	m_effectSprite = new CBitmap();
	m_effectSprite->Initialize(L"res/effect/slash.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	m_effectSprite->SetSpriteAnimation(3, 2, m_sustainmentTime, false);

	m_effectShader = new CTextureShader();
	m_effectShader->Initialize(NULL, NULL);

	m_num = new CObject_Num();
	m_num->Initialize();

	m_effectTimer = new CTime();
	m_hitTimer = new CTime();

	m_sound = new CSound();
	m_sound->Initialize("res/sound/se/slash.wav");
	m_sound->Loop(false);
}

void CEffect_Hack::Shutdown()
{
	if(m_effectSprite != nullptr) {
		m_effectSprite->Shutdown();
		SAFE_DELETE(m_effectSprite);
	}
	if(m_effectShader != nullptr) {
		m_effectShader->Shutdown();
		SAFE_DELETE(m_effectShader);
	}
	if(m_num != nullptr) {
		m_num->Shutdown();
		SAFE_DELETE(m_num);
	}
	if(m_effectTimer != nullptr) {
		SAFE_DELETE(m_effectTimer);
	}
	if(m_hitTimer != nullptr) {
		SAFE_DELETE(m_effectTimer);
	}
	if(m_sound != nullptr)
	{
		m_sound->Release();
		SAFE_DELETE(m_sound);
	}
}

void CEffect_Hack::Reset()
{
	m_attackNum = 1;
	m_effectSprite->AnimateReset();
	m_effectTimer->SetTimer(static_cast<float>(m_sustainmentTime)*0.001f, false);
	m_num->setPosition(548 + (rand()%30) -15, 175 + (rand()%10) -5, m_effectPos.posZ);

	CMonster* tempMonster = CBattleManager::getBattleManager()->GetMonster();
	tempMonster->setHit(false);
	m_bText = false;
}

void CEffect_Hack::SetDamage(int num, int totalDamage)
{
	m_attackNum = num;
	m_damage = static_cast<int>(totalDamage/num);
}

bool CEffect_Hack::GetAlive()
{
	return !m_effectTimer->GetTimer();
}

void CEffect_Hack::Update()
{
	if((static_cast<float>(m_sustainmentTime)*0.001f - m_effectTimer->RemainTime()) > m_attackTiming)
	{
		if(m_attackNum >= 1) {
			m_bAttack = true;
			m_attackNum--;
		}
	}

	CMonster* tempMonster = CBattleManager::getBattleManager()->GetMonster();

	m_num->SetNum(m_damage);

	if(m_bAttack)
	{
		m_bText = true;
		m_bAttack = false;

		tempMonster = CBattleManager::getBattleManager()->GetMonster();
		tempMonster->setHp(tempMonster->getStat().m_hp - m_damage);
		if(m_damage != 0) {
			m_hitTimer->SetTimer(0.35f, false);
			tempMonster->setHit(true);
		}
	}

	if(m_hitTimer->RemainTime() >= 0.28f) {
		m_sound->Play();
		tempMonster->setHit(true);
	}
	else {
		m_sound->Reset();
		tempMonster->setHit(false);
	}
}

void CEffect_Hack::Render()
{
	m_effectSprite->Render(448, 100, m_effectPos.posZ, 2.0f, 2.0f);
	m_effectShader->Render(m_effectSprite->GetTexture(), 1.0f);

	if(m_bText)
	{
		float opacity = 1.0f;
		if(m_hitTimer->RemainTime() <= (m_hitTimer->GetSetTime() - 2.0f)) {
			opacity = m_hitTimer->RemainTime() / (m_hitTimer->GetSetTime() - 2.0f);
		}
		m_num->setPosition(m_num->getPosition().posX, m_num->getPosition().posY - 1, m_effectPos.posZ);
		m_num->setOpacity(opacity);
		m_num->Render();

		if(opacity <= 0.0f)
		{
			m_num->SetNum(0);
			m_bText = false;
		}
	}
}