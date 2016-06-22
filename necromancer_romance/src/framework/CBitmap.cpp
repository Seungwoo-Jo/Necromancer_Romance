#include "CDirect3d.h"
#include "CBitmap.h"
#include "CTime.h"


CBitmap::CBitmap()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_Texture = 0;
	m_animateTimer = 0;
	m_bAnimate = false;
	m_bAnimateRepeat = true;
}


CBitmap::CBitmap(const CBitmap& other)
{
}


CBitmap::~CBitmap()
{
}


bool CBitmap::Initialize(WCHAR* textureFilename, int srcX, int srcY, int srcWidth, int srcHeight, int outputWidth, int outputHeight)
{
	bool result = true;
	D3DX11_IMAGE_INFO imageInfo;

	D3DX11GetImageInfoFromFile(textureFilename, NULL, &imageInfo, NULL);

	CDirect3D::GetDirect3D()->GetScreenSize(m_screenWidth, m_screenHeight);

	m_bitmapWidth = imageInfo.Width;
	m_bitmapHeight = imageInfo.Height;

	m_srcX1 = ((float)srcX / (float)m_bitmapWidth);
	m_srcY1 = ((float)srcY / (float)m_bitmapHeight);

	m_srcX2 = ((float)(srcWidth-srcX) / (float)m_bitmapWidth);
	m_srcY2 = ((float)(srcHeight-srcY) / (float)m_bitmapHeight);

	m_srcWidth = srcWidth;
	m_srcHeight = srcHeight;

	m_outputWidth = outputWidth;
	m_outputHeight = outputHeight;

	m_previousPosX = -1;
	m_previousPosY = -1;

	m_bAnimate = false;
	m_widthNum = 1;
	m_heightNum = 1;
	m_nowFrame = 0;

	result = InitializeBuffers(CDirect3D::GetDirect3D()->GetDevice());
	if(!result) {
		return result;
	}

	result = LoadTexture(CDirect3D::GetDirect3D()->GetDevice(), textureFilename);
	if(!result) {
		return result;
	}

	return result;
}
bool CBitmap::Initialize(WCHAR* textureFilename, float srcX1, float srcY1, float srcX2, float srcY2, int outputWidth, int outputHeight)
{
	bool result = true;
	D3DX11_IMAGE_INFO imageInfo;

	D3DX11GetImageInfoFromFile(textureFilename, NULL, &imageInfo, NULL);

	CDirect3D::GetDirect3D()->GetScreenSize(m_screenWidth, m_screenHeight);

	m_bitmapWidth = imageInfo.Width;
	m_bitmapHeight = imageInfo.Height;

	m_srcX1 = srcX1;
	m_srcY1 = srcY1;

	m_srcX2 = srcX2;
	m_srcY2 = srcY2;

	m_srcWidth = static_cast<int>((srcX2 - srcX1) * static_cast<float>(m_bitmapWidth));
	m_srcHeight = static_cast<int>((srcY2 - srcY1) * static_cast<float>(m_bitmapHeight));

	m_outputWidth = outputWidth;
	m_outputHeight = outputHeight;

	m_previousPosX = -1;
	m_previousPosY = -1;

	m_bAnimate = false;
	m_widthNum = 1;
	m_heightNum = 1;
	m_nowFrame = 0;

	result = InitializeBuffers(CDirect3D::GetDirect3D()->GetDevice());
	if(!result) {
		return result;
	}

	result = LoadTexture(CDirect3D::GetDirect3D()->GetDevice(), textureFilename);
	if(!result) {
		return result;
	}

	return result;
}
bool CBitmap::Initialize(WCHAR* textureFilename, float srcX1, float srcY1, float srcX2, float srcY2, float outputWidth, float outputHeight)
{
	bool result = true;
	D3DX11_IMAGE_INFO imageInfo;

	D3DX11GetImageInfoFromFile(textureFilename, NULL, &imageInfo, NULL);

	CDirect3D::GetDirect3D()->GetScreenSize(m_screenWidth, m_screenHeight);

	m_bitmapWidth = imageInfo.Width;
	m_bitmapHeight = imageInfo.Height;

	m_srcX1 = srcX1;
	m_srcY1 = srcY1;

	m_srcX2 = srcX2;
	m_srcY2 = srcY2;

	m_srcWidth = static_cast<int>((srcX2 - srcX1) * static_cast<float>(m_bitmapWidth));
	m_srcHeight = static_cast<int>((srcY2 - srcY1) * static_cast<float>(m_bitmapHeight));

	m_outputWidth = static_cast<int>(m_bitmapWidth * outputWidth);
	m_outputHeight = static_cast<int>(m_bitmapHeight * outputHeight);

	m_previousPosX = -1;
	m_previousPosY = -1;

	m_bAnimate = false;
	m_widthNum = 1;
	m_heightNum = 1;
	m_nowFrame = 0;

	result = InitializeBuffers(CDirect3D::GetDirect3D()->GetDevice());
	if(!result) {
		return result;
	}

	result = LoadTexture(CDirect3D::GetDirect3D()->GetDevice(), textureFilename);
	if(!result) {
		return result;
	}

	return result;
}

void CBitmap::Shutdown()
{
	if(m_bAnimate) {
		m_bAnimate = false;
		SAFE_DELETE_ARRAY(m_animationDesc);
	}

	ReleaseTexture();
	ShutdownBuffers();

	return;
}




bool CBitmap::Render(int positionX, int positionY, int positionZ)
{
	bool result = true;

	if(m_bAnimate)
	{
		if(m_animateTimer->GetTimer())
		{
			m_animateTimer->SetTimer(static_cast<float>(m_animateDelay)*0.001f, false);

			m_nowFrame++;
			if(m_nowFrame >= m_totalFrameNum) {
				if(m_bAnimateRepeat) {
					m_nowFrame = 0;
				}
				else {
					m_nowFrame = m_totalFrameNum-1;
				}
			}
		}

		m_srcX1 = m_animationDesc[m_nowFrame].m_fStartX;
		m_srcY1 = m_animationDesc[m_nowFrame].m_fStartY;
		m_srcX2 = m_animationDesc[m_nowFrame].m_fEndX;
		m_srcY2 = m_animationDesc[m_nowFrame].m_fEndY;
	}

	result = UpdateBuffers(CDirect3D::GetDirect3D()->GetDeviceContext(), positionX, positionY, positionZ);
	if(!result) {
		return result;
	}

	RenderBuffers(CDirect3D::GetDirect3D()->GetDeviceContext());

	return result;
}
bool CBitmap::Render(int positionX, int positionY, int positionZ, float WidthRatio, float HeightRatio)
{
	bool result = true;

	if(m_bAnimate)
	{
		if(m_animateTimer->GetTimer())
		{
			m_animateTimer->SetTimer(static_cast<float>(m_animateDelay)*0.001f, false);

			m_nowFrame++;
			if(m_nowFrame >= m_totalFrameNum) {
				if(m_bAnimateRepeat) {
					m_nowFrame = 0;
				}
				else {
					m_nowFrame = m_totalFrameNum-1;
				}
			}
		}

		int tempOutputWidth = m_outputWidth;
		int tempOutputHeight = m_outputHeight;

		m_srcX1 = m_animationDesc[m_nowFrame].m_fStartX;
		m_srcY1 = m_animationDesc[m_nowFrame].m_fStartY;
		m_srcX2 = m_animationDesc[m_nowFrame].m_fEndX;
		m_srcY2 = m_animationDesc[m_nowFrame].m_fEndY;

		m_outputWidth = static_cast<int>(m_outputWidth * WidthRatio);
		m_outputHeight = static_cast<int>(m_outputHeight * HeightRatio);

		result = UpdateBuffers(CDirect3D::GetDirect3D()->GetDeviceContext(), positionX, positionY, positionZ);
		if(!result) {
			return result;
		}

		RenderBuffers(CDirect3D::GetDirect3D()->GetDeviceContext());

		m_outputWidth = tempOutputWidth;
		m_outputHeight = tempOutputHeight;
	}
	else
	{
		int tempSrcWidth = m_srcWidth;
		int tempSrcHeight = m_srcHeight;
		int tempOutputWidth = m_outputWidth;
		int tempOutputHeight = m_outputHeight;

		m_srcWidth = static_cast<int>(m_srcWidth * WidthRatio);
		m_srcHeight = static_cast<int>(m_srcHeight * HeightRatio);
		m_outputWidth = static_cast<int>(m_outputWidth * WidthRatio);
		m_outputHeight = static_cast<int>(m_outputHeight * HeightRatio);

		result = UpdateBuffers(CDirect3D::GetDirect3D()->GetDeviceContext(), positionX, positionY, positionZ);
		if(!result) {
			return result;
		}

		RenderBuffers(CDirect3D::GetDirect3D()->GetDeviceContext());

		m_srcWidth = tempSrcWidth;
		m_srcHeight = tempSrcHeight;
		m_outputWidth = tempOutputWidth;
		m_outputHeight = tempOutputHeight;
	}
	return result;
}

bool CBitmap::Render(int positionX, int positionY, int positionZ, float srcX, float srcY, float WidthRatio, float HeightRatio)
{
	bool result = true;

	float tempSrcX1 = m_srcX1;
	float tempSrcX2 = m_srcX2;
	float tempSrcY1 = m_srcY1;
	float tempSrcY2 = m_srcY2;
	int tempSrcWidth = m_srcWidth;
	int tempSrcHeight = m_srcHeight;
	int tempOutputWidth = m_outputWidth;
	int tempOutputHeight = m_outputHeight;

	m_srcX1 = srcX;
	m_srcY1 = srcY;
	m_srcX2 = srcX + WidthRatio;
	m_srcY2 = srcY + HeightRatio;
	m_srcWidth = static_cast<int>(m_srcWidth * WidthRatio);
	m_srcHeight = static_cast<int>(m_srcHeight * HeightRatio);
	m_outputWidth = static_cast<int>(m_outputWidth * WidthRatio);
	m_outputHeight = static_cast<int>(m_outputHeight * HeightRatio);

	result = UpdateBuffers(CDirect3D::GetDirect3D()->GetDeviceContext(), positionX, positionY, positionZ);
	if(!result) {
		return result;
	}

	RenderBuffers(CDirect3D::GetDirect3D()->GetDeviceContext());

	m_srcX1 = tempSrcX1;
	m_srcX2 = tempSrcX2;
	m_srcY1 = tempSrcY1;
	m_srcY2 = tempSrcY2;
	m_srcWidth = tempSrcWidth;
	m_srcHeight = tempSrcHeight;
	m_outputWidth = tempOutputWidth;
	m_outputHeight = tempOutputHeight;

	return result;
}

void CBitmap::SetSpriteAnimation(int widthNum, int heightNum, int animateTime, bool repeat)
{
	m_bAnimate = true;
	m_animationDesc = new AnimationDesc[(widthNum * heightNum)];
	m_bAnimateRepeat = repeat;

	m_widthNum = widthNum;
	m_heightNum = heightNum;
	m_srcWidth = static_cast<int>(m_bitmapWidth / m_widthNum);
	m_srcHeight = static_cast<int>(m_bitmapHeight / m_heightNum);
	m_outputWidth = static_cast<int>(m_bitmapWidth / m_widthNum);
	m_outputHeight = static_cast<int>(m_bitmapHeight / m_heightNum);
	m_totalFrameNum = m_widthNum * m_heightNum;
	m_nowFrame = 0;

	double frameWidthRatio = 1.0f / m_widthNum;
	double frameHeightRatio = 1.0f / m_heightNum;

	double startX = 0.0f;
	double startY = 0.0f;
	double endX = frameWidthRatio;
	double endY = frameHeightRatio;

	int index = 0;
	for(int i=0; i<heightNum; i++) 
	{
		for(int j=0; j<widthNum; j++)
		{
			m_animationDesc[index].m_fStartX = static_cast<float>(startX);
			m_animationDesc[index].m_fStartY = static_cast<float>(startY);
			m_animationDesc[index].m_fEndX = static_cast<float>(endX);
			m_animationDesc[index].m_fEndY = static_cast<float>(endY);

			startX = endX;
			endX += frameWidthRatio;
			
			index++;
		}
		startX = 0.0f;
		endX = frameWidthRatio;
		startY = endY;
		endY += frameHeightRatio;
	}

	if(m_animateTimer == NULL) {
		m_animateTimer = new CTime();
	}
	m_animateTime = animateTime;
	m_animateDelay = static_cast<int>((float)m_animateTime / (float)m_totalFrameNum);
}
void CBitmap::AnimateReset()
{
	m_nowFrame = 0;
}

int CBitmap::GetIndexCount()
{
	return m_indexCount;
}

void CBitmap::GetRect(Qusy::Rect& rect)
{
	rect.setRect(0, 0, 0, 0);

	rect.setRect(
		m_previousPosX,
		m_previousPosY,
		m_previousPosX + m_outputWidth,
		m_previousPosY + m_outputHeight
	);
}

ID3D11ShaderResourceView* CBitmap::GetTexture()
{
	return m_Texture->GetTexture();
}

bool CBitmap::InitializeBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	int i;


	m_vertexCount = 6;

	m_indexCount = m_vertexCount;

	vertices = new VertexType[m_vertexCount];
	if(!vertices) {
		return false;
	}

	indices = new unsigned long[m_indexCount];
	if(!indices) {
		return false;
	}

	memset(vertices, 0, (sizeof(VertexType) * m_vertexCount));

	for(i=0; i<m_indexCount; i++)
	{
		indices[i] = i;
	}

    vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

    vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

    result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if(FAILED(result)){
		return false;
	}

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

    indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	delete [] vertices;
	vertices = 0;

	delete [] indices;
	indices = 0;

	return true;
}

void CBitmap::ShutdownBuffers()
{
	if(m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	if(m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}

bool CBitmap::UpdateBuffers(ID3D11DeviceContext* deviceContext, int positionX, int positionY, int positionZ)
{
	float left, right, top, bottom;
	VertexType* vertices;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	VertexType* verticesPtr;
	HRESULT result;

	
	m_previousPosX = positionX;
	m_previousPosY = positionY;

	left = (float)((m_screenWidth / 2) * -1) + (float)positionX;
	right = left + (float)m_outputWidth;
	top = (float)(m_screenHeight / 2) - (float)positionY;
	bottom = top - (float)m_outputHeight;

	vertices = new VertexType[m_vertexCount];
	if(!vertices) {
		return false;
	}

	vertices[0].position = D3DXVECTOR3(left, top, (float)positionZ);  // Top left.
	vertices[0].texture = D3DXVECTOR2(m_srcX1, m_srcY1);

	vertices[1].position = D3DXVECTOR3(right, bottom, (float)positionZ);  // Bottom right.
	vertices[1].texture = D3DXVECTOR2(m_srcX2, m_srcY2);

	vertices[2].position = D3DXVECTOR3(left, bottom, (float)positionZ);  // Bottom left.
	vertices[2].texture = D3DXVECTOR2(m_srcX1, m_srcY2);

	vertices[3].position = D3DXVECTOR3(left, top, (float)positionZ);  // Top left.
	vertices[3].texture = D3DXVECTOR2(m_srcX1, m_srcY1);

	vertices[4].position = D3DXVECTOR3(right, top, (float)positionZ);  // Top right.
	vertices[4].texture = D3DXVECTOR2(m_srcX2, m_srcY1);

	vertices[5].position = D3DXVECTOR3(right, bottom, (float)positionZ);  // Bottom right.
	vertices[5].texture = D3DXVECTOR2(m_srcX2, m_srcY2);

	result = deviceContext->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if(FAILED(result))
	{
		return false;
	}

	verticesPtr = (VertexType*)mappedResource.pData;

	memcpy(verticesPtr, (void*)vertices, (sizeof(VertexType) * m_vertexCount));

	deviceContext->Unmap(m_vertexBuffer, 0);

	delete [] vertices;
	vertices = 0;

	return true;
}

void CBitmap::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;


	stride = sizeof(VertexType); 
	offset = 0;
    
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}

bool CBitmap::LoadTexture(ID3D11Device* device, WCHAR* filename)
{
	bool result;


	m_Texture = new CTexture;
	if(!m_Texture) {
		return false;
	}

	result = m_Texture->Initialize(device, filename);
	if(!result) {
		return false;
	}

	return true;
}

void CBitmap::ReleaseTexture()
{
	if(m_Texture)
	{
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}

	return;
}