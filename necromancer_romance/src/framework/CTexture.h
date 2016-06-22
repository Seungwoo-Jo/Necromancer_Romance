#ifndef _CTEXTURE_H_
#define _CTEXTURE_H_


// INCLUDES //
#include <d3d11.h>
#include <d3dx11tex.h>


// Class name: CTexture //
class CTexture
{
private:
	ID3D11ShaderResourceView* m_texture;

public:
	CTexture();
	CTexture(const CTexture&);
	~CTexture();

	bool Initialize(ID3D11Device*, WCHAR*);
	void Shutdown();

	ID3D11ShaderResourceView* GetTexture();
};

#endif