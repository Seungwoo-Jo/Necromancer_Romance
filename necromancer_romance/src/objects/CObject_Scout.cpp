// ..\framework
#include "..\framework\CSound.h"
#include "..\framework\CInput.h"
#include "..\framework\common.h"
#include "..\framework\CBitmap.h"
#include "..\framework\CTextureShader.h"
#include "..\framework\CFont.h"

// ..\managers
#include "..\managers\CNero.h"
#include "..\managers\CObjectManager.h"
#include "..\managers\CCardManager.h"

// ..\objects
#include "CCard.h"
#include "CObject_Status.h"
#include "CObject_Scout.h"
#include "CObject_Common.h"
#include "CObject_Cardgauge.h"

CObject_Scout::CObject_Scout()
{
	m_input = NULL;
	m_scoutWindow = NULL;
	m_scoutWindowShader = NULL;
	m_scoutBtn = NULL;
	m_scoutBtnShader = NULL;
	m_scoutNum = 0;
	m_buyPrice = 300;
	for(int i=0; i<PAGE_CARD_NUM; i++) {
		m_gauge[i] = NULL;
	}
	for(int i=0; i<30; i++) {
		m_changeArray[i] = NULL;
	}
	m_sound_Scout = NULL;
	m_sceneOpacity = 1.0f;

}

CObject_Scout::CObject_Scout(const CObject_Scout& scout)
{

}

CObject_Scout::~CObject_Scout()
{

}

void CObject_Scout::Initalize()
{
	setPosition(0, -421, 10);

	m_scoutWindow = new CBitmap();
	m_scoutWindow->Initialize(L"res/member_scout.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	m_scoutWindowShader = new CTextureShader();
	m_scoutWindowShader->Initialize(NULL, NULL);

	m_scoutBtn = new CBitmap();
	m_scoutBtn->Initialize(L"res/btn_scout.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	m_scoutBtnShader = new CTextureShader();
	m_scoutBtnShader->Initialize(NULL, NULL);

	for(int i=0; i<PAGE_CARD_NUM; i++) {
		m_gauge[i] = new CObject_Cardgauge();
		m_gauge[i]->Initalize(NULL);
	}

	m_text = new CFont();
	m_text->Initialize(L"10X10");

	m_pageNow = 0;
	m_pageMax = 0;
	
	m_sound_Scout = new CSound();
	m_sound_Scout->Initialize("res/sound/se/scout.wav");
	m_sound_Scout->Loop(false);

	for(int i=0; i<30; i++)
	{
		if(TOTAL_CARD >= i+1)
		{
			CCard* tempCard = CCardManager::getCardManager()->getCardWithNum(i+1);
			if(tempCard != NULL)
			{
				bool result = true;
				for(int j=0; j<CNero::getNero()->GetHaveCardNum(); j++)
				{
					if(tempCard == CNero::getNero()->GetHaveCardWithIndex(j)) {
						result = false;
					}
				}
				if(result)
				{
					m_changeArray[i] = tempCard;
					m_pageMax = i;
				}
			}
		}
		else
		{
			break;
		}
	}

	

}

void CObject_Scout::Shutdown()
{
	if(m_scoutWindow != NULL)
	{
		m_scoutWindow->Shutdown();
		SAFE_DELETE(m_scoutWindow);
	}
	if(m_scoutWindowShader != NULL)
	{
		m_scoutWindowShader->Shutdown();
		SAFE_DELETE(m_scoutWindowShader);
	}
	if(m_scoutBtn != NULL)
	{
		m_scoutBtn->Shutdown();
		SAFE_DELETE(m_scoutBtn);
	}
	if(m_scoutBtnShader != NULL)
	{
		m_scoutBtnShader->Shutdown();
		SAFE_DELETE(m_scoutBtnShader);
	}
	for(int i=0; i<PAGE_CARD_NUM; i++)
	{
		if(m_gauge[i] != NULL)
		{
			m_gauge[i]->Shutdown();
			SAFE_DELETE(m_gauge[i]);
		}
	}
	if(m_sound_Scout != NULL)
	{
		m_sound_Scout->Release();
		SAFE_DELETE(m_sound_Scout);
	}
	if(m_text != NULL)
	{
		m_text->Shutdown();
		SAFE_DELETE(m_text);
	}
}

void CObject_Scout::Update(CInput* input)
{
	m_input = input;
	Qusy::Rect Back;

	input->GetMousePoint(m_mouse.posX, m_mouse.posY);
	m_scoutWindow->GetRect(Back);


	if(Qusy::Collision(m_mouse, Back))
	{
		if(input->IsWheelUp()) {
			m_pageNow--;
			if(m_pageNow < 0) {
				m_pageNow = 0;
			}
		}
		if(input->IsWheelDown()) {
			m_pageNow++;
			if(m_pageNow+4 > m_pageMax)
			{
				if(m_pageMax > 4) {
					m_pageNow = m_pageMax-4;
				}
				else {
					m_pageNow = m_pageMax;
				}
			}
		}
	}

	for(int i=0; i<PAGE_CARD_NUM; i++)
	{
		Qusy::Position btnPosition;
		Qusy::Rect temp;
		btnPosition.setPosition(100 + (231*i), getPosition().posY+70+197+41, 10);
		temp.setRect(btnPosition.posX, btnPosition.posY, btnPosition.posX+156, btnPosition.posY+41);

		if(m_changeArray[(m_pageNow) + i] != NULL)
		{
			if(Qusy::Collision(m_mouse, temp))
			{
				if(input->IsLButtonUp())
				{
					if(CNero::getNero()->GetGold() >= m_buyPrice)
					{
						CNero::getNero()->AddHaveCard(m_changeArray[(m_pageNow) + i]);
						m_changeArray[(m_pageNow) + i] = NULL;
						CNero::getNero()->SetGold(CNero::getNero()->GetGold() -  m_buyPrice);
						if(m_scoutNum == 0) {
							CNero::getNero()->SetStoryProgress(STORY::STORY05);
						}
						m_scoutNum++;
					
						m_sound_Scout->Stop();
						m_sound_Scout->Play();
					}
				}

				if(input->IsLButtonDown())
				{
					m_sound_Scout->Reset();
				}
			}
		}
	}
	
	

	m_buyPrice = 300 + (m_scoutNum * 300);

	removeNull();
}

void CObject_Scout::Render()
{
	Qusy::Position pos = getPosition();
	
	float opacity = 1.0f - ((pos.posY * -1)/421.0f);

	m_scoutWindow->Render(pos.posX, pos.posY, pos.posZ);
	m_scoutWindowShader->Render(m_scoutWindow->GetTexture(), opacity);

	if(m_bShow)
	{
		setPosition(pos.posX, pos.posY + 28, pos.posZ);
		if(getPosition().posY >= 0) {
			setPosition(pos.posX, 0, pos.posZ);
		}
	}
	else
	{
		setPosition(pos.posX, pos.posY - 28, pos.posZ);
		if(getPosition().posY <= -421) {
			setPosition(pos.posX, -421, pos.posZ);
		}
	}

	if(m_bShow)
	{
		int tempX = -1;
		WCHAR price[6] = {NULL,};
		wsprintf(price, L"%d", 300 + m_scoutNum * 300);

		// 교체창에 가진 카드 깔기
		for(int i=0; i<PAGE_CARD_NUM; i++)
		{
			Qusy::Position renderPosition;
			Qusy::Rect temp;
			int width = 155;
			int height = 173;
			renderPosition.setPosition(100 + (231*i), pos.posY+115, 10);
			temp.setRect(renderPosition.posX, renderPosition.posY, renderPosition.posX+155, renderPosition.posY+173);
			
			if(m_changeArray[(m_pageNow) + i] != NULL)
			{
				m_changeArray[(m_pageNow) + i]->CardRender(renderPosition.posX, renderPosition.posY, renderPosition.posZ, width, height, NULL, opacity);

				m_scoutBtn->Render(renderPosition.posX, renderPosition.posY+180, renderPosition.posZ-1);
				m_scoutBtnShader->Render(m_scoutBtn->GetTexture(), opacity);

				m_text->Draw(price, 24, renderPosition.posX+117, renderPosition.posY+180+21, GetColor(255, 255, 255, 255), NULL);

				m_gauge[i]->SetCard(m_changeArray[(m_pageNow) + i]);
				m_gauge[i]->Render(155, 173);
			}
			
		}
	}
}

void CObject_Scout::acceptSceneOpacity(float opacity)
{
	m_sceneOpacity = opacity;
}

void CObject_Scout::Show(bool show)
{
	m_bShow = show;
}

void CObject_Scout::removeNull()
{
	for(int i=0; i<30; i++)
	{
		if(m_changeArray[i] == NULL)
		{
			if(i+1 < 30)
			{
				m_changeArray[i] = m_changeArray[i+1];
				m_changeArray[i+1] = NULL;
			}
		}
	}
}