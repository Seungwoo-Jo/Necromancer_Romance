// ..\framework
#include "..\framework\CInput.h"
#include "..\framework\common.h"
#include "..\framework\CBitmap.h"
#include "..\framework\CTextureShader.h"

// ..\objects
#include "CObject_StatusButton.h"

CObject_StatusButton::CObject_StatusButton()
{
	m_common = NULL;
	m_shader = NULL;
}

CObject_StatusButton::CObject_StatusButton(const CObject_StatusButton& object)
{
}

CObject_StatusButton::~CObject_StatusButton()
{
}

void CObject_StatusButton::Initalize(int x, int y, int z, float widthRatio, float heightRatio, WCHAR* fileName)
{
	setPosition(x, y, z);
	m_common = new CBitmap();
	m_common->Initialize(fileName, 0.0f, 0.0f, 1.0f, 1.0f, widthRatio, heightRatio);

	m_shader = new CTextureShader();
	m_shader->Initialize(NULL, NULL);
}

void CObject_StatusButton::Shutdown()
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

void CObject_StatusButton::Update(CInput* input)
{
	
}

void CObject_StatusButton::Render()
{
	Qusy::Position pos = getPosition();
	m_common->Render(pos.posX, pos.posY, pos.posZ);
	m_shader->Render(m_common->GetTexture(), getOpacity());
}

Qusy::Rect CObject_StatusButton::GetRect()
{
	Qusy::Rect temp;
	m_common->GetRect(temp);
	return temp;
}