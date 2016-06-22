#include "CDirect3d.h"
#include "CTextureShader.h"


CTextureShader::CTextureShader()
{
	m_vertexShader = 0;
	m_pixelShader = 0;
	m_layout = 0;
	m_matrixBuffer = 0;
	m_psBuffer = 0;
	m_sampleState = 0;
}


CTextureShader::CTextureShader(const CTextureShader& other)
{
}


CTextureShader::~CTextureShader()
{
}


bool CTextureShader::Initialize(WCHAR* vsFilename, WCHAR* psFilename)
{
	bool result;

	result = InitializeShader(vsFilename, psFilename);
	if(!result)
	{
		return false;
	}

	return true;
}


void CTextureShader::Shutdown()
{
	ShutdownShader();

	return;
}

/* 원본
bool CTextureShader::Render(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
								D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* texture)
{
	bool result;


	result = SetShaderParameters(deviceContext, worldMatrix, viewMatrix, projectionMatrix, texture);
	if(!result)
	{
		return false;
	}

	RenderShader(deviceContext, indexCount);

	return true;
}
*/
// 수정본
bool CTextureShader::Render(ID3D11ShaderResourceView* texture, float alpha = 0.0f)
{
	bool result;
	D3DXMATRIX worldMatrix, viewMatrix, orthoMatrix;

	CDirect3D::GetDirect3D()->GetWorldMatrix(worldMatrix);
	CDirect3D::GetDirect3D()->GetViewMatrix(viewMatrix);
	CDirect3D::GetDirect3D()->GetOrthoMatrix(orthoMatrix);

	float valueArray[4] = {alpha, alpha, alpha, alpha};

	result = SetShaderParameters(CDirect3D::GetDirect3D()->GetDeviceContext(), worldMatrix, viewMatrix, orthoMatrix, valueArray, texture);
	if(!result) {
		return false;
	}

	RenderShader(CDirect3D::GetDirect3D()->GetDeviceContext(), 6);

	return true;
}

bool CTextureShader::Render(ID3D11ShaderResourceView* texture, float value0, float value1, float value2, float value3)
{
	bool result;
	D3DXMATRIX worldMatrix, viewMatrix, orthoMatrix;

	CDirect3D::GetDirect3D()->GetWorldMatrix(worldMatrix);
	CDirect3D::GetDirect3D()->GetViewMatrix(viewMatrix);
	CDirect3D::GetDirect3D()->GetOrthoMatrix(orthoMatrix);

	float valueArray[4] = {value0, value1, value2, value3};

	result = SetShaderParameters(CDirect3D::GetDirect3D()->GetDeviceContext(), worldMatrix, viewMatrix, orthoMatrix, valueArray, texture);
	if(!result) {
		return false;
	}

	RenderShader(CDirect3D::GetDirect3D()->GetDeviceContext(), 6);

	return true;
}

bool CTextureShader::InitializeShader(WCHAR* vsFilename, WCHAR* psFilename)
{
	HRESULT result;
	ID3D10Blob* errorMessage;
	ID3D10Blob* vertexShaderBuffer;
	ID3D10Blob* pixelShaderBuffer;
	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
	unsigned int numElements;
	D3D11_BUFFER_DESC matrixBufferDesc;
    D3D11_SAMPLER_DESC samplerDesc;


	errorMessage = 0;
	vertexShaderBuffer = 0;
	pixelShaderBuffer = 0;

	vsFilename = L"shader/texture.vs";
	if(psFilename == NULL) {
		psFilename = L"shader/texture.ps";
	}

	result = D3DX11CompileFromFile(vsFilename, NULL, NULL, "TextureVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, 
								   &vertexShaderBuffer, &errorMessage, NULL);
	if(FAILED(result))
	{
		if(errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, CDirect3D::GetDirect3D()->GetHwnd(), vsFilename);
		}
		else
		{
			MessageBox(CDirect3D::GetDirect3D()->GetHwnd(), vsFilename, L"Missing Shader File", MB_OK);
		}

		return false;
	}

	result = D3DX11CompileFromFileW(psFilename, NULL, NULL, "TexturePixelShader", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, 
								   &pixelShaderBuffer, &errorMessage, NULL);
	if(FAILED(result))
	{
		if(errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, CDirect3D::GetDirect3D()->GetHwnd(), psFilename);
		}
		else
		{
			MessageBox(CDirect3D::GetDirect3D()->GetHwnd(), psFilename, L"Missing Shader File", MB_OK);
		}

		return false;
	}

    result = CDirect3D::GetDirect3D()->GetDevice()->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_vertexShader);
	if(FAILED(result)) {
		return false;
	}
	
    result = CDirect3D::GetDirect3D()->GetDevice()->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_pixelShader);
	if(FAILED(result)) {
		return false;
	}

	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "TEXCOORD";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

    numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	result = CDirect3D::GetDirect3D()->GetDevice()->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), 
		                               &m_layout);
	if(FAILED(result))
	{
		return false;
	}

	vertexShaderBuffer->Release();
	vertexShaderBuffer = 0;

	pixelShaderBuffer->Release();
	pixelShaderBuffer = 0;

    matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
    matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	result = CDirect3D::GetDirect3D()->GetDevice()->CreateBuffer(&matrixBufferDesc, NULL, &m_matrixBuffer);

	matrixBufferDesc.ByteWidth = sizeof(PSBufferType);
	result = CDirect3D::GetDirect3D()->GetDevice()->CreateBuffer(&matrixBufferDesc, NULL, &m_psBuffer);
	if(FAILED(result))
	{
		return false;
	}

    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.MipLODBias = 0.0f;
    samplerDesc.MaxAnisotropy = 1;
    samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
    samplerDesc.BorderColor[0] = 0.0f;
	samplerDesc.BorderColor[1] = 0.0f;
	samplerDesc.BorderColor[2] = 0.0f;
	samplerDesc.BorderColor[3] = 0.0f;
    samplerDesc.MinLOD = 0;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

    result = CDirect3D::GetDirect3D()->GetDevice()->CreateSamplerState(&samplerDesc, &m_sampleState);
	if(FAILED(result))
	{
		return false;
	}

	return true;
}


void CTextureShader::ShutdownShader()
{
	if(m_sampleState)
	{
		m_sampleState->Release();
		m_sampleState = 0;
	}

	if(m_matrixBuffer)
	{
		m_matrixBuffer->Release();
		m_matrixBuffer = 0;
	}

	if(m_layout)
	{
		m_layout->Release();
		m_layout = 0;
	}

	if(m_pixelShader)
	{
		m_pixelShader->Release();
		m_pixelShader = 0;
	}

	if(m_vertexShader)
	{
		m_vertexShader->Release();
		m_vertexShader = 0;
	}

	return;
}


void CTextureShader::OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* shaderFilename)
{
	char* compileErrors;
	unsigned long bufferSize, i;
	ofstream fout;


	compileErrors = (char*)(errorMessage->GetBufferPointer());

	bufferSize = errorMessage->GetBufferSize();

	fout.open("shader-error.txt");

	for(i=0; i<bufferSize; i++)
	{
		fout << compileErrors[i];
	}

	fout.close();

	errorMessage->Release();
	errorMessage = 0;

	MessageBox(hwnd, L"Error compiling shader.  Check shader-error.txt for message.", shaderFilename, MB_OK);

	return;
}


bool CTextureShader::SetShaderParameters(ID3D11DeviceContext* deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
											 D3DXMATRIX projectionMatrix, float* valueArray, ID3D11ShaderResourceView* texture)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource = {0,};
	MatrixBufferType* dataPtr;
	PSBufferType* psDataPtr;
	unsigned int bufferNumber;

	D3DXMatrixTranspose(&worldMatrix, &worldMatrix);
	D3DXMatrixTranspose(&viewMatrix, &viewMatrix);
	D3DXMatrixTranspose(&projectionMatrix, &projectionMatrix);

	result = deviceContext->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if(FAILED(result))
	{
		return false;
	}

	dataPtr = (MatrixBufferType*)mappedResource.pData;
	
	dataPtr->world = worldMatrix;
	dataPtr->view = viewMatrix;
	dataPtr->projection = projectionMatrix;

    deviceContext->Unmap(m_matrixBuffer, 0);

	bufferNumber = 0;

    deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_matrixBuffer);
	
	D3D11_MAPPED_SUBRESOURCE temp;

	result = deviceContext->Map(m_psBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &temp);
	if(FAILED(result))
	{
		return false;
	}

	psDataPtr = (PSBufferType*)temp.pData;

	psDataPtr->color[0] = valueArray[0];
	psDataPtr->color[1] = valueArray[1];
	psDataPtr->color[2] = valueArray[2];
	psDataPtr->color[3] = valueArray[3];

    deviceContext->Unmap(m_psBuffer, 0);

	deviceContext->PSSetConstantBuffers(0, 1, &m_psBuffer);

	deviceContext->PSSetShaderResources(0, 1, &texture);


	return true;
}


void CTextureShader::RenderShader(ID3D11DeviceContext* deviceContext, int indexCount)
{
	deviceContext->IASetInputLayout(m_layout);

    deviceContext->VSSetShader(m_vertexShader, NULL, 0);
    deviceContext->PSSetShader(m_pixelShader, NULL, 0);

	deviceContext->PSSetSamplers(0, 1, &m_sampleState);

	deviceContext->DrawIndexed(indexCount, 0, 0);

	return;
}