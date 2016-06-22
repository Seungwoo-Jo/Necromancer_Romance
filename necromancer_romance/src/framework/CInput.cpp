#include <thread>
#include "CInput.h"
#include <Windows.h>
#include "CBitmap.h"
#include "CTextureShader.h"

CInput::CInput()
{
}


CInput::CInput(const CInput& other)
{
}


CInput::~CInput()
{
}


void CInput::Initialize()
{
	m_mouseX = 0;
	m_mouseY = 0;

	m_lbtDown = false;
	m_rbtDown = false;
	m_lbtUp = false;
	m_rbtUp = false;
	m_wheelMove = 0;

	for(int i=0; i<256; i++) {
		m_keys[i] = false;
	}

	m_bDestory = false;

	return;
}

void CInput::Shutdown()
{

}

void CInput::GetMousePoint(int& x, int& y)
{
	x = m_mouseX;
	y = m_mouseY;
	return;
}

void CInput::MouseReset()
{
	m_lbtUp = false;
	m_rbtUp = false;
}

void CInput::KeyReset()
{
	for(int i=0; i<256; i++) {
		m_keys[i] = false;
	}
}

void CInput::KeyDown(unsigned int input)
{
	m_keys[input] = true;
	return;
}


void CInput::KeyUp(unsigned int input)
{
	m_keys[input] = false;
	return;
}

void CInput::LButtonDown()
{
	m_lbtDown = true;
	return;
}

void CInput::RButtonDown()
{
	m_rbtDown = true;
	return;
}

void CInput::LButtonUp()
{
	m_lbtDown = false;
	m_lbtUp = true;
	return;
}

void CInput::RButtonUp()
{
	m_rbtDown = false;
	m_rbtUp = true;
	return;
}

void CInput::WheelUp()
{
	m_wheelMove = -1;
	return;
}

void CInput::WheelNone()
{
	m_wheelMove = 0;
	return;
}

void CInput::WheelDown()
{
	m_wheelMove = 1;
	return;
}

void CInput::MouseMove(unsigned int mouse)
{
	m_mouseX = LOWORD(mouse);
	m_mouseY = HIWORD(mouse);
	return;
}

bool CInput::IsKeyDown(unsigned int key)
{
	return m_keys[key];
}

bool CInput::IsLButtonDown()
{
	return m_lbtDown;
}

bool CInput::IsRButtonDown()
{
	return m_rbtDown;
}

bool CInput::IsLButtonUp()
{
	return m_lbtUp;
}

bool CInput::IsRButtonUp()
{
	return m_rbtUp;
}

bool CInput::IsWheelUp()
{
	if(m_wheelMove == -1){
		return true;
	}
	else {
		return false;
	}
}

bool CInput::IsWheelDown()
{
	if(m_wheelMove == 1){
		return true;
	}
	else {
		return false;
	}
}
void CInput::SetDestory(bool destory)
{
	m_bDestory = destory;
}

bool CInput::IsDestroy()
{
	return m_bDestory;
}