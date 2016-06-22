#ifndef _CBITMAP_H_
#define _CBITMAP_H_

// INCLUDES //
#include <d3d11.h>
#include <d3dx10math.h>

// INCLUDES //
#include "CTexture.h"
#include "common.h"

class CTime;

// Class name: CBitmap //
class CBitmap
{
private:
	struct VertexType 
	{
		D3DXVECTOR3 position;
	    D3DXVECTOR2 texture;
	};

	struct AnimationDesc
	{
		float m_fStartX;
		float m_fStartY;
		float m_fEndX;
		float m_fEndY;

	};

	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	CTexture* m_Texture;
	int m_screenWidth, m_screenHeight;
	float m_srcX1, m_srcY1, m_srcX2, m_srcY2;
	int m_srcWidth, m_srcHeight;
	int m_outputWidth, m_outputHeight;
	int m_bitmapWidth, m_bitmapHeight;
	int m_previousPosX, m_previousPosY;

	bool m_bAnimate;
	bool m_bAnimateRepeat;
	AnimationDesc* m_animationDesc;
	int m_widthNum, m_heightNum;
	int m_animateTime;
	int m_animateDelay;
	CTime* m_animateTimer;
	int m_totalFrameNum, m_nowFrame;

	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	bool UpdateBuffers(ID3D11DeviceContext*, int, int, int);
	void RenderBuffers(ID3D11DeviceContext*);
	bool LoadTexture(ID3D11Device*, WCHAR*);
	void ReleaseTexture();

public:
	CBitmap();
	CBitmap(const CBitmap&);
	~CBitmap();

	
	bool Initialize(WCHAR*, int, int, int, int, int, int);
	bool Initialize(WCHAR*, float, float, float, float, int, int);
	bool Initialize(WCHAR*, float, float, float, float, float, float);

	void Shutdown();

	void SetRotate(float, float, float);

	bool Render(int, int, int);
	bool Render(int, int, int, float, float);

	// Caution: No Animation
	bool Render(int, int, int, float, float, float, float);

	void SetSpriteAnimation(int widthNum, int heightNum, int animateTime, bool repeat);
	void AnimateReset();

	void GetRect(Qusy::Rect&);
	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();
};

#endif