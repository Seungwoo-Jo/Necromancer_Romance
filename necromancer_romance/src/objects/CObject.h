#ifndef _COBJECT_H_
#define _COBJECT_H_

#include "..\framework\common.h"

class CInput;

// Class name: CObject //
class CObject
{
private:
	Qusy::Position m_position;
	float m_opacity;

public:
	CObject();
	CObject(const CObject&);
	~CObject();

	virtual void Shutdown();
	virtual void Update(CInput*);
	virtual void Render();
	virtual void Render(float);

	Qusy::Position getPosition();
	void setPosition(int, int, int);

	float getOpacity();
	void setOpacity(float);
};

#endif