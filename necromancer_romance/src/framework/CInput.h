#ifndef _CINPUT_H_
#define _CINPUT_H_

class CBitmap;
class CTextureShader;

// Class name: CInput //
class CInput
{
private:
	bool m_keys[256];
	int m_mouseX, m_mouseY;
	bool m_lbtDown, m_rbtDown;
	bool m_lbtUp, m_rbtUp;
	int m_wheelMove; // -1: up, 0: none, 1: down
	
	bool m_bDestory;

public:
	CInput();
	CInput(const CInput&);
	~CInput();

	void Initialize();
	void Shutdown();

	void GetMousePoint(int&, int&);
	void MouseReset();

	
	void KeyReset();
	void KeyDown(unsigned int);
	void KeyUp(unsigned int);
	void LButtonDown();
	void RButtonDown();
	void LButtonUp();
	void RButtonUp();

	void WheelUp();
	void WheelNone();
	void WheelDown();

	void MouseMove(unsigned int);
	bool IsLButtonDown();
	bool IsRButtonDown();
	bool IsLButtonUp();
	bool IsRButtonUp();
	bool IsWheelUp();
	bool IsWheelDown();

	bool IsKeyDown(unsigned int);

	void SetDestory(bool);
	bool IsDestroy();
};

#endif