#ifndef _CGRAPHICS_H_
#define _CGRAPHICS_H_


// INCLUDES //
#include "CDirect3d.h"
#include "CCamera.h"
#include "CTextureShader.h"
#include "CBitmap.h"

// GLOBALS //
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.0f;


// Class name: CGraphics //
class CGraphics
{
private:
	CDirect3D* m_D3D;
	CCamera* m_Camera;
	CTextureShader* m_TextureShader;

	bool Render();

public:
	CGraphics();
	CGraphics(const CGraphics&);
	~CGraphics();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();
};

#endif