#ifndef _CFONT_H_
#define _CFONT_H_

#include <Windows.h>
#include "..\..\lib\FW1FontWrapper.h"

// Class name: CFont //
class CFont
{
private:
	IFW1Factory *m_pFW1Factory;
	IFW1FontWrapper* m_pWrapper;

public:
	CFont();
	CFont(const CFont&);
	~CFont();

	bool Initialize(LPCWSTR);
	bool Shutdown();

	bool SetFont(LPCWSTR);
	bool Draw(WCHAR*, float, float, float, UINT32, UINT);
};

UINT32 GetColor(UINT8, UINT8, UINT8, UINT8);

#endif