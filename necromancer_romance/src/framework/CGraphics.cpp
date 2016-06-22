#include "CGraphics.h"
#include "..\managers\CSceneManager.h"

CGraphics::CGraphics()
{
	m_D3D = 0;
	m_Camera = 0;
	m_TextureShader = 0;

}


CGraphics::CGraphics(const CGraphics& other)
{
}


CGraphics::~CGraphics()
{
}


bool CGraphics::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;

	m_D3D = CDirect3D::GetDirect3D();
	if(!m_D3D) {
		return false;
	}

	

	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	m_Camera = new CCamera;
	if(!m_Camera) {
		return false;
	}

	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);

	return true;
}


void CGraphics::Shutdown()
{

	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;
}


bool CGraphics::Frame()
{
	bool result = false;

	result = Render();
	if(!result) {
		return false;
	}

	return true;
}


bool CGraphics::Render()
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	bool result = true;

	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	m_Camera->Render();

	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->SetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);

	CSceneManager::getSceneManager()->GetNowScene()->Render();

	m_D3D->EndScene();

	return result;
}