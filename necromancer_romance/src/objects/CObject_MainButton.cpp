// ..\framework
#include "..\framework\CTime.h"
#include "..\framework\CInput.h"
#include "..\framework\common.h"
#include "..\framework\CBitmap.h"
#include "..\framework\CTextureShader.h"
#include "..\framework\CSound.h"

// ..\objects
#include "CObject_MainButton.h"

CObject_MainButton::CObject_MainButton()
{
	m_start = NULL;
	m_credit = NULL;
	m_quit = NULL;
	for(int i=0; i<3; i++) {
		m_back[i] = NULL;
	}
	for(int i=0; i<6; i++) {
		m_shader[i] = NULL;
	}
	for(int i=0; i<3; i++) {
		m_bClick[i] = 0;
	}
	for(int i=0; i<3; i++) {
		m_opacity[i] = 0.0f;
	}
	m_focus = 0;
	m_bNext = false;
}

CObject_MainButton::CObject_MainButton(const CObject_MainButton& object)
{
}

CObject_MainButton::~CObject_MainButton()
{
}

void CObject_MainButton::Initalize(int x, int y, int z)
{
	setPosition(x, y, z);
	m_start = new CBitmap();
	m_start->Initialize(L"res/btn_main_start.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	m_credit = new CBitmap();
	m_credit->Initialize(L"res/btn_main_credit.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	m_quit = new CBitmap();
	m_quit->Initialize(L"res/btn_main_quit.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	for(int i=0; i<3; i++)
	{
		m_back[i] = new CBitmap();
		m_back[i]->Initialize(L"res/btn_main_back.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	}
	for(int i=0; i<6; i++) {
		m_shader[i] = new CTextureShader();
		m_shader[i]->Initialize(NULL, NULL);
	}

	for(int i=0; i<3; i++) {
		m_timer[i] = new CTime();
		m_timer[i]->SetTimer(0.0f, false);
	}
}

void CObject_MainButton::Shutdown()
{
	if(m_start != NULL)
	{
		m_start->Shutdown();
		SAFE_DELETE(m_start);
	}
	if(m_credit != NULL)
	{
		m_credit->Shutdown();
		SAFE_DELETE(m_credit);
	}
	if(m_quit != NULL)
	{
		m_quit->Shutdown();
		SAFE_DELETE(m_quit);
	}
	for(int i=0; i<3; i++)
	{
		if(m_back[i] != NULL)
		{
			m_back[i]->Shutdown();
			SAFE_DELETE(m_back[i]);
		}
	}
	for(int i=0; i<4; i++)
	{
		if(m_shader[i] != NULL)
		{
			m_shader[i]->Shutdown();
			SAFE_DELETE(m_shader[i]);
		}
	}
	for(int i=0; i<3; i++) 
	{
		if(m_timer[i] != NULL)
		{
			m_timer[i]->StopTimer();
			SAFE_DELETE(m_timer[i]);
		}
	}
}

void CObject_MainButton::Update(CInput* input)
{
	Qusy::Point mouse;
	input->GetMousePoint(mouse.posX, mouse.posY);

	Qusy::Rect btn1, btn2, btn3;

	m_start->GetRect(btn1);
	m_credit->GetRect(btn2);
	m_quit->GetRect(btn3);

	m_focus = 0;

	if(Qusy::Collision(mouse, btn1))
	{

		if((m_focus & 1) != 1) {
			m_focus += 1;
		}
		m_timer[0]->SetTimer(0.5f, false);
		
		if(input->IsLButtonUp() && m_bClick[0] == 1) {
			m_bClick[0] = 2;
		}
		else {
			m_bClick[0] = 0;
		}
		if(input->IsLButtonDown()) {
			m_bClick[0] = 1;
		}
	}
	else if(Qusy::Collision(mouse, btn2))
	{

		if((m_focus & 2) != 2) {
			m_focus += 2;
		}
		m_timer[1]->SetTimer(0.5f, false);
		
		if(input->IsLButtonUp() && m_bClick[1] == 1) {
			m_bClick[1] = 2;
		}
		else {
			m_bClick[1] = 0;
		}
		if(input->IsLButtonDown()) {
			m_bClick[1] = 1;
		}
	}
	else if(Qusy::Collision(mouse, btn3))
	{

		if((m_focus & 4) != 4) {
			m_focus += 4;
		}
		m_timer[2]->SetTimer(0.5f, false);
		
		if(input->IsLButtonUp() && m_bClick[2] == 1) {
			m_bClick[2] = 2;
		}
		else {
			m_bClick[2] = 0;
		}
		if(input->IsLButtonDown()) {
			m_bClick[2] = 1;
		}
	}
	else 
	{
	}
}

void CObject_MainButton::Render()
{
	Qusy::Position pos = getPosition();

	if(m_bNext)
	{
		for(int i=0; i<3; i++) {
			m_opacity[i] = 0.0f;
		}
	}
	else
	{
		if(!m_timer[0]->GetTimer()) {
			if((m_focus & 1) == 1) {
				m_opacity[0] = 1.0f;
			}
			else {
				m_opacity[0] = m_timer[0]->RemainTime()/m_timer[0]->GetSetTime();
			}
		}
		else {
			m_opacity[0] = 0.0f;
		}

		if(!m_timer[1]->GetTimer()) {
			if((m_focus & 2) == 2) {
				m_opacity[1] = 1.0f;
			}
			else {
				m_opacity[1] = m_timer[1]->RemainTime()/m_timer[1]->GetSetTime();
			}
		}
		else {
			m_opacity[1] = 0.0f;
		}

		if(!m_timer[2]->GetTimer()) {
			if((m_focus & 4) == 4) {
				m_opacity[2] = 1.0f;
			}
			else {
				m_opacity[2] = m_timer[2]->RemainTime()/m_timer[2]->GetSetTime();
			}
		}
		else {
			m_opacity[2] = 0.0f;
		}
	}
	

	m_back[0]->Render(pos.posX, pos.posY, pos.posZ+10);
	m_shader[3]->Render(m_back[0]->GetTexture(), m_opacity[0]);

	m_back[1]->Render(pos.posX, pos.posY+82, pos.posZ+10);
	m_shader[4]->Render(m_back[1]->GetTexture(), m_opacity[1]);

	m_back[2]->Render(pos.posX, pos.posY+164, pos.posZ+10);
	m_shader[5]->Render(m_back[2]->GetTexture(), m_opacity[2]);

	m_start->Render(pos.posX, pos.posY, pos.posZ);
	m_shader[0]->Render(m_start->GetTexture(), getOpacity());

	m_credit->Render(pos.posX, pos.posY+82, pos.posZ);
	m_shader[1]->Render(m_credit->GetTexture(), getOpacity());

	m_quit->Render(pos.posX, pos.posY+164, pos.posZ);
	m_shader[2]->Render(m_quit->GetTexture(), getOpacity());
}

int CObject_MainButton::GetClickButton()
{
	if(m_bClick[0] == 2) {
		m_bClick[0] = 0;
		m_bNext = true;
		return 1;
	}
	else if(m_bClick[1] == 2) {
		m_bClick[1] = 0;
		m_bNext = true;
		return 2;
	}
	else if(m_bClick[2] == 2) {
		m_bClick[2] = 0;
		m_bNext = true;
		return 3;
	}
	else {
		return 0;
	}
}