#include "..\framework\CBitmap.h"
#include "..\framework\CTextureShader.h"
#include "..\framework\CTime.h"
#include "..\framework\CSound.h"

#include "CMonster.h"
#include "..\managers\CBattleManager.h"
#include "..\managers\CNero.h"

#include "CCard.h"
#include "CObject_SpeechBubble.h"
#include "CEffect_SpeechBubble.h"

CEffect_SpeechBubble::CEffect_SpeechBubble()
{
	m_speechBubble		= nullptr;
	m_effectTimer		= nullptr;
	m_sound				= nullptr;
	m_slot				= -1;
	m_cardNum			= -1;
}

CEffect_SpeechBubble::CEffect_SpeechBubble(const CEffect_SpeechBubble& eft)
{
}

CEffect_SpeechBubble::~CEffect_SpeechBubble()
{
}

void CEffect_SpeechBubble::Initialize()
{
	m_effectPos.setPosition(0, 0, 0);

	m_speechBubble = new CObject_SpeechBubble();
	m_speechBubble->Initalize(0);

	m_effectTimer = new CTime();

	m_sound = new CSound();
	m_sound->Initialize("res/sound/se/chop.wav");
	m_sound->Loop(false);

	m_slot = -1;
	m_cardNum = -1;
}

void CEffect_SpeechBubble::Shutdown()
{
	if(m_speechBubble != nullptr) {
		m_speechBubble->Shutdown();
		SAFE_DELETE(m_speechBubble);
	}

	if(m_effectTimer != nullptr) {
		SAFE_DELETE(m_effectTimer);
	}
	if(m_sound != nullptr)
	{
		m_sound->Release();
		SAFE_DELETE(m_sound);
	}
}

void CEffect_SpeechBubble::Reset(WCHAR* text)
{
	lstrcpy(m_script, text);
	m_speechBubble->Reset();
	m_effectTimer->SetTimer(0.8f, false);
}

void CEffect_SpeechBubble::SetSlot(int cardNum)	
{
	m_cardNum = cardNum;
}

void CEffect_SpeechBubble::SetDamage(int num, int totalDamage)
{
}

bool CEffect_SpeechBubble::GetAlive()
{
	return !m_effectTimer->GetTimer();
}

void CEffect_SpeechBubble::Update()
{
	for(int i=0; i<4; i++)
	{
		CCard* tempCard = CNero::getNero()->GetPartyCardWithSlot(i);
		if(tempCard->getIdNum() == m_cardNum)
		{
			m_slot = i;
			break;
		}
		else
		{
			m_slot = -1;
		}
	}

	if(m_effectTimer->RemainTime() > 0.6f)
	{
		m_speechBubble->setOpacity( 1.0f - ((m_effectTimer->RemainTime()-0.6f)/0.2f));
	}
	/*
	else if(m_effectTimer->RemainTime() < 0.2f)
	{
		m_speechBubble->setOpacity(m_effectTimer->RemainTime()/0.2f);
	}
	*/
	else
	{
		m_speechBubble->setOpacity(1.0f);
	}
}

void CEffect_SpeechBubble::Render()
{
	if(m_slot != -1) {
		m_speechBubble->Render(m_slot, m_script);
	}
}