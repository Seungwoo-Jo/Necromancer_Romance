// ..\framework
#include "..\framework\CInput.h"
#include "..\framework\common.h"
#include "..\framework\CBitmap.h"
#include "..\framework\CTextureShader.h"
#include "..\framework\CFont.h"

// ..\managers
#include "..\managers\CNero.h"

// ..\objects
#include "CObject_Cardgauge.h"
#include "CCard.h"

CObject_Cardgauge::CObject_Cardgauge()
{
	m_hpBar		= NULL;
	m_shader[0] = NULL;
	m_shader[1] = NULL;
	m_hpText	= NULL;
	m_apText	= NULL;
	m_useCard	= NULL;
}

CObject_Cardgauge::CObject_Cardgauge(const CObject_Cardgauge& object)
{
}

CObject_Cardgauge::~CObject_Cardgauge()
{
}

void CObject_Cardgauge::Initalize(CCard* card)
{
	if(card != NULL) {
		int x, y;
		card->getCardPosition(x, y);
		setPosition(x, y, 10);
	}

	m_hpBar = new CBitmap();
	m_hpBar->Initialize(L"res/battle/card_hp_bar.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	m_shader[0] = new CTextureShader();
	m_shader[0]->Initialize(NULL, NULL);

	m_shader[1] = new CTextureShader();
	m_shader[1]->Initialize(NULL, NULL);

	m_useCard = card;

	m_hpText = new CFont();
	m_hpText->Initialize(L"HY¿ï¸ªµµB");

	m_apText = new CFont();
	m_apText->Initialize(L"10X10");
}

void CObject_Cardgauge::Shutdown()
{
	if(m_hpBar != NULL)
	{
		m_hpBar->Shutdown();
		SAFE_DELETE(m_hpBar);
	}

	if(m_shader[0] != NULL)
	{
		m_shader[0]->Shutdown();
		SAFE_DELETE(m_shader[0]);
	}

	if(m_shader[1] != NULL)
	{
		m_shader[1]->Shutdown();
		SAFE_DELETE(m_shader[1]);
	}
	if(m_hpText != NULL)
	{
		m_hpText->Shutdown();
		SAFE_DELETE(m_hpText);
	}
	if(m_apText != NULL)
	{
		m_apText->Shutdown();
		SAFE_DELETE(m_apText);
	}
}

void CObject_Cardgauge::Update(CInput* input)
{
	if(m_useCard != NULL)
	{
		int x, y;
		m_useCard->getCardPosition(x, y);
		setPosition(x, y, 10);

		if(m_useCard->getStat().m_hp < 0) {
			m_useCard->setHp(0);
		}
	}
}

void CObject_Cardgauge::Render()
{
	if(m_useCard != NULL) 
	{
		Qusy::Position pos = getPosition();
		
		float hpRatio = static_cast<float>(m_useCard->getStat().m_hp)/static_cast<float>(m_useCard->getStat().m_maxHp);
		m_hpBar->Render(pos.posX+7, pos.posY+136, pos.posZ, hpRatio, 1.0f);
		m_shader[0]->Render(m_hpBar->GetTexture(), getOpacity());

		WCHAR hp[7] = {NULL,};	wsprintf(hp, L"%d", m_useCard->getStat().m_hp);
		m_hpText->Draw(hp, 17.0f, pos.posX+40, pos.posY+118, GetColor(200, 200, 200, (UINT8)(255*getOpacity())), NULL);

		WCHAR ap[7] = {NULL,};	wsprintf(ap, L"%d", m_useCard->getStat().m_ap);
		m_apText->Draw(ap, 25.0f, pos.posX+74, pos.posY+157, GetColor(255, 255, 255, (UINT8)(255*getOpacity())), NULL);

		WCHAR maxAp[7] = {NULL,}; wsprintf(maxAp, L"%d", m_useCard->getStat().m_maxAp);
		m_apText->Draw(maxAp, 25.0f, pos.posX+118, pos.posY+157, GetColor(255, 255, 255, (UINT8)(255*getOpacity())), NULL);
	}
}

void CObject_Cardgauge::Render(int cardWidth, int cardHeight)
{
	float XRatio = (float)cardWidth/(float)CARD_WIDTH;
	float YRatio = (float)cardHeight/(float)CARD_HEIGHT;

	if(m_useCard != NULL)
	{
		Qusy::Position pos = getPosition();
		
		float hpRatio = static_cast<float>(m_useCard->getStat().m_hp)/static_cast<float>(m_useCard->getStat().m_maxHp);
		m_hpBar->Render(pos.posX+(int)(7*XRatio), pos.posY+(int)(136*YRatio), pos.posZ-1, XRatio*hpRatio, YRatio);
		m_shader[0]->Render(m_hpBar->GetTexture(), getOpacity());

		WCHAR hp[7] = {NULL,};	wsprintf(hp, L"%d", m_useCard->getStat().m_hp);
		m_hpText->Draw(hp, (16.0f*XRatio), pos.posX+(57.0f*XRatio), pos.posY+(120.0f*YRatio), GetColor(0, 0, 0, (UINT8)(180*getOpacity())), NULL);
		m_hpText->Draw(hp, (16.0f*XRatio), pos.posX+(57.0f*XRatio), pos.posY+(119.0f*YRatio), GetColor(50, 255, 50, (UINT8)(220*getOpacity())), NULL);

		WCHAR ap[7] = {NULL,};	wsprintf(ap, L"%d", m_useCard->getStat().m_ap);
		m_apText->Draw(ap, (24.0f*XRatio), pos.posX+(74.0f*XRatio), pos.posY+(158.0f*YRatio), GetColor(255, 255, 255, (UINT8)(255*getOpacity())), NULL);

		WCHAR maxAp[7] = {NULL,}; wsprintf(maxAp, L"%d", m_useCard->getStat().m_maxAp);
		m_apText->Draw(maxAp, (24.0f*XRatio), pos.posX+(121.0f*XRatio), pos.posY+(158.0f*YRatio), GetColor(255, 255, 255, (UINT8)(255*getOpacity())), NULL);
	}
}

void CObject_Cardgauge::SetCard(CCard* card)
{
	int x, y;
	card->getCardPosition(x, y);
	setPosition(x, y, 10);

	m_useCard = card;
}