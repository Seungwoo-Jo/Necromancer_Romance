// ..\framework
#include "..\framework\CInput.h"
#include "..\framework\common.h"
#include "..\framework\CBitmap.h"
#include "..\framework\CTextureShader.h"
#include "..\framework\CFont.h"

#include "..\managers\CCardManager.h"
#include "..\managers\CScriptManager.h"

// ..\objects
#include "CCard.h"
#include "CObject_TalkWindow.h"

CObject_TalkWindow::CObject_TalkWindow()
{
	m_common	= NULL;
	m_shader	= NULL;
	m_script	= NULL;
	m_numOfText = 0;
	m_slow		= 0.0f;
}

CObject_TalkWindow::CObject_TalkWindow(const CObject_TalkWindow& object)
{
}

CObject_TalkWindow::~CObject_TalkWindow()
{
}

void CObject_TalkWindow::Initalize()
{
	setPosition(12, 470, 0);

	m_common = new CBitmap();
	m_common->Initialize(L"res/script2.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	m_shader = new CTextureShader();
	m_shader->Initialize(NULL, NULL);
	
	for(int i=0; i<15; i++)
	{
		WCHAR text[48] = {NULL,};
		wsprintf(text, L"res/cards/illustration/illust_%d.png", i);
		m_illustration[i] = new CBitmap();
		if(i == 3) {
			m_illustration[i]->Initialize(text, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
		}
		else {
			m_illustration[i]->Initialize(text, 0.0f, 0.0f, 1.0f, 1.0f, 0.6f, 0.6f);
		}
	}
	m_illustShader = new CTextureShader();
	m_illustShader->Initialize(NULL, NULL);

	m_script = new CFont();
	m_script->Initialize(L"10X10");

	m_numOfText = 0;
	m_slow		= 0.0f;

	ZeroMemory(m_name, sizeof(m_name));
	ZeroMemory(m_text, sizeof(m_text));
	ZeroMemory(m_output, sizeof(m_output));
}

void CObject_TalkWindow::Shutdown()
{
	if(m_common != NULL)
	{
		m_common->Shutdown();
		SAFE_DELETE(m_common);
	}
	if(m_shader != NULL)
	{
		m_shader->Shutdown();
		SAFE_DELETE(m_shader);
	}
	for(int i=0; i<14; i++)
	{
		if(m_illustration[i] != NULL)
		{
			m_illustration[i]->Shutdown();
			SAFE_DELETE(m_illustration[i]);
		}
	}
	if(m_illustShader != NULL)
	{
		m_illustShader->Shutdown();
		SAFE_DELETE(m_illustShader);
	}
	if(m_script != NULL)
	{
		m_script->Shutdown();
		SAFE_DELETE(m_script);
	}
}

void CObject_TalkWindow::Reset(int script_num, int card_num)
{
	setPosition(12, 470, 0);
	ZeroMemory(m_name, sizeof(m_name));
	ZeroMemory(m_text, sizeof(m_text));
	ZeroMemory(m_output, sizeof(m_output));

	WCHAR* text = CScriptManager::getSkillManager()->getScriptWithNum(script_num);
	swprintf_s(m_text, 128, text);
	m_numOfText = 0;
	
	m_cardNum = card_num;
	
	if(m_cardNum == CARD::NOCARD) {
		swprintf_s(m_name, 2, L" ");
	}
	else if(m_cardNum == CARD::DAY) {
		swprintf_s(m_name, 4, L"레나타");
	}
	else if(m_cardNum == CARD::HILDE) {
		swprintf_s(m_name, 2, L"신");
	}
	else if(m_cardNum == CARD::AYRIN) {
		setPosition(0, 0, 0);
	}
	else if(m_cardNum == CARD::ILL_SHOA) {
		swprintf_s(m_name, 3, L"쇼아");
	}
	else {
		swprintf_s(m_name, 5, CCardManager::getCardManager()->getCardWithNum(card_num)->getCardName());
	}
}

void CObject_TalkWindow::Update(CInput* input)
{
	if(m_numOfText < 128)
	{
		for(int i=0; i<=m_numOfText; i++)
		{
			m_output[i] = m_text[i];
		}
		
		m_numOfText += 1;
	}
}

void CObject_TalkWindow::Render()
{
	Qusy::Position pos = getPosition();

	int y = 88;

	if(m_cardNum == CARD::AYRIN) {
		y = 0;
	}
	m_illustration[m_cardNum]->Render(pos.posX, y, pos.posZ, 0.0f, 0.0f, 1.0f, 1.0f);
	m_illustShader->Render(m_illustration[m_cardNum]->GetTexture(), getOpacity());

	if(m_cardNum != CARD::AYRIN) {
		m_common->Render(pos.posX, pos.posY, pos.posZ);
		m_shader->Render(m_common->GetTexture(), getOpacity());
	}
	if(m_cardNum != CARD::NOCARD || m_cardNum != CARD::AYRIN) {
		m_script->Draw(m_name, 30.0f, pos.posX+95, pos.posY+34, GetColor(255, 255, 255, 255), NULL);
	}
	if(m_cardNum != CARD::AYRIN) {
		m_script->Draw(m_output, 34.0f, pos.posX+38, pos.posY+135, GetColor(255, 255, 255, 255), FW1_LEFT| FW1_VCENTER |FW1_NOGEOMETRYSHADER);
	}
}

Qusy::Rect CObject_TalkWindow::GetRect()
{
	Qusy::Rect temp;
	m_common->GetRect(temp);
	return temp;
}

CBitmap* CObject_TalkWindow::GetBitmap()
{
	return m_common;
}