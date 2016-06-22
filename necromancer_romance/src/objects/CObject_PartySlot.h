#ifndef _COBJECT_PARTYSLOT_H_
#define _COBJECT_PARTYSLOT_H_

#include "CObject.h"

class CBitmap;
class CTextureShader;
class CFont;

class CObject_PartySlot : public CObject
{
private:
	CBitmap* m_partySlot;
	CTextureShader* m_shader;
	CFont* m_text;

	float m_sceneOpacity;
public:
	CObject_PartySlot();
	CObject_PartySlot(const CObject_PartySlot&);
	~CObject_PartySlot();

	void Initalize();
	void Shutdown();

	virtual void Update(CInput*);
	virtual void Render();

	void acceptSceneOpacity(float);
};

#endif