#ifndef _CEFFECT_SPEECHBUBBLE_H_
#define _CEFFECT_SPEECHBUBBLE_H_

#include "CEffect.h"

class CSound;
class CObject_SpeechBubble;

class CEffect_SpeechBubble: public CEffect
{
private:
	Qusy::Position m_effectPos;

	CObject_SpeechBubble* m_speechBubble;

	CTime* m_effectTimer;
	int m_slot;
	int m_cardNum;

	WCHAR m_script[36];

	CSound* m_sound;
public:
	CEffect_SpeechBubble();
	CEffect_SpeechBubble(const CEffect_SpeechBubble&);
	~CEffect_SpeechBubble();

	virtual void Initialize();
	virtual void Shutdown();

	virtual void Reset(WCHAR*);
	void SetSlot(int cardNum);
	virtual void SetDamage(int num, int totalDamage);
	virtual bool GetAlive();

	virtual void Update();
	virtual void Render();
	void Render(WCHAR*);
};

#endif