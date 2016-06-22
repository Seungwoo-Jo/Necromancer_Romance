// ..\framework
#include "..\framework\CInput.h"
#include "..\framework\common.h"
#include "..\framework\CBitmap.h"
#include "..\framework\CTextureShader.h"

// ..\objects
#include "CObject_Background.h"

CObject_Background::CObject_Background()
{
	m_background = NULL;
	m_shader = NULL;
}

CObject_Background::CObject_Background(const CObject_Background& object)
{
}

CObject_Background::~CObject_Background()
{
}

void CObject_Background::Initalize(int x, int y, int z, WCHAR* fileName)
{
	setPosition(x, y, z);
	m_background = new CBitmap();
	m_background->Initialize(fileName, 0.0f, 0.0f, 1.0f, 1.0f, 1280, 720);

	m_shader = new CTextureShader();
	m_shader->Initialize(NULL, NULL);
}

void CObject_Background::Shutdown()
{
	if(m_background != NULL)
	{
		m_background->Shutdown();
		SAFE_DELETE(m_background);
	}

	if(m_shader != NULL)
	{
		m_shader->Shutdown();
		SAFE_DELETE(m_shader);
	}
}

void CObject_Background::Update(CInput* input)
{
	
}

void CObject_Background::Render()
{
	Qusy::Position pos = getPosition();
	m_background->Render(pos.posX, pos.posY, pos.posZ);
	m_shader->Render(m_background->GetTexture(), getOpacity());
}