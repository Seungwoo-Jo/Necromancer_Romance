// ..\framework
#include "..\framework\CTime.h"
#include "..\framework\CInput.h"
#include "..\framework\common.h"
#include "..\framework\CBitmap.h"
#include "..\framework\CTextureShader.h"

#include "..\managers\CBattleManager.h"

// ..\objects
#include "CMonster.h"
#include "CObject_Target.h"

CObject_Target::CObject_Target()
{
	m_targetMark = NULL;
	m_shader = NULL;
	m_spriteTimer = NULL;
	m_outputNum = 0;
}

CObject_Target::CObject_Target(const CObject_Target& object)
{
}

CObject_Target::~CObject_Target()
{
}

void CObject_Target::Initalize(int x, int y, int z)
{
	setPosition(x, y, z);
	m_targetMark = new CBitmap();
	m_targetMark->Initialize(L"res/battle/target.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	m_shader = new CTextureShader();
	m_shader->Initialize(NULL, NULL);

	m_spriteTimer = new CTime();
	m_spriteTimer->SetTimer(1.8f, true);
}

void CObject_Target::Shutdown()
{
	if(m_targetMark != NULL)
	{
		m_targetMark->Shutdown();
		SAFE_DELETE(m_targetMark);
	}
	if(m_shader != NULL)
	{
		m_shader->Shutdown();
		SAFE_DELETE(m_shader);
	}
	if(m_spriteTimer != NULL)
	{
		m_spriteTimer->StopTimer();
		SAFE_DELETE(m_spriteTimer);
	}
}

void CObject_Target::Update(CInput* input)
{
}

void CObject_Target::Render()
{
	Qusy::Position pos = getPosition();
	float opacity = 0.0f;

	opacity = sinf( (180 - (m_spriteTimer->RemainTime()*100)) * (PI/180) );

	int dy = (int)(opacity * 36.0f);
	if(dy >= 18) {
		dy = 18;
	}

	m_targetMark->Render(pos.posX, pos.posY + dy, pos.posZ);
	m_shader->Render(m_targetMark->GetTexture(), opacity);
}

void CObject_Target::setMark()
{
	setPosition(315 + (201 * CBattleManager::getBattleManager()->GetMonster()->getTarget()), 335, 7);
}