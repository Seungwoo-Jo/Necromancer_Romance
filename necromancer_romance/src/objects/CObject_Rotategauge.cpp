// ..\framework
#include "..\framework\CInput.h"
#include "..\framework\common.h"
#include "..\framework\CBitmap.h"
#include "..\framework\CTextureShader.h"
#include "..\framework\CFont.h"

// ..\objects
#include "CObject_Rotategauge.h"

CObject_Rotategauge::CObject_Rotategauge()
{
	m_barBack	= NULL;
	m_spBar		= NULL;
	for(int i=0; i<4; i++) {
		m_shader[i] = NULL;
	}
}

CObject_Rotategauge::CObject_Rotategauge(const CObject_Rotategauge& object)
{
}

CObject_Rotategauge::~CObject_Rotategauge()
{
}

void CObject_Rotategauge::Initalize()
{
	setPosition(930, 120, 10);
	m_barBack = new CBitmap();
	m_barBack->Initialize(L"res/battle/dummy_slot_gauge_back.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	m_spBar = new CBitmap();
	m_spBar->Initialize(L"res/battle/dummy_slot_gauge.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	for(int i=0; i<2; i++) 
	{
		m_shader[i] = new CTextureShader();
		m_shader[i]->Initialize(NULL, NULL);
	}
}

void CObject_Rotategauge::Shutdown()
{
	if(m_barBack != NULL)
	{
		m_barBack->Shutdown();
		SAFE_DELETE(m_barBack);
	}

	if(m_spBar != NULL)
	{
		m_spBar->Shutdown();
		SAFE_DELETE(m_spBar);
	}

	for(int i=0; i<2; i++) 
	{
		if(m_shader[i] != NULL)
		{
			m_shader[i]->Shutdown();
			SAFE_DELETE(m_shader[i]);
		}
	}
}

void CObject_Rotategauge::Update(CInput* input)
{
}

void CObject_Rotategauge::Render()
{
	Qusy::Position pos = getPosition();
	m_barBack->Render(pos.posX, pos.posY, pos.posZ, 1.0f, 1.0f);
	m_shader[0]->Render(m_barBack->GetTexture(), getOpacity());


	m_spBar->Render(pos.posX, pos.posY, pos.posZ, 1.0f-(m_remainTime/12.0f), 1.0f);
	m_shader[1]->Render(m_spBar->GetTexture(), getOpacity());

}

void CObject_Rotategauge::SetRemainTime(float remain)
{
	m_remainTime = remain;
}