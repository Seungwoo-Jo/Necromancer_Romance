// ..\framework
#include "..\framework\CInput.h"
#include "..\framework\common.h"
#include "..\framework\CBitmap.h"
#include "..\framework\CTextureShader.h"
#include "..\framework\CTime.h"

// ..\objects
#include "CObject_InnButton.h"

CObject_InnButton::CObject_InnButton()
{
	m_button = NULL;
	m_shader = NULL;
	m_notice = NULL;
	m_noticeShader = NULL;
	m_fadeTimer = NULL;
	m_bFocus = false;
	m_bClick = false;
}

CObject_InnButton::CObject_InnButton(const CObject_InnButton& object)
{
}

CObject_InnButton::~CObject_InnButton()
{
}

void CObject_InnButton::Initalize(int x, int y, int z)
{
	setPosition(x, y, z);

	m_button = new CBitmap();
	m_button->Initialize(L"res/select_inn.png", 0.0f, 0.0f, 1.0f, 1.0f, 4.0f, 4.0f);

	m_shader = new CTextureShader();
	m_shader->Initialize(NULL, NULL);

	m_notice = new CBitmap();
	m_notice->Initialize(L"res/town_inn_name.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	m_noticeShader = new CTextureShader();
	m_noticeShader->Initialize(NULL, NULL);

	m_fadeTimer = new CTime();
}

void CObject_InnButton::Shutdown()
{
	if(m_button != NULL)
	{
		m_button->Shutdown();
		SAFE_DELETE(m_button);
	}
	if(m_notice != NULL)
	{
		m_notice->Shutdown();
		SAFE_DELETE(m_notice);
	}
	if(m_shader != NULL)
	{
		m_shader->Shutdown();
		SAFE_DELETE(m_shader);
	}
	if(m_noticeShader != NULL)
	{
		m_noticeShader->Shutdown();
		SAFE_DELETE(m_noticeShader);
	}
	if(m_fadeTimer != NULL)
	{
		SAFE_DELETE(m_fadeTimer);
	}
}

void CObject_InnButton::Update(CInput* input)
{
	m_input = input;
	Qusy::Point Mouse;
	Qusy::Rect Button[2];
	
	input->GetMousePoint(Mouse.posX, Mouse.posY);
	Button[0].setRect(335, 200, 570, 420);
	Button[1].setRect(335, 421, 650, 640);

	if(Qusy::Collision(Mouse, Button[0]) || Qusy::Collision(Mouse, Button[1]))
	{
		m_bFocus = true;
		m_fadeTimer->SetTimer(0.4f, false);

		if(input->IsLButtonUp())  {
			m_bClick = true;
		}
	}
	else
	{
		m_bFocus = false;
		m_bClick = false;
	}
}

void CObject_InnButton::Render()
{
	Qusy::Position pos = getPosition();

	m_button->Render(0, 0, pos.posZ);
	
	if(m_bFocus)
	{
		m_shader->Render(m_button->GetTexture(), getOpacity());

		m_notice->Render(320, 50, pos.posZ);
		m_noticeShader->Render(m_notice->GetTexture(), getOpacity());
	}
	else
	{
		m_shader->Render(m_button->GetTexture(), (m_fadeTimer->RemainTime()/m_fadeTimer->GetSetTime()) );

		m_notice->Render(320, 50, pos.posZ);
		m_noticeShader->Render(m_notice->GetTexture(), (m_fadeTimer->RemainTime()/m_fadeTimer->GetSetTime()) );
	}
}

bool CObject_InnButton::IsBtnUp()
{
	if(m_bFocus) {
		return m_bClick;
	}
	else {
		return false;
	}
}

Qusy::Rect CObject_InnButton::GetButtonRect()
{
	Qusy::Rect temp;
	return temp;
}