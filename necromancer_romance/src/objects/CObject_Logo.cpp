#include "..\framework\CInput.h"
#include "..\framework\common.h"
#include "..\framework\CBitmap.h"
#include "..\framework\CTextureShader.h"
#include "CObject_Logo.h"

CObject_Logo::CObject_Logo()
{
	m_logo = NULL;
	m_shader = NULL;
}

CObject_Logo::CObject_Logo(const CObject_Logo& object)
{
}

CObject_Logo::~CObject_Logo()
{
}

void CObject_Logo::Initalize(int x, int y, int z)
{
	setPosition(x, y, z);
	m_logo = new CBitmap();
	m_logo->Initialize(L"res/intro_logo.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f); // 541 351

	m_shader = new CTextureShader();
	m_shader->Initialize(NULL, NULL);
}

void CObject_Logo::Shutdown()
{
	if(m_logo != NULL)
	{
		m_logo->Shutdown();
		SAFE_DELETE(m_logo);
	}

	if(m_shader != NULL)
	{
		m_shader->Shutdown();
		SAFE_DELETE(m_shader);
	}
}

void CObject_Logo::Update(CInput* input)
{

}

void CObject_Logo::Render()
{
	Qusy::Position pos = getPosition();
	m_logo->Render(pos.posX, pos.posY, pos.posZ);
	m_shader->Render(m_logo->GetTexture(), getOpacity());
}