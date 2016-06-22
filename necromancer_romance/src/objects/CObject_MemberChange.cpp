// ..\framework
#include "..\framework\CInput.h"
#include "..\framework\common.h"
#include "..\framework\CBitmap.h"
#include "..\framework\CTextureShader.h"

// ..\managers
#include "..\managers\CNero.h"
#include "..\managers\CObjectManager.h"
#include "..\managers\CBattleManager.h"

// ..\objects
#include "CCard.h"
#include "CObject_Status.h"
#include "CObject_MemberChange.h"
#include "CObject_Common.h"
#include "CObject_Cardgauge.h"

CObject_MemberChange::CObject_MemberChange()
{
	m_background = NULL;
	m_shader = NULL;
	m_input = NULL;
	m_statusWindow = NULL;
	m_statusBtn = NULL;
	m_statusBtnShader = NULL;
	m_turn = NULL;
	m_clickCard = NULL;
	for(int i=0; i<9; i++) {
		m_gauge[i] = NULL;
	}
	for(int i=0; i<4; i++)
		m_btnOpacity[i] = 0.0f;
	m_bShow = false;
	m_sceneOpacity = 0.0f;
	m_pageNow = 0;
	m_pageMax = 0;
	for(int i=0; i<30; i++) {
		m_changeArray[i] = NULL;
	}
	m_numOfCard = 0;
	m_mouse.posX = 0;
	m_mouse.posY = 0;
	for(int i=0; i<PAGE_CARD_NUM+4; i++) {
		m_bDrag[i] = false;
	}
	m_bActivate = true;
	m_srcCard = -1;
	m_destCard = -1;
}

CObject_MemberChange::CObject_MemberChange(const CObject_MemberChange& object)
{
}

CObject_MemberChange::~CObject_MemberChange()
{
}

void CObject_MemberChange::Initalize(int sceneNum)
{
	setPosition(0, -421, 10);
	m_numOfCard = 0;
	m_sceneNum = sceneNum;

	m_background = new CBitmap();
	m_background->Initialize(L"res/member_change.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	m_shader = new CTextureShader();
	m_shader->Initialize(NULL, NULL);

	m_statusWindow = new CObject_Status();
	m_statusWindow->Initalize(NULL);

	m_statusBtn = new CBitmap();
	m_statusBtn->Initialize(L"res/btn_status.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	m_statusBtnShader = new CTextureShader();
	m_statusBtnShader->Initialize(NULL, NULL);

	/*
	m_turn = new CObject_Common();
	m_turn->Initalize(0, 0, 0, 1.0f, 1.0f, L"res/battle/card_turn.png");
	*/
	for(int i=0; i<9; i++) {
		m_gauge[i] = new CObject_Cardgauge();
		m_gauge[i]->Initalize(NULL);
	}
	

	for(int i=0; i<CNero::getNero()->GetHaveCardNum(); i++) 
	{
		bool result = false;
		CCard* tempCard = CNero::getNero()->GetHaveCardWithIndex(i);
		if(tempCard != NULL)
		{
			for(int j=0; j<4; j++)
			{
				if(CNero::getNero()->GetPartyCardWithSlot(j) != NULL)
				{
					if(CNero::getNero()->GetPartyCardWithSlot(j) == tempCard) {
						result = true;
						break;
					}
				}
			}
			if(!result)
			{
				m_changeArray[m_numOfCard] = tempCard;
				m_numOfCard++;
			}
		}
	}
	m_pageNow = 0;
	m_pageMax = (m_numOfCard-1);
}

void CObject_MemberChange::Shutdown()
{
	if(m_background != NULL)
	{
		m_background->Shutdown();
		SAFE_DELETE(m_background);
	}
	if(m_shader != NULL)
	{
		m_shader->Shutdown();
		SAFE_DELETE(m_shader);
	}

	for(int i=0; i<30; i++) {
		m_changeArray[i] = NULL;
	}
	m_bShow = false;
	m_pageNow = 0;
	m_pageMax = 0;
	m_numOfCard = 0;
}

void CObject_MemberChange::Update(CInput* input)
{
	m_numOfCard = 0;

	for(int i=0; i<CNero::getNero()->GetHaveCardNum(); i++) 
	{
		bool result = false;
		CCard* tempCard = CNero::getNero()->GetHaveCardWithIndex(i);
		if(tempCard != NULL)
		{
			for(int j=0; j<4; j++)
			{
				if(CNero::getNero()->GetPartyCardWithSlot(j) != NULL)
				{
					if(CNero::getNero()->GetPartyCardWithSlot(j) == tempCard) {
						result = true;
						break;
					}
				}
			}
			if(!result)
			{
				m_changeArray[m_numOfCard] = tempCard;
				m_numOfCard++;
			}
		}
	}
	m_pageMax = (m_numOfCard-1);
	if(m_pageMax < 0) {
		m_pageMax = 0;
	}

	m_input = input;
	Qusy::Rect Back;

	input->GetMousePoint(m_mouse.posX, m_mouse.posY);
	m_background->GetRect(Back);

	m_statusWindow->Update(input);

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
	
	if(m_bActivate)
	{
		for(int i=0; i<PAGE_CARD_NUM; i++)
		{
			CCard* tempCard = m_changeArray[(m_pageNow) + i];
		
			if(tempCard != NULL)
			{
				Qusy::Rect cardRect;
				Qusy::Position pos = getPosition();
			
				cardRect.setRect(100+(231*i), pos.posY+100, 100+(231*i)+156, pos.posY+100+234);

				if(Qusy::Collision(m_mouse, cardRect))
				{
					if(m_srcCard == -1)
					{
						if(m_input->IsLButtonDown()) {
							m_bDrag[i] = true;
							m_srcCard = i;
						}
					}
					else
					{
						if(m_input->IsLButtonUp()) {
							m_bDrag[i] = false;
							m_destCard = i;
						}
					}
				
				}
			}
		}

		for(int i=0; i<4; i++)
		{
			CCard* tempCard = CNero::getNero()->GetPartyCardWithSlot(i);
		
			Qusy::Rect cardRect;
			Qusy::Point cardPoint;

			if(tempCard == NULL) {
				cardRect.setRect(272+(199*i), 470, 272+(199*i)+156, 470+234);
			}
			else 
			{
				tempCard->getCardPosition(cardPoint.posX, cardPoint.posY);
				cardRect.setRect(272+(199*i), 470, 272+(199*i)+156, 470+234);
				m_btnOpacity[i] = 1.0f;

				Qusy::Rect temp;
				temp.setRect(cardRect.posX1, cardRect.posY1+192, cardRect.posX1+156, cardRect.posY1+192+42);

				if(Qusy::Collision(m_mouse, cardRect))
				{
					m_btnOpacity[i] = 1.0f;

					if(Qusy::Collision(m_mouse, temp))
					{
						if(input->IsLButtonDown())
						{
							if(!m_bDrag[PAGE_CARD_NUM+i]) {
								m_statusWindow->setCard(tempCard);
							}
						}
					}
				}
				else
				{
					m_btnOpacity[i] = 0.0f;
				}

			}

			if(Qusy::Collision(m_mouse, cardRect))
			{
				if(m_srcCard == -1)
				{
					if(m_input->IsLButtonDown()) {
						m_bDrag[PAGE_CARD_NUM+i] = true;
						m_srcCard = 10 + i;
					}
				}
				else
				{
					if(m_input->IsLButtonUp()) {
						m_bDrag[PAGE_CARD_NUM+i] = false;
						m_destCard = 10 + i;
					}
				}
			}
		}
	
		if(m_srcCard > -1 && m_destCard > -1)
		{
			CCard* tempCard = NULL;

			if(m_srcCard < 10 && m_destCard < 10)			// 예비 -> 예비
			{
				tempCard = m_changeArray[m_pageNow + m_srcCard];
				m_changeArray[m_pageNow + m_srcCard] = m_changeArray[m_pageNow + m_destCard];
				m_changeArray[m_pageNow + m_destCard] = tempCard;
			
				m_bDrag[m_srcCard] = false;
				m_srcCard = -1;
				m_destCard = -1;
				removeNull();
			}
			else if(m_srcCard < 10 && m_destCard >= 10)		// 예비 -> 메인
			{
				if(CNero::getNero()->GetPartyCardWithSlot(m_destCard-10) != CNero::getNero()->GetCardNero())
				{
					tempCard = m_changeArray[m_pageNow + m_srcCard];
					m_changeArray[m_pageNow + m_srcCard] = CNero::getNero()->GetPartyCardWithSlot(m_destCard-10);
					CNero::getNero()->SetPartyCard(m_destCard-10, tempCard);
			
					m_bDrag[m_srcCard] = false;
					m_srcCard = -1;
					m_destCard = -1;
					removeNull();
				}
				else
				{
					m_bDrag[m_srcCard] = false;
					m_srcCard = -1;
					m_destCard = -1;
				}
			}
			else if(m_srcCard >= 10 && m_destCard < 10)		// 메인 -> 예비
			{
				if(CNero::getNero()->GetPartyCardWithSlot(m_srcCard-10) != CNero::getNero()->GetCardNero())
				{
					tempCard = CNero::getNero()->GetPartyCardWithSlot(m_srcCard-10);
					CNero::getNero()->SetPartyCard(m_srcCard-10, m_changeArray[m_pageNow + m_destCard]);
					m_changeArray[m_pageNow + m_destCard] = tempCard;
			
					m_bDrag[m_srcCard-10+PAGE_CARD_NUM] = false;
					m_srcCard = -1;
					m_destCard = -1;
					removeNull();
				}
				else
				{
					m_bDrag[m_srcCard-10] = false;
					m_srcCard = -1;
					m_destCard = -1;
				}
			}
			else if(m_srcCard >= 10 && m_destCard >= 10)	// 메인 -> 메인
			{
				tempCard = CNero::getNero()->GetPartyCardWithSlot(m_srcCard-10);
				CNero::getNero()->SetPartyCard(m_srcCard-10, CNero::getNero()->GetPartyCardWithSlot(m_destCard-10));
				CNero::getNero()->SetPartyCard(m_destCard-10, tempCard);

				m_bDrag[m_srcCard-10+PAGE_CARD_NUM] = false;
				m_srcCard = -1;
				m_destCard = -1;
				removeNull();
			}
		}
	}
	else
	{
		for(int i=0; i<PAGE_CARD_NUM+4; i++) {
			m_bDrag[i] = false;
			m_srcCard = -1;
			m_destCard = -1;
		}
	}

	if(m_input->IsLButtonUp())
	{
		for(int i=0; i<PAGE_CARD_NUM+4; i++) {
			m_bDrag[i] = false;
		}
		m_srcCard = -1;
		m_destCard = -1;
		removeNull();
	}
}

void CObject_MemberChange::Render()
{
	Qusy::Position pos = getPosition();
	
	float opacity = 1.0f - ((pos.posY * -1)/421.0f);

	m_background->Render(pos.posX, pos.posY, pos.posZ);
	m_shader->Render(m_background->GetTexture(), opacity);

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

	int clickIndex = -1;

	if(m_bShow)
	{
		// 교체창에 가진 카드 깔기
		for(int i=0; i<PAGE_CARD_NUM; i++)
		{
			Qusy::Position renderPosition;
			Qusy::Rect temp;
			int width = 155;
			int height = 173;
			renderPosition.setPosition(100 + (231*i), pos.posY+100, 10);
			temp.setRect(renderPosition.posX, renderPosition.posY, renderPosition.posX+156, renderPosition.posY+234);
			
			if(m_changeArray[(m_pageNow) + i] != NULL)
			{
				if(m_bDrag[i]) {
					m_clickCard = m_changeArray[(m_pageNow) + i];
					clickIndex = i;
				}
				else {
					m_changeArray[(m_pageNow) + i]->CardRender(renderPosition.posX, renderPosition.posY, renderPosition.posZ, width, height, NULL, opacity);
				}
				m_gauge[i]->SetCard(m_changeArray[(m_pageNow) + i]);
				m_gauge[i]->setOpacity(opacity);
				m_gauge[i]->Render(155, 173);
			}
		}
	}
	
	if(CNero::getNero()->IsBattle())
	{
		for(int i=0; i<4; i++)
		{
			Qusy::Position renderPosition;
			renderPosition.setPosition(261 + (200.5f*i) - 12, 470 - 8, 10);
		
			/*
			if(CBattleManager::getBattleManager()->GetTurnCard() == CNero::getNero()->GetPartyCardWithSlot(i))
			{
				if(CBattleManager::getBattleManager()->GetTurnCard() != NULL) {
					m_turn->setPosition(renderPosition.posX, renderPosition.posY, renderPosition.posZ);
					m_turn->Render();
				}
			}
			*/
		}
	}
	// 슬롯창
	for(int i=0; i<4; i++)
	{
		CCard* tempCard = CNero::getNero()->GetPartyCardWithSlot(i);
		Qusy::Position renderPosition;
		Qusy::Rect temp;
		int width = 155;
		int height = 173;
		renderPosition.setPosition(261 + (200.5f*i), 531, 10);
		temp.setRect(renderPosition.posX, renderPosition.posY, renderPosition.posX+155, renderPosition.posY+173);

		if(tempCard != NULL)
		{
			if(m_bDrag[PAGE_CARD_NUM+i])
			{
				m_clickCard = tempCard;
				clickIndex = PAGE_CARD_NUM+i;
			}
			else
			{
				if(tempCard->getHit()) {
					tempCard->CardRender(renderPosition.posX, renderPosition.posY, renderPosition.posZ+10, 155, 173, SHADER::HIT, m_sceneOpacity);
				}
				else {
					tempCard->CardRender(renderPosition.posX, renderPosition.posY, renderPosition.posZ+10, 155, 173, SHADER::TURN, m_sceneOpacity);
				}
				//tempCard->CardRender(renderPosition.posX, renderPosition.posY, renderPosition.posZ+10, 156, 234, NULL, m_sceneOpacity);

				if(m_bActivate) {
					m_statusBtn->Render(renderPosition.posX, renderPosition.posY+192, renderPosition.posZ-2);
					m_statusBtnShader->Render(m_statusBtn->GetTexture(), m_btnOpacity[i]);
				}
			}
			m_gauge[PAGE_CARD_NUM+i]->SetCard(tempCard);
			m_gauge[PAGE_CARD_NUM+i]->setOpacity(m_sceneOpacity);
			m_gauge[PAGE_CARD_NUM+i]->Render(155, 173);
		}
	}
	
	

	if(m_clickCard != NULL && !m_statusWindow->getOpen())
	{
		Qusy::Position renderPosition;
		renderPosition.setPosition(m_mouse.posX-78-5, m_mouse.posY-93, 8);
		m_clickCard->CardRender(renderPosition.posX, renderPosition.posY, renderPosition.posZ-1, 167, 186, NULL, m_sceneOpacity);
		m_gauge[clickIndex]->Render(167, 186);
	}
	
	m_statusWindow->Render();

	m_clickCard = NULL;
}

void CObject_MemberChange::Show(bool show)
{
	m_bShow = show;
}

void CObject_MemberChange::acceptSceneOpacity(float opacity)
{
	m_sceneOpacity = opacity;
}

void CObject_MemberChange::removeNull()
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

void CObject_MemberChange::SetActivate(bool activate)
{
	m_bActivate = activate;
}

bool CObject_MemberChange::GetActivate()
{
	return m_bActivate;
}

bool CObject_MemberChange::GetStatusOpen()
{
	return m_statusWindow->getOpen();
}