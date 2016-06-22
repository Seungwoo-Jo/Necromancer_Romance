#ifndef _COBJECT_TALKWINDOW_H_
#define _COBJECT_TALKWINDOW_H_

#include "CObject.h"

class CBitmap;
class CTextureShader;
class CFont;

class CObject_TalkWindow : public CObject
{
private:
	CBitmap* m_common;
	CTextureShader* m_shader;

	CBitmap* m_illustration[15];
	CTextureShader* m_illustShader;

	WCHAR m_name[5];
	WCHAR m_text[128];
	WCHAR m_output[128];

	int m_numOfText;
	int m_cardNum;
	float m_slow;
	CFont* m_script;
public:
	CObject_TalkWindow();
	CObject_TalkWindow(const CObject_TalkWindow&);
	~CObject_TalkWindow();

	void Initalize();
	void Shutdown();

	void Reset(int script_num, int card_num);

	virtual void Update(CInput*);
	virtual void Render();
	

	Qusy::Rect GetRect();
	CBitmap* GetBitmap();
};

#endif