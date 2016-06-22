#include "..\framework\CInput.h"
#include "..\framework\CFont.h"
#include "..\framework\CTime.h"
#include "..\framework\CBitmap.h"
#include "..\framework\CTextureShader.h"

#include "..\managers\CNero.h"
#include "..\managers\CSceneManager.h"

#include "CCard.h"
#include "CObject_ExploreResult.h"

CObject_ExploreResult::CObject_ExploreResult()
{
	m_resultWindow = NULL;
	m_resultWindowShader = NULL;
	for(int i=0; i<5; i++) {
		m_resultMark[i] = NULL;
	}
	m_resultMarkShader = NULL;
	m_text = NULL;
	m_timer = NULL;
	m_bShow = false;
	m_resultTarget = NULL;
	m_resultNum = -1;
	m_resultValue = 0;
	for(int i=0; i<5; i++) {
		m_bResult[i] = false;
	}

}

CObject_ExploreResult::~CObject_ExploreResult()
{
}

void CObject_ExploreResult::Initialize()
{
	setPosition(290, 130, 8);

	m_resultWindow = new CBitmap();
	m_resultWindow->Initialize(L"res/field/explore_result.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	m_resultWindowShader = new CTextureShader();
	m_resultWindowShader->Initialize(NULL, NULL);
	
	m_resultMark[RESULT::WON]		= new CBitmap();
	m_resultMark[RESULT::LOST]		= new CBitmap();
	m_resultMark[RESULT::BATTLE]	= new CBitmap();
	m_resultMark[RESULT::TREASURE]	= new CBitmap();
	m_resultMark[RESULT::TRAP]		= new CBitmap();
	
	m_resultMark[RESULT::WON]		->Initialize(L"res/field/explore_won.png",		0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	m_resultMark[RESULT::LOST]		->Initialize(L"res/field/explore_lost.png",		0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	m_resultMark[RESULT::BATTLE]	->Initialize(L"res/field/explore_battle.png",	0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	m_resultMark[RESULT::TREASURE]	->Initialize(L"res/field/explore_treasure.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	m_resultMark[RESULT::TRAP]		->Initialize(L"res/field/explore_trap.png",		0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	m_resultMarkShader = new CTextureShader();
	m_resultMarkShader->Initialize(NULL, NULL);

	m_text = new CFont();
	m_text->Initialize(L"10X10");

	m_timer = new CTime();
	m_timer->SetTimer(0.1f, false);

	m_resultTarget = NULL;
	m_resultValue = 0;
	m_resultNum = -1;
	m_bShow = false;

}

void CObject_ExploreResult::Shutdown()
{
	if(m_resultWindow != NULL)
	{
		m_resultWindow->Shutdown();
		SAFE_DELETE(m_resultWindow);
	}
	if(m_resultWindowShader != NULL)
	{
		m_resultWindowShader->Shutdown();
		SAFE_DELETE(m_resultWindowShader);
	}
	for(int i=0; i<5; i++)
	{
		if(m_resultMark[i] != NULL)
		{
			m_resultMark[i]->Shutdown();
			SAFE_DELETE(m_resultMark[i]);
		}
	}
	if(m_resultMarkShader != NULL)
	{
		m_resultMarkShader->Shutdown();
		SAFE_DELETE(m_resultMarkShader);
	}
	if(m_text != NULL)
	{
		m_text->Shutdown();
		SAFE_DELETE(m_text);
	}
	if(m_timer != NULL)
	{
		m_timer->StopTimer();
		SAFE_DELETE(m_timer);
	}

	m_bShow = false;
}

void CObject_ExploreResult::Update(CInput* input)
{
	Qusy::Point mouse;
	input->GetMousePoint(mouse.posX, mouse.posY);

	m_resultValue = 0;

	if(m_resultNum == RESULT::TREASURE)
	{
		int temp = rand()%100;
		if(temp < 40) {
			m_resultValue = 50;
		}
		else if(temp >= 40 && temp < 60) {
			m_resultValue = 100;
		}
		else if(temp >= 60 && temp < 75) {
			m_resultValue = 200;
		}
		else if(temp >= 75 && temp < 85) {
			m_resultValue = 300;
		}
		else if(temp >= 85 && temp < 93) {
			m_resultValue = 500;
		}
		else if(temp >= 93 && temp < 98) {
			m_resultValue = 700;
		}
		else {
			m_resultValue = 1000;
		}

		m_bResult[RESULT::TREASURE] = true;
		CNero::getNero()->SetGold(CNero::getNero()->GetGold()+m_resultValue);
		
	}
	else if(m_resultNum == RESULT::TRAP)
	{
		while(true)
		{
			m_resultTarget = CNero::getNero()->GetPartyCardWithSlot(rand()%4);
			if(m_resultTarget != NULL) {
				break;
			}
		}
		int temp = rand()%100;

		if(temp < 50) {
			m_resultValue = static_cast<int>((float)m_resultTarget->getStat().m_maxHp * 0.05f);
		}
		else if(temp >= 50 && temp < 80) {
			m_resultValue = static_cast<int>((float)m_resultTarget->getStat().m_maxHp * 0.10f);
		}
		else if(temp >= 80 && temp < 91) {
			m_resultValue = static_cast<int>((float)m_resultTarget->getStat().m_maxHp * 0.20f);
		}
		else if(temp >= 91 && temp < 96) {
			m_resultValue = static_cast<int>((float)m_resultTarget->getStat().m_maxHp * 0.30f);
		}
		else if(temp >= 96 && temp < 99) {
			m_resultValue = static_cast<int>((float)m_resultTarget->getStat().m_maxHp * 0.50f);
		}
		else {
			m_resultValue = static_cast<int>((float)m_resultTarget->getStat().m_maxHp * 1.00f);
		}
		m_bResult[RESULT::TRAP] = true;
		m_resultTarget->setHp(m_resultTarget->getStat().m_hp - m_resultValue);

		
	}
	
	if(!m_timer->GetTimer())
	{
		for(int i=0; i<5; i++)
		{
			m_bResult[i] = false;
		}
	}
	
}

void CObject_ExploreResult::Render()
{
	Qusy::Position pos = getPosition();
	float opacity = 0.0f;
	
	if(m_bShow) {
		opacity = 1.0f - (m_timer->RemainTime()/m_timer->GetSetTime());
	}
	else {
		opacity = (m_timer->RemainTime()/m_timer->GetSetTime());
	}
	m_resultWindow->Render(pos.posX, pos.posY, pos.posZ, 1.0f, 1.0f);
	m_resultWindowShader->Render(m_resultWindow->GetTexture(), opacity);

	if(m_bResult[RESULT::TREASURE])
	{
		m_resultMark[RESULT::TREASURE]->Render(pos.posX+150, pos.posY+100, pos.posZ, 1.0f, 1.0f);
		m_resultMarkShader->Render(m_resultMark[RESULT::TREASURE]->GetTexture(), opacity);

		WCHAR gold[14]		= {NULL,};	wsprintf(gold, L"%d 골드 획득!", m_resultValue);
		m_text->Draw(gold, 32, 640, 407, GetColor(255, 255, 255, (UINT8)(255.0f)), NULL);
	}
	else if(m_bResult[RESULT::TRAP])
	{
		m_resultMark[RESULT::TRAP]->Render(pos.posX+150, pos.posY+100, pos.posZ, 1.0f, 1.0f);
		m_resultMarkShader->Render(m_resultMark[RESULT::TRAP]->GetTexture(), opacity);

		WCHAR damage[12]	= {NULL,};	wsprintf(damage, L"%d의 데미지", m_resultValue);
		WCHAR name[6]		= {NULL,};	lstrcpy(name, m_resultTarget->getCardName());

		m_text->Draw(L"함정에 걸리고 말았다...", 32, 640, 407, GetColor(255, 255, 255, (UINT8)(opacity*255.0f)), NULL);

		m_text->Draw(name, 32, 590, 455, GetColor(255, 255, 255, (UINT8)(255.0f)), FW1_RIGHT|FW1_VCENTER);
		m_text->Draw(L"는(은)", 32, 615, 455, GetColor(255, 255, 255, (UINT8)(opacity*255.0f)), NULL);
		m_text->Draw(damage, 32, 665, 455, GetColor(255, 55, 55, (UINT8)(255.0f)), NULL);
		m_text->Draw(L"를 입었다.", 32, 690, 455, GetColor(255, 255, 255, (UINT8)(255.0f)), NULL);
	}

	m_resultNum = -1;
}

void CObject_ExploreResult::Show(bool show)
{
	if(!show)
	{
		m_timer->SetTimer(1.0f, false);
	}
	m_bShow = show;
}

void CObject_ExploreResult::SetResult(int result)
{
	m_resultNum = result;
}