#ifndef _CTEXTURESHADER_H_
#define _CTEXTURESHADER_H_

enum SHADER
{
	HIT = 1,
	BLACK,
	SEPIA,
	TURN,
};

// INCLUDES //
#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>
using namespace std;


// Class name: CTextureShader
class CTextureShader
{
private:
	struct MatrixBufferType
	{
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX projection;
	};

	struct PSBufferType
	{
		float color[4];
	};

	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11Buffer* m_matrixBuffer;
	ID3D11Buffer* m_psBuffer;
	ID3D11SamplerState* m_sampleState;


	bool InitializeShader(WCHAR*, WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, float[], ID3D11ShaderResourceView*);
	void RenderShader(ID3D11DeviceContext*, int);

public:
	CTextureShader();
	CTextureShader(const CTextureShader&);
	~CTextureShader();

	bool Initialize(WCHAR*, WCHAR*);
	void Shutdown();
	
	//1 Value (alpha)
	bool Render(ID3D11ShaderResourceView*, float);

	//4 Value (float array)
	bool Render(ID3D11ShaderResourceView*, float, float, float, float);
};

#endif