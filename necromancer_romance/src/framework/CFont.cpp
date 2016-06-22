#include "CDirect3d.h"
#include "CFont.h"

CFont::CFont()
{
	m_pFW1Factory = NULL;
	m_pWrapper = NULL;
}

CFont::CFont(const CFont& temp)
{
}

CFont::~CFont()
{
}

bool CFont::Initialize(LPCWSTR fontName)
{
	FW1CreateFactory(FW1_VERSION, &m_pFW1Factory);
	m_pFW1Factory->CreateFontWrapper(CDirect3D::GetDirect3D()->GetDevice(), fontName, &m_pWrapper);
	return true;
}

bool CFont::Shutdown()
{
	if(!m_pWrapper)
	{
		m_pWrapper->Release();
		m_pWrapper = NULL;
	}

	if(!m_pFW1Factory)
	{
		m_pFW1Factory->Release();
		m_pFW1Factory = NULL;
	}
	return true;
}

bool CFont::SetFont(LPCWSTR fontName)
{
	if(m_pFW1Factory) {
		return false;
	}
	if(!m_pWrapper) {
		m_pWrapper->Release();
	}
	m_pFW1Factory->CreateFontWrapper(CDirect3D::GetDirect3D()->GetDevice(), fontName, &m_pWrapper);
	return true;
}

bool CFont::Draw(WCHAR* text, float size, float x, float y, UINT32 color, UINT flag)
{
	if(flag == NULL) {
		flag = FW1_CENTER|FW1_VCENTER;
	}

	flag = flag|FW1_NOGEOMETRYSHADER;

	m_pWrapper->DrawString(CDirect3D::GetDirect3D()->GetDeviceContext(), text, size, x, y, color, flag);
	return true;
}

UINT32 GetColor(UINT8 red, UINT8 green, UINT8 blue, UINT8 alpha)
{
	UINT32 color = 0;

	color =  color		 + alpha;
	color = (color << 8) + blue;
	color = (color << 8) + green;
	color = (color << 8) + red;

	return color;
}