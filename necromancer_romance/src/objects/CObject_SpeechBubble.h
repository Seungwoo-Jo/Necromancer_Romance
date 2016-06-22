#ifndef _COBJECT_SPEECHBUBBLE_H_
#define _COBJECT_SPEECHBUBBLE_H_

#include "CObject.h"

class CBitmap;
class CTextureShader;
class CFont;

class CObject_SpeechBubble : public CObject
{
private:
	CBitmap* m_speechBubble;
	CTextureShader* m_shader;
	CFont*	m_script;

public:
	CObject_SpeechBubble();
	CObject_SpeechBubble(const CObject_SpeechBubble&);
	~CObject_SpeechBubble();

	void Initalize(int slot);
	void Shutdown();

	void Reset();

	virtual void Update(CInput*);
	virtual void Render();
	void Render(int slot, WCHAR* script);
	Qusy::Rect GetRect();
	CBitmap* GetBitmap();
};

#endif