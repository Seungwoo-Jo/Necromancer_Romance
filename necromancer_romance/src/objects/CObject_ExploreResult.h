#ifndef _COBJECT_EXPLORERESULT_H_
#define _COBJECT_EXPLORERESULT_H_

#include "CObject.h"

enum RESULT
{
	WON = 0,
	LOST,
	BATTLE,
	TREASURE,
	TRAP,
};

class CInput;
class CTime;
class CFont;
class CBitmap;
class CTextureShader;
class CCard;

class CObject_ExploreResult : public CObject
{
private:
	CBitmap* m_resultWindow;
	CTextureShader* m_resultWindowShader;

	CBitmap* m_resultMark[5];
	CTextureShader* m_resultMarkShader;

	CTime* m_timer;
	CFont* m_text;

	CCard* m_resultTarget;
	int m_resultValue;
	int m_resultNum;
	bool m_bResult[5];
	bool m_bShow;
	

public:
	CObject_ExploreResult();
	~CObject_ExploreResult();

	void Initialize();
	void Shutdown();
	
	void Update(CInput*);
	void Render();

	void Show(bool);
	void SetResult(int);
};

#endif