#include "CObject.h"
#include "..\framework\CInput.h"

CObject::CObject()
{
	m_position.setPosition(0, 0, 0);
	m_opacity = 1.0f;
}

CObject::CObject(const CObject& object)
{
	// empty
}

CObject::~CObject()
{
	// empty
}

void CObject::Shutdown()
{
	// empty
}

void CObject::Update(CInput* input)
{
	// empty
}

void CObject::Render()
{
	// empty
}

void CObject::Render(float opacity)
{
	setOpacity(opacity);
	Render();
}

Qusy::Position CObject::getPosition()
{
	return m_position;
}

void CObject::setPosition(int x, int y, int z)
{
	m_position.setPosition(x, y, z);
}

float CObject::getOpacity()
{
	return m_opacity;
}

void CObject::setOpacity(float opacity)
{
	m_opacity = opacity;
}