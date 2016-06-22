#include "CTexture.h"


CTexture::CTexture()
{
	m_texture = 0;
}


CTexture::CTexture(const CTexture& other)
{
}


CTexture::~CTexture()
{
}


bool CTexture::Initialize(ID3D11Device* device, WCHAR* filename)
{
	HRESULT result;

	result = D3DX11CreateShaderResourceViewFromFile(device, filename, NULL, NULL, &m_texture, NULL);
	if(FAILED(result)) {
		return false;
	}
	return true;
}


void CTexture::Shutdown()
{
	if(m_texture)
	{
		m_texture->Release();
		m_texture = 0;
	}

	return;
}


ID3D11ShaderResourceView* CTexture::GetTexture()
{
	return m_texture;
}