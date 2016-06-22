#ifndef _CDIRECT3D_H_
#define _CDIRECT3D_H_


// LINKING //
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")


// INCLUDES //
#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <d3dx10math.h>


// Class name: CDirect3d //
class CDirect3D
{
private:
	static CDirect3D* s_direct3d;

	HWND m_hwnd;
	int m_screenWidth, m_screenHeight;

	bool m_vsync_enabled;
	int m_videoCardMemory;
	char m_videoCardDescription[128];
	IDXGISwapChain* m_swapChain;
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;
	ID3D11RenderTargetView* m_renderTargetView;
	ID3D11Texture2D* m_depthStencilBuffer;
	ID3D11DepthStencilState* m_depthStencilState;
	ID3D11DepthStencilView* m_depthStencilView;
	ID3D11BlendState* m_blendState;
	ID3D11RasterizerState* m_rasterState;
	D3DXMATRIX m_projectionMatrix;
	D3DXMATRIX m_worldMatrix;
	D3DXMATRIX m_orthoMatrix;
	D3DXMATRIX m_viewMatrix;
	ID3D11DepthStencilState* m_depthDisabledStencilState;

	CDirect3D();

public:
	CDirect3D(const CDirect3D&);
	~CDirect3D();

	static CDirect3D* GetDirect3D()
	{
		if(s_direct3d == NULL) {
			s_direct3d = new CDirect3D;
		}
		return s_direct3d;
	}

	bool Initialize(int, int, bool, HWND, bool, float, float);
	void Shutdown();
	
	void BeginScene(float, float, float, float);
	void EndScene();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();

	void GetProjectionMatrix(D3DXMATRIX&);
	void GetWorldMatrix(D3DXMATRIX&);
	void GetOrthoMatrix(D3DXMATRIX&);
	void GetViewMatrix(D3DMATRIX&);
	void SetViewMatrix(D3DMATRIX);

	void GetVideoCardInfo(char*, int&);

	HWND GetHwnd();
	void GetScreenSize(int&, int&);

	void TurnZBufferOn();
	void TurnZBufferOff();
};

#endif