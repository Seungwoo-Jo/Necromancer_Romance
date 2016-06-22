#include "..\framework\CBitmap.h"
#include "..\framework\CTextureShader.h"

#include "CObject_Num.h"

CObject_Num::CObject_Num()
{
	for(int i=0; i<5; i++)
	{
		m_numberImage[i] = nullptr;
		m_numberShader[i] = nullptr;
		m_num[i] = 0;
	}
	m_numLength = 0;
}

CObject_Num::CObject_Num(const CObject_Num& obj)
{
}

CObject_Num::~CObject_Num()
{
}

void CObject_Num::Initialize()
{
	for(int i=0; i<5; i++) {
		m_numberImage[i] = new CBitmap();
		m_numberImage[i]->Initialize(L"res/effect/number_image.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

		m_numberShader[i] = new CTextureShader();
		m_numberShader[i]->Initialize(NULL, NULL);
	}
}

void CObject_Num::Shutdown()
{
	for(int i=0; i<3; i++)
	{
		if(m_numberImage[i] != nullptr)
		{
			m_numberImage[i]->Shutdown();
			SAFE_DELETE(m_numberImage[i]);
		}
	}
	for(int i=0; i<3; i++)
	{
		if(m_numberShader[i] != nullptr)
		{
			m_numberShader[i]->Shutdown();
			SAFE_DELETE(m_numberShader[i]);
		}
	}
}

void CObject_Num::Update(CInput* input)
{

}

void CObject_Num::Render()
{
	Qusy::Position pos = getPosition();

	if(m_numLength != 0)
	{
		for(int i=0; i<m_numLength; i++)
		{
			float srcX = m_num[(m_numLength-1)-i] * 0.1f;
			m_numberImage[i]->Render(pos.posX + (50*i), pos.posY, pos.posZ, srcX, 0.0f, 0.1f, 1.0f);
			m_numberShader[i]->Render(m_numberImage[i]->GetTexture(), getOpacity());
		}
	}
}

void CObject_Num::SetNum(int num)
{
	m_numLength = 0;
	if(num != 0)
	{
		for(int i=1 ; num >= i ; i*=10 )
		{
			m_num[m_numLength] = ((num % (i*10)) - (num % i)) / i;
			m_numLength++;
		}
	}
	else if(num == 0)
	{
		m_numLength = 1;
		m_num[0] = 0;
	}
}