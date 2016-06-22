#ifndef _CCAMERA_H_
#define _CCAMERA_H_


// INCLUDES //
#include <d3dx10math.h>


// Class name: CCamera //
class CCamera
{
private:
	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;
	D3DXMATRIX m_viewMatrix;

public:
	CCamera();
	CCamera(const CCamera&);
	~CCamera();

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);

	D3DXVECTOR3 GetPosition();
	D3DXVECTOR3 GetRotation();

	void Render();
	void GetViewMatrix(D3DXMATRIX&);
};

#endif