#include "..\framework\CBitmap.h"
#include "..\framework\CTextureShader.h"
#include "..\framework\CTime.h"
#include "..\framework\CSound.h"

#include "CObject_Chain.h"

CObject_Chain::CObject_Chain()
{
	m_chainStart	= nullptr;
	m_chainMove		= nullptr;
	m_chainShader	= nullptr;
	m_moveTimer		= nullptr;

	m_bMove = false;

	m_sound_ChainStart = nullptr;
	m_sound_ChainMove = nullptr;
}

CObject_Chain::CObject_Chain(const CObject_Chain& obj)
{

}

CObject_Chain::~CObject_Chain()
{
	
}

void CObject_Chain::Initialize()
{
	m_chainStart = new CBitmap();
	m_chainStart->Initialize(L"res/battle/chain_start.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	m_chainStart->SetSpriteAnimation(4, 4, 650, false);

	m_chainMove = new CBitmap();
	m_chainMove->Initialize(L"res/battle/chain_move.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	m_chainMove->SetSpriteAnimation(4, 4, 525, false);

	m_chainShader = new CTextureShader();
	m_chainShader->Initialize(NULL, NULL);

	m_moveTimer = new CTime();

	m_sound_ChainStart = new CSound();
	m_sound_ChainStart->Initialize("res/sound/se/chain_start.wav");
	m_sound_ChainStart->Loop(false);

	m_sound_ChainMove = new CSound();
	m_sound_ChainMove->Initialize("res/sound/se/chain_move.wav");
	m_sound_ChainMove->Loop(false);

	setOpacity(1.0f);
}

void CObject_Chain::Shutdown()
{
	if(m_chainStart != nullptr)
	{
		m_chainStart->Shutdown();
		SAFE_DELETE(m_chainStart);
	}
	if(m_chainMove != nullptr)
	{
		m_chainMove->Shutdown();
		SAFE_DELETE(m_chainMove);
	}
	if(m_chainShader != nullptr)
	{
		m_chainShader->Shutdown();
		SAFE_DELETE(m_chainShader);
	}
}

void CObject_Chain::Update(CInput* input)
{
	if(m_moveTimer->GetTimer()) {
		m_bMove = false;
	}
}

void CObject_Chain::Render()
{	
	if(m_bMove) {
		m_chainMove->Render(0, 0, 0);
		m_chainShader->Render(m_chainMove->GetTexture(), getOpacity());
	}
	else {
		
		m_chainStart->Render(0, 0, 0);
		m_chainShader->Render(m_chainStart->GetTexture(), getOpacity());
	}
}

void CObject_Chain::Reset()
{
	if(m_bMove) {
		m_sound_ChainMove->Play();
		m_chainMove->AnimateReset();
	}
	else {
		m_sound_ChainStart->Play();
		m_chainStart->AnimateReset();
	}

	m_sound_ChainMove->Reset();
	m_sound_ChainStart->Reset();
}

void CObject_Chain::Move()
{
	
	m_bMove = true;
	m_moveTimer->SetTimer(0.5f, false);
	Reset();
}