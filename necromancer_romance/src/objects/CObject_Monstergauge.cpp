// ..\framework
#include "..\framework\CInput.h"
#include "..\framework\common.h"
#include "..\framework\CBitmap.h"
#include "..\framework\CTextureShader.h"

// ..\objects
#include "CObject_Monstergauge.h"
#include "CMonster.h"

CObject_Monstergauge::CObject_Monstergauge()
{
	m_barBack	= NULL;
	m_hpBar		= NULL;
	m_spBar		= NULL;
	for(int i=0; i<4; i++) {
		m_shader[i] = NULL;
	}
	for(int i=0; i<5; i++) {
		m_type[i] = NULL;
	}
	m_typeShader = NULL;
	m_useMonster = NULL;
}

CObject_Monstergauge::CObject_Monstergauge(const CObject_Monstergauge& object)
{
}

CObject_Monstergauge::~CObject_Monstergauge()
{
}

void CObject_Monstergauge::Initalize(CMonster* monster)
{
	setPosition(207, 0, 10);
	m_barBack = new CBitmap();
	m_barBack->Initialize(L"res/battle/monster_bar_back.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	m_hpBar = new CBitmap();
	m_hpBar->Initialize(L"res/battle/monster_hp_bar.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	m_spBar = new CBitmap();
	m_spBar->Initialize(L"res/battle/monster_sp_bar.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	m_timer = new CBitmap();
	m_timer->Initialize(L"res/battle/monster_timer.png", 0.0f, 0.0f, 1.0f, 1.0f, 0.4375f, 0.4375f);

	for(int i=0; i<5; i++) {
		m_type[i] = new CBitmap();
	}

	for(int i=0; i<3; i++) 
	{
		m_shader[i] = new CTextureShader();
		m_shader[i]->Initialize(NULL, NULL);
	}

	m_shader[3] = new CTextureShader();
	m_shader[3]->Initialize(NULL, L"shader/CircleTimerShader.ps");

	m_type[ARMOR::SKIN]->Initialize(L"res/type/type_skin.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	m_type[ARMOR::LIGHT]->Initialize(L"res/type/type_light.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	m_type[ARMOR::HEAVY]->Initialize(L"res/type/type_heavy.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	m_type[ARMOR::PLATE]->Initialize(L"res/type/type_plate.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	m_type[ARMOR::SPIRIT]->Initialize(L"res/type/type_spirit.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	m_typeShader = new CTextureShader();
	m_typeShader->Initialize(NULL, NULL);

	m_useMonster = monster;
}

void CObject_Monstergauge::Shutdown()
{
	if(m_barBack != NULL)
	{
		m_barBack->Shutdown();
		SAFE_DELETE(m_barBack);
	}

	if(m_hpBar != NULL)
	{
		m_hpBar->Shutdown();
		SAFE_DELETE(m_hpBar);
	}

	if(m_spBar != NULL)
	{
		m_spBar->Shutdown();
		SAFE_DELETE(m_spBar);
	}

	for(int i=0; i<4; i++) 
	{
		if(m_shader[i] != NULL)
		{
			m_shader[i]->Shutdown();
			SAFE_DELETE(m_shader[i]);
		}
	}

	for(int i=0; i<5; i++) 
	{
		if(m_type[i] != NULL)
		{
			m_type[i]->Shutdown();
			SAFE_DELETE(m_type[i]);
		}
	}

	if(m_typeShader != NULL)
	{
		m_typeShader->Shutdown();
		SAFE_DELETE(m_typeShader);
	}

	if(m_timer != NULL)
	{
		m_timer->Shutdown();
		SAFE_DELETE(m_timer);
	}
}

void CObject_Monstergauge::Update(CInput* input)
{
}

void CObject_Monstergauge::Render()
{
	Qusy::Position pos = getPosition();
	m_barBack->Render(pos.posX, pos.posY, pos.posZ, 1.0f, 1.0f);
	m_shader[0]->Render(m_barBack->GetTexture(), getOpacity());

	float hpRatio = static_cast<float>(m_useMonster->getStat().m_hp)/static_cast<float>(m_useMonster->getStat().m_maxHp);
	m_hpBar->Render(pos.posX+112, pos.posY+41, pos.posZ, hpRatio, 1.0f);
	m_shader[1]->Render(m_hpBar->GetTexture(), getOpacity());

	float apRatio = static_cast<float>(m_useMonster->getStat().m_ap)/static_cast<float>(m_useMonster->getStat().m_maxAp);
	m_spBar->Render(pos.posX+790, pos.posY+20+(78 * (1.0f-apRatio)), pos.posZ, 0.0f, 1.0f-apRatio, 1.0f, apRatio);
	m_shader[2]->Render(m_spBar->GetTexture(), getOpacity());

	m_timer->Render(pos.posX+41, pos.posY+29, pos.posZ, 1.0f, 1.0f);
	m_shader[3]->Render(m_timer->GetTexture(), (1.0f-m_useMonster->getRemainToTurnRatio()), getOpacity(), NULL, NULL);

	m_type[m_useMonster->getArmorType()]->Render(pos.posX+790, pos.posY+20, pos.posZ-1, 1.0f, 1.0f);
	m_typeShader->Render(m_type[m_useMonster->getArmorType()]->GetTexture(), getOpacity());
}

void CObject_Monstergauge::setMonster(CMonster* monster)
{
	m_useMonster = monster;
}