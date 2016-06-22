#ifndef _CSYSTEM_H_
#define _CSYSTEM_H_


#define WIN32_LEAN_AND_MEAN

//#define DEBUG

// INCLUDES //
#include <windows.h>


// INCLUDES //
#include "CInput.h"
#include "CGraphics.h"
#include "..\..\lib\FW1FontWrapper.h"


// Class name: CSystem //
class CSystem
{
private:
	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;

	CInput* m_Input;
	CGraphics* m_Graphics;


	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();

public:
	CSystem();
	CSystem(const CSystem&);
	~CSystem();

	bool Initialize();
	void Shutdown();
	void Run();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
};


// FUNCTION PROTOTYPES //
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


// GLOBALS //
static CSystem* ApplicationHandle = 0;


#endif