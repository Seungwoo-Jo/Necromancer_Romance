#include "..\framework\CBitmap.h"
#include "..\framework\CTextureShader.h"
#include "..\framework\CTime.h"
#include "..\framework\CSound.h"

#include "CMonster.h"
#include "..\managers\CBattleManager.h"

#include "CObject_Num.h"
#include "CEffect_DrawingSword.h"

CEffect_DrawingSword::CEffect_DrawingSword()
{
	m_effectSprite[0]	= nullptr;
	m_effectSprite[1]	= nullptr;
	m_effectSprite[2]	= nullptr;
	m_effectShader[0]	= nullptr;
	m_effectShader[1]	= nullptr;
	m_num				= nullptr;
	m_sustainmentTime	= 0.0f;
	m_effectTimer		= nullptr;
	m_hitTimer			= nullptr;
	m_sound[0]			= nullptr;
	m_sound[1]			= nullptr;
	m_attackNum			= 0;
	m_attackTiming		= 0.0f;
	m_bText				= false;
	m_bAttack			= false;
}

CEffect_DrawingSword::CEffect_DrawingSword(const CEffect_DrawingSword& eft)
{
}

CEffect_DrawingSword::~CEffect_DrawingSword()
{
}

void CEffect_DrawingSword::Initialize()
{
	m_effectPos.setPosition(0, 0, 0);
	m_sustainmentTime = 1372;
	m_attackNum = 1;
	m_attackTiming = 1.0f;
	m_damage = 0;

	m_effectSprite[0] = new CBitmap();
	m_effectSprite[0]->Initialize(L"res/effect/morrighu_leaf_first.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.25f, 1.25f);
	m_effectSprite[0]->SetSpriteAnimation(5, 5, 700, false);

	m_effectSprite[1] = new CBitmap();
	m_effectSprite[1]->Initialize(L"res/effect/morrighu_leaf_last.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.00f, 1.00f);
	m_effectSprite[1]->SetSpriteAnimation(4, 4, 448, false);

	m_effectSprite[2] = new CBitmap();
	m_effectSprite[2]->Initialize(L"res/effect/morrighu_leaf_drawing.png", 0.0f, 0.0f, 1.0f, 1.0f, 2.00f, 2.00f);
	m_effectSprite[2]->SetSpriteAnimation(2, 4, 224, false);

	m_effectShader[0] = new CTextureShader();
	m_effectShader[0]->Initialize(NULL, NULL);

	m_effectShader[1] = new CTextureShader();
	m_effectShader[1]->Initialize(NULL, NULL);

	m_num = new CObject_Num();
	m_num->Initialize();

	m_effectTimer = new CTime();
	m_hitTimer = new CTime();

	m_sound[0] = new CSound();
	m_sound[0]->Initialize("res/sound/se/drawing_sword1.wav");
	m_sound[0]->Loop(false);

	m_sound[1] = new CSound();
	m_sound[1]->Initialize("res/sound/se/drawing_sword2.wav");
	m_sound[1]->Loop(false);
}

void CEffect_DrawingSword::Shutdown()
{
	for(int i=0; i<3; i++)
	{
		if(m_effectSprite[i] != nullptr) {
			m_effectSprite[i]->Shutdown();
			SAFE_DELETE(m_effectSprite[i]);
		}
	}
	for(int i=0; i<2; i++)
	{
		if(m_effectShader[i] != nullptr) {
			m_effectShader[i]->Shutdown();
			SAFE_DELETE(m_effectShader[i]);
		}
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
	if(m_sound[0] != nullptr)
	{
		m_sound[0]->Release();
		SAFE_DELETE(m_sound[0]);
	}
	if(m_sound[1] != nullptr)
	{
		m_sound[1]->Release();
		SAFE_DELETE(m_sound[1]);
	}
}

void CEffect_DrawingSword::Reset()
{
	m_attackNum = 1;
	for(int i=0; i<3; i++) {
		m_effectSprite[i]->AnimateReset();
	}
	m_effectTimer->SetTimer(static_cast<float>(m_sustainmentTime)*0.001f, false);
	m_num->setPosition(548 + (rand()%30) -15, 175 + (rand()%10) -5, m_effectPos.posZ);

	CMonster* tempMonster = CBattleManager::getBattleManager()->GetMonster();
	tempMonster->setHit(false);
	m_bText = false;
	m_sound[0]->Reset();
}

void CEffect_DrawingSword::SetDamage(int num, int totalDamage)
{
	m_attackNum = num;
	m_damage = static_cast<int>(totalDamage/num);
}

bool CEffect_DrawingSword::GetAlive()
{
	return !m_effectTimer->GetTimer();
}

void CEffect_DrawingSword::Update()
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
		m_sound[1]->Play();
		tempMonster->setHit(true);
	}
	else {
		m_sound[1]->Reset();
		tempMonster->setHit(false);
	}
}

void CEffect_DrawingSword::Render()
{
	// 베기 전
	if(m_effectTimer->RemainTime() < 1.372f && m_effectTimer->RemainTime() >= 0.672f)
	{
		m_sound[0]->Play();
		m_effectSprite[0]->Render(384, 75, m_effectPos.posZ, 1.25f, 1.25f);
		m_effectShader[0]->Render(m_effectSprite[0]->GetTexture(), 1.0f);
	}

	// 벤 후
	if(m_effectTimer->RemainTime() < 0.448f && m_effectTimer->RemainTime() >= 0.0f)
	{
		m_effectSprite[1]->Render(384, 75, m_effectPos.posZ, 1.0f, 1.0f);
		m_effectShader[0]->Render(m_effectSprite[1]->GetTexture(), 1.0f);
	}

	// 베기
	if(m_effectTimer->RemainTime() < 0.672f && m_effectTimer->RemainTime() >= 0.448f)
	{
		m_effectSprite[2]->Render(0, 50, m_effectPos.posZ, 2.0f, 2.0f);
		m_effectShader[1]->Render(m_effectSprite[2]->GetTexture(), 1.0f);
	}

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