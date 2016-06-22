// ..\framework
#include "..\framework\CInput.h"
#include "..\framework\common.h"
#include "..\framework\CBitmap.h"
#include "..\framework\CTextureShader.h"
#include "..\framework\CFont.h"

// ..\managers
#include "..\managers\CNero.h"
#include "..\managers\CBattleManager.h"

// ..\objects
#include "CObject_PartySlot.h"

CObject_PartySlot::CObject_PartySlot()
{
	m_partySlot = NULL;
	m_shader = NULL;
	m_sceneOpacity = 1.0f;
}

CObject_PartySlot::CObject_PartySlot(const CObject_PartySlot& object)
{
}

CObject_PartySlot::~CObject_PartySlot()
{
}

void CObject_PartySlot::Initalize()
{
	setPosition(0, 720-120, 50);
	m_partySlot = new CBitmap();
	m_partySlot->Initialize(L"res/card_slot.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	m_shader = new CTextureShader();
	m_shader->Initialize(NULL, NULL);

	m_text = new CFont();
	m_text->Initialize(L"10X10");
}

void CObject_PartySlot::Shutdown()
{
	if(m_partySlot != NULL)
	{
		m_partySlot->Shutdown();
		SAFE_DELETE(m_partySlot);
	}
	if(m_shader != NULL)
	{
		m_shader->Shutdown();
		SAFE_DELETE(m_shader);
	}
	if(m_text != NULL)
	{
		m_text->Shutdown();
		SAFE_DELETE(m_text);
	}
}

void CObject_PartySlot::Update(CInput* input)
{
	
}

void CObject_PartySlot::Render()
{
	Qusy::Position pos = getPosition();
	m_partySlot->Render(pos.posX, pos.posY, pos.posZ);
	m_shader->Render(m_partySlot->GetTexture(), getOpacity());

	WCHAR gold[16] = {NULL,};
	WCHAR soul[16] = {NULL,};
	WCHAR rota[16] = {NULL,};

	wsprintf(gold, L"%d", CNero::getNero()->GetGold());
	wsprintf(soul, L"%d", CNero::getNero()->GetSoul());
	wsprintf(rota, L"%d / 3", CNero::getNero()->GetRotate());

	m_text->Draw(gold, 24, pos.posX+ 106, pos.posY+ 71, GetColor(255, 255, 255, (UINT8)(getOpacity()*255.0f)), NULL);
	m_text->Draw(soul, 24, pos.posX+ 106, pos.posY+100, GetColor(255, 255, 255, (UINT8)(getOpacity()*255.0f)), NULL);
	m_text->Draw(rota, 24, pos.posX+1207, pos.posY+ 84, GetColor(255, 255, 255, (UINT8)(getOpacity()*255.0f)), NULL);
}

void CObject_PartySlot::acceptSceneOpacity(float opacity)
{
	m_sceneOpacity = opacity;
}
