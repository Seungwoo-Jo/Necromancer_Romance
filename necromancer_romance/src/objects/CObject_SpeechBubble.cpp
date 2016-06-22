// ..\framework
#include "..\framework\CInput.h"
#include "..\framework\common.h"
#include "..\framework\CBitmap.h"
#include "..\framework\CTextureShader.h"
#include "..\framework\CFont.h"

// ..\objects
#include "CObject_SpeechBubble.h"

CObject_SpeechBubble::CObject_SpeechBubble()
{
	m_speechBubble = NULL;
	m_shader = NULL;
	m_script = NULL;
}

CObject_SpeechBubble::CObject_SpeechBubble(const CObject_SpeechBubble& object)
{
}

CObject_SpeechBubble::~CObject_SpeechBubble()
{
}

void CObject_SpeechBubble::Initalize(int slot)
{
	setPosition(261 + (200.5f*slot), 320, 10);

	m_speechBubble = new CBitmap();
	m_speechBubble->Initialize(L"res/speech_bubble.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	m_shader = new CTextureShader();
	m_shader->Initialize(NULL, NULL);

	m_script = new CFont();
	m_script->Initialize(L"10X10");
}

void CObject_SpeechBubble::Shutdown()
{
	if(m_speechBubble != NULL)
	{
		m_speechBubble->Shutdown();
		SAFE_DELETE(m_speechBubble);
	}

	if(m_shader != NULL)
	{
		m_shader->Shutdown();
		SAFE_DELETE(m_shader);
	}

	if(m_script != NULL)
	{
		m_script->Shutdown();
		SAFE_DELETE(m_script);
	}
}

void CObject_SpeechBubble::Reset()
{

}

void CObject_SpeechBubble::Update(CInput* input)
{
	
}

void CObject_SpeechBubble::Render()
{
	Qusy::Position pos = getPosition();
	m_speechBubble->Render(pos.posX+(39.0f*(1.0f-getOpacity())), pos.posY+(140.0f*(1.0f-getOpacity())), pos.posZ, getOpacity(), getOpacity());
	m_shader->Render(m_speechBubble->GetTexture(), 1.0f);
}

void CObject_SpeechBubble::Render(int slot, WCHAR* script)
{
	setPosition(261 + (200.5f*slot), 320, 10);
	Qusy::Position pos = getPosition();

	Render();

	if(getOpacity() >= 0.1f)
	{
		WCHAR text[10] = {NULL,};	lstrcpy(text, script);
		m_script->Draw(text, (28.0f*getOpacity()), pos.posX+39+(39.0f*getOpacity()), pos.posY+59+(81.0f*(1.0f-getOpacity())), GetColor(0, 0, 0, 255), NULL);
	}
}

Qusy::Rect CObject_SpeechBubble::GetRect()
{
	Qusy::Rect temp;
	m_speechBubble->GetRect(temp);
	return temp;
}

CBitmap* CObject_SpeechBubble::GetBitmap()
{
	return m_speechBubble;
}