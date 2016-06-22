// ..\framework
#include "..\framework\CInput.h"
#include "..\framework\common.h"
#include "..\framework\CBitmap.h"
#include "..\framework\CTextureShader.h"

// ..\objects
#include "CObject_ScoutButton.h"

CObject_ScoutButton::CObject_ScoutButton()
{
	m_ButtonUp = NULL;
	m_ButtonDown = NULL;
	m_shader = NULL;
	m_bBtnDown = false;
	m_bBtnUp = false;
}

CObject_ScoutButton::CObject_ScoutButton(const CObject_ScoutButton& object)
{
}

CObject_ScoutButton::~CObject_ScoutButton()
{
}

void CObject_ScoutButton::Initalize(int x, int y, int z)
{
	setPosition(x, y, z);
	m_ButtonUp = new CBitmap();
	m_ButtonUp->Initialize(L"res/btn_inn.png", 0.0f, 0.0f, 1.0f, 1.0f, 0.8f, 0.8f);

	m_ButtonDown = new CBitmap();
	m_ButtonDown->Initialize(L"res/btn_inn.png", 0.0f, 0.0f, 1.0f, 1.0f, 0.8f, 0.8f);

	m_shader = new CTextureShader();
	m_shader->Initialize(NULL, NULL);
}

void CObject_ScoutButton::Shutdown()
{
	if(m_ButtonUp != NULL)
	{
		m_ButtonUp->Shutdown();
		SAFE_DELETE(m_ButtonUp);
	}

	if(m_ButtonDown != NULL)
	{
		m_ButtonDown->Shutdown();
		SAFE_DELETE(m_ButtonDown);
	}

	if(m_shader != NULL)
	{
		m_shader->Shutdown();
		SAFE_DELETE(m_shader);
	}
}

void CObject_ScoutButton::Update(CInput* input)
{
	m_input = input;
	Qusy::Point Mouse;
	Qusy::Rect Button;
	
	input->GetMousePoint(Mouse.posX, Mouse.posY);
	m_ButtonUp->GetRect(Button);

	if(Qusy::Collision(Mouse, Button))
	{
		if(input->IsLButtonDown()) {
			m_bBtnDown = true;
		}
		else if(input->IsLButtonUp())  {
			m_bBtnDown = false;
		}
	}
	else
	{
		m_bBtnDown = false;
	}
}

void CObject_ScoutButton::Render()
{
	Qusy::Position pos = getPosition();

	if(!m_bBtnDown)
	{
		m_ButtonUp->Render(pos.posX, pos.posY, pos.posZ);
		m_shader->Render(m_ButtonUp->GetTexture(), getOpacity());
	}
	else
	{
		m_ButtonDown->Render(pos.posX, pos.posY, pos.posZ);
		m_shader->Render(m_ButtonDown->GetTexture(), getOpacity());
	}
}

bool CObject_ScoutButton::IsBtnUp()
{
	Qusy::Point Mouse;
	Qusy::Rect Button;
	
	m_input->GetMousePoint(Mouse.posX, Mouse.posY);
	m_ButtonUp->GetRect(Button);

	if(Qusy::Collision(Mouse, Button))
	{
		if(m_input->IsLButtonDown()) {
			m_bBtnUp = false;
		}
		else if(m_input->IsLButtonUp())  {
			m_bBtnUp = true;
		}
	}
	else
	{
		m_bBtnUp = false;
	}

	return m_bBtnUp;
}

Qusy::Rect CObject_ScoutButton::GetButtonRect()
{
	Qusy::Rect temp;
	m_ButtonUp->GetRect(temp);
	return temp;
}