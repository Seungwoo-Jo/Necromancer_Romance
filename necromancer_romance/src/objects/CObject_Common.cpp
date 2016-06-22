// ..\framework
#include "..\framework\CInput.h"
#include "..\framework\common.h"
#include "..\framework\CBitmap.h"
#include "..\framework\CTextureShader.h"

// ..\objects
#include "CObject_Common.h"

CObject_Common::CObject_Common()
{
	m_common = NULL;
	m_shader = NULL;
}

CObject_Common::CObject_Common(const CObject_Common& object)
{
}

CObject_Common::~CObject_Common()
{
}

void CObject_Common::Initalize(int x, int y, int z, float widthRatio, float heightRatio, WCHAR* fileName)
{
	setPosition(x, y, z);
	m_common = new CBitmap();
	m_common->Initialize(fileName, 0.0f, 0.0f, 1.0f, 1.0f, widthRatio, heightRatio);

	m_shader = new CTextureShader();
	m_shader->Initialize(NULL, NULL);
}

void CObject_Common::Shutdown()
{
	if(m_common != NULL)
	{
		m_common->Shutdown();
		SAFE_DELETE(m_common);
	}

	if(m_shader != NULL)
	{
		m_shader->Shutdown();
		SAFE_DELETE(m_shader);
	}
}

void CObject_Common::Update(CInput* input)
{
	
}

void CObject_Common::Render()
{
	Qusy::Position pos = getPosition();
	m_common->Render(pos.posX, pos.posY, pos.posZ);
	m_shader->Render(m_common->GetTexture(), getOpacity());
}

Qusy::Rect CObject_Common::GetRect()
{
	Qusy::Rect temp;
	m_common->GetRect(temp);
	return temp;
}

CBitmap* CObject_Common::GetBitmap()
{
	return m_common;
}