#ifndef _COBJECT_EXPLOREBAR_H_
#define _COBJECT_EXPLOREBAR_H_

#include "CObject.h"

class CBitmap;
class CTextureShader;
class CTime;

class CObject_ExploreBar : public CObject
{
private:
	CBitmap* m_exploreBar;
	CBitmap* m_nero;
	CBitmap* m_hero;
	CTextureShader* m_shader[3];
	CTime* m_fadeTimer;
	CTime* m_heroTimer;
	bool m_bShow;
public:
	CObject_ExploreBar();
	CObject_ExploreBar(const CObject_ExploreBar&);
	~CObject_ExploreBar();

	void Initalize();
	void Shutdown();

	virtual void Update(CInput*);
	virtual void Render();

	void Show(bool);
};

#endif