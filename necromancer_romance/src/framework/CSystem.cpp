#include <time.h>
#include "CSystem.h"
#include "..\managers\CObjectManager.h"
#include "..\managers\CSceneManager.h"
#include "..\managers\CCardManager.h"
#include "..\managers\CMonsterManager.h"
#include "..\managers\CSkillManager.h"
CSystem::CSystem()
{
	m_Input = 0;
	m_Graphics = 0;
}


CSystem::CSystem(const CSystem& other)
{
}


CSystem::~CSystem()
{
}


bool CSystem::Initialize()
{
	int screenWidth, screenHeight;
	bool result;


	screenWidth = 0;
	screenHeight = 0;

	srand((unsigned int)time(NULL));

	InitializeWindows(screenWidth, screenHeight);

	m_Graphics = new CGraphics;
	if(!m_Graphics)
	{
		return false;
	}

	result = m_Graphics->Initialize(screenWidth, screenHeight, m_hwnd);
	if(!result)
	{
		return false;
	}
	
	m_Input = new CInput;
	if(!m_Input)
	{
		return false;
	}

	m_Input->Initialize();


	CSceneManager::getSceneManager()->SetScene(SCENE::INTRO);
	CSceneManager::getSceneManager()->ChangeScene();

	return true;
}


void CSystem::Shutdown()
{
	if(m_Graphics)
	{
		m_Graphics->Shutdown();
		SAFE_DELETE(m_Graphics);
	}

	if(m_Input)
	{
		m_Input->Shutdown();
		SAFE_DELETE(m_Input);
	}

	CObjectManager::getObjectManager()->Shutdown();
	CSceneManager::getSceneManager()->Shutdown();
	CCardManager::getCardManager()->Shutdown();
	CSkillManager::getSkillManager()->Shutdown();
	CMonsterManager::getMonsterManager()->Shutdown();


	ShutdownWindows();
}


void CSystem::Run()
{
	MSG msg;
	bool done, result;

	ZeroMemory(&msg, sizeof(MSG));
	
	done = false;
	while(!done)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if(msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			result = Frame();
			if(!result)
			{
				done = true;
			}
		}
	}

	return;
}


bool CSystem::Frame()
{
	bool result = true;

	CSceneManager::getSceneManager()->GetNowScene()->Update(m_Input);
	m_Graphics->Frame();

	if(m_Input->IsDestroy()) {
		return false;
	}

	CSceneManager::getSceneManager()->ChangeScene();

	m_Input->MouseReset();
	m_Input->WheelNone();
	return result;
}


LRESULT CALLBACK CSystem::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	
	switch(umsg)
	{
		case WM_MOUSEMOVE:
			m_Input->MouseMove((unsigned int)lparam);
			return 0;

		case WM_LBUTTONDOWN:	
			m_Input->MouseMove((unsigned int)lparam);
			m_Input->LButtonDown();
			return 0;
			
		case WM_RBUTTONDOWN:
			m_Input->MouseMove((unsigned int)lparam);
			m_Input->RButtonDown();
			return 0;

		case WM_LBUTTONUP:
			m_Input->MouseMove((unsigned int)lparam);
			m_Input->LButtonUp();
			return 0;

		case WM_RBUTTONUP:
			m_Input->MouseMove((unsigned int)lparam);
			m_Input->RButtonUp();
			return 0;

		case WM_MOUSEWHEEL:
			if((SHORT)HIWORD(wparam) > 0) {
				m_Input->WheelUp();
			}
			else {
				m_Input->WheelDown();
			}
			return 0;

		case WM_KEYDOWN:
		{
			m_Input->KeyDown((unsigned int)wparam);
			return 0;
		}

		case WM_KEYUP:
		{
			m_Input->KeyUp((unsigned int)wparam);
			return 0;
		}
		default:
		{
			return DefWindowProc(hwnd, umsg, wparam, lparam);
		}
	}
}


void CSystem::InitializeWindows(int& screenWidth, int& screenHeight)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;
	RECT clSize = {0,};

	ApplicationHandle = this;

	m_hinstance = GetModuleHandle(NULL);

	m_applicationName = L"Necromancer Romance v0.35 150602";

	wc.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc   = WndProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = m_hinstance;
	wc.hIcon		 = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm       = wc.hIcon;
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize        = sizeof(WNDCLASSEX);
	
	RegisterClassEx(&wc);

	screenWidth  = 1280;
	screenHeight = 720;

	memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
	dmScreenSettings.dmSize       = sizeof(dmScreenSettings);
	dmScreenSettings.dmPelsWidth  = (unsigned long)screenWidth;
	dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
	dmScreenSettings.dmBitsPerPel = 32;			
	dmScreenSettings.dmFields     = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

	if(FULL_SCREEN)
	{
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize       = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth  = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;			
		dmScreenSettings.dmFields     = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		posX = posY = 0;
	}
	else
	{
		clSize.left = 0;
		clSize.top = 0;
		clSize.right = screenWidth;
		clSize.bottom = screenHeight;

		AdjustWindowRect(&clSize, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP, FALSE);

		posX = (GetSystemMetrics(SM_CXSCREEN) - clSize.right-clSize.left)  / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - clSize.bottom-clSize.top) / 2;
	}

	/*
#ifndef _DEBUG
	ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
	posX = posY = 0;
#endif
	*/

	int temp[2] = {clSize.right-clSize.left, clSize.bottom-clSize.top};

	m_hwnd = CreateWindowExW(NULL, m_applicationName, m_applicationName, 
						    WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
						    posX, posY, temp[0], temp[1], NULL, NULL, m_hinstance, NULL);

	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	//ShowCursor(false);

	return;
}


void CSystem::ShutdownWindows()
{
	ShowCursor(true);

	if(FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	DestroyWindow(m_hwnd);
	m_hwnd = NULL;

	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = NULL;

	ApplicationHandle = NULL;

	return;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch(umessage)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

		case WM_CLOSE:
		{
			PostQuitMessage(0);		
			return 0;
		}

		default:
		{
			return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
		}
	}
}