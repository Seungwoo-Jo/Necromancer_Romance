// ..\framework
#include "..\framework\CTime.h"
#include "..\framework\CInput.h"
#include "..\framework\common.h"
#include "..\framework\CBitmap.h"
#include "..\framework\CTextureShader.h"
#include "..\framework\CFont.h"

#include "..\managers\CNero.h"

// ..\objects
#include "CCard.h"
#include "CObject_Status.h"
#include "CObject_Cardgauge.h"

CObject_Status::CObject_Status()
{
	m_status = NULL;
	m_story = NULL;
	m_shader[0] = NULL;
	m_shader[1] = NULL;
	m_gauge = NULL;
	m_bStatus = false;
	m_bOpen = false;
	m_timer = NULL;
	m_text = NULL;
}

CObject_Status::CObject_Status(const CObject_Status& object)
{
}

CObject_Status::~CObject_Status()
{
}

void CObject_Status::Initalize(CCard* card)
{
	setPosition(0, 0, 3);
	m_card = card;

	m_status = new CBitmap();
	m_status->Initialize(L"res/status_stat.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	m_story = new CBitmap();
	m_story->Initialize(L"res/status_story.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	m_shader[0] = new CTextureShader();
	m_shader[0]->Initialize(NULL, NULL);

	m_shader[1] = new CTextureShader();
	m_shader[1]->Initialize(NULL, NULL);

	m_type[CARDTYPE::SWORD] = new CBitmap();
	m_type[CARDTYPE::SWORD]->Initialize(L"res/type/card_sword.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	m_type[CARDTYPE::SPEAR] = new CBitmap();
	m_type[CARDTYPE::SPEAR]->Initialize(L"res/type/card_spear.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	m_type[CARDTYPE::BLUNT] = new CBitmap();
	m_type[CARDTYPE::BLUNT]->Initialize(L"res/type/card_blunt.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	m_type[CARDTYPE::BOW] = new CBitmap();
	m_type[CARDTYPE::BOW]->Initialize(L"res/type/card_bow.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	m_type[CARDTYPE::MAGIC] = new CBitmap();
	m_type[CARDTYPE::MAGIC]->Initialize(L"res/type/card_magic.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	m_typeShader = new CTextureShader();
	m_typeShader->Initialize(NULL, NULL);

	m_powerUp = new CBitmap();
	m_powerUp->Initialize(L"res/btn_powerup.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	m_powerUpShader = new CTextureShader();
	m_powerUpShader->Initialize(NULL, NULL);

	m_gauge = new CObject_Cardgauge();
	m_gauge->Initalize(NULL);

	m_timer = new CTime();
	m_timer->SetTimer(0.2f, false);

	m_text = new CFont();
	m_text->Initialize(L"10X10");

	m_finalSize.setRect(400, 92, 880, 628);
}

void CObject_Status::Shutdown()
{
	if(m_status != NULL)
	{
		m_status->Shutdown();
		SAFE_DELETE(m_status);
	}
	if(m_story != NULL)
	{
		m_story->Shutdown();
		SAFE_DELETE(m_story);
	}
	for(int i=0; i<2; i++)
	{
		if(m_shader[i] != NULL)
		{
			m_shader[i]->Shutdown();
			SAFE_DELETE(m_shader[i]);
		}
	}
	for(int i=0; i<5; i++)
	{
		if(m_type[i] != NULL)
		{
			m_type[i]->Shutdown();
			SAFE_DELETE(m_type[i]);
		}
	}
	if(m_typeShader != NULL)
	{
		m_typeShader->Shutdown();
		SAFE_DELETE(m_typeShader);
	}
	if(m_powerUp != NULL)
	{
		m_powerUp->Shutdown();
		SAFE_DELETE(m_powerUp);
	}
	if(m_powerUpShader != NULL)
	{
		m_powerUpShader->Shutdown();
		SAFE_DELETE(m_powerUpShader);
	}
	if(m_gauge != NULL)
	{
		m_gauge->Shutdown();
		SAFE_DELETE(m_gauge);
	}
	if(m_timer != NULL)
	{
		m_timer->StopTimer();
		SAFE_DELETE(m_timer);
	}
	if(m_text != NULL)
	{
		m_text->Shutdown();
		SAFE_DELETE(m_text);
	}
	
}

void CObject_Status::Update(CInput* input)
{
	Qusy::Point mouse;
	input->GetMousePoint(mouse.posX, mouse.posY);

	if(m_card != NULL)
	{
		//m_card->GetCardRect(m_currentRect);

		int dX1 = (int)((double)(m_finalSize.posX1-m_firstSize.posX1)/12);
		int dY1 = (int)((double)(m_finalSize.posY1-m_firstSize.posY1)/12);
		int dX2 = (int)((double)(m_finalSize.posX2-m_firstSize.posX2)/12);
		int dY2 = (int)((double)(m_finalSize.posY2-m_firstSize.posY2)/12);

		if(m_bOpen)
		{
			if(m_currentRect.posY1 > 92)
			{
				m_currentRect.posX1 += dX1;
				m_currentRect.posY1 += dY1;
				m_currentRect.posX2 += dX2;
				m_currentRect.posY2 += dY2;

				if(m_timer->GetTimer()) {
					m_timer->SetTimer(0.55f, false);
				}

				if(m_currentRect.posY1 <= 92)
				{
					m_currentRect.posX1 = 400;
					//m_currentRect.posY1 = 0;
					m_currentRect.posY1 = 92;
					m_currentRect.posX2 = 880;
					//m_currentRect.posY2 = 720;
					m_currentRect.posY2 = 628;
				}
			}
			
			else
			{
				m_bStatus = true;
			}
			
		}
		else
		{
			if(m_currentRect.posY1 < m_firstSize.posY1)
			{
				m_currentRect.posX1 -= dX1;
				m_currentRect.posY1 -= dY1;
				m_currentRect.posX2 -= dX2;
				m_currentRect.posY2 -= dY2;

				if(m_currentRect.posY1 >= m_firstSize.posY1)
				{
					m_currentRect.posX1 = m_firstSize.posX1;
					m_currentRect.posY1 = m_firstSize.posY1;
					m_currentRect.posX2 = m_firstSize.posX2;
					m_currentRect.posY2 = m_firstSize.posY2;
				}
			}
			if(m_timer->GetTimer())
			{
				m_bStatus = false;
			}
		}


		if(input->IsRButtonUp())
		{
			m_bStatus = false;
			m_bOpen = false;

			if(!m_timer->GetTimer()) {
				m_timer->SetTimer(0.25f, false);
			}
		}

		Qusy::Rect temp;
		m_powerUp->GetRect(temp);

		if(Qusy::Collision(mouse, temp))
		{
			if(input->IsLButtonUp())
			{
				if(CNero::getNero()->GetSoul() > 0) {
					CNero::getNero()->SetSoul(CNero::getNero()->GetSoul() -1);
					m_card->PowerUp();
				}
			}
		}
	}
}

void CObject_Status::Render()
{
	bool bTextRender = false;
	Qusy::Position pos = getPosition();

	if(m_bStatus)
	{	
		float statusX = 0;
		float storyX = 0;
		if(m_bOpen) {
			if(statusX < 0) {
				statusX = 0;
			}
			else {
				statusX = 400 - ((1.0f - (m_timer->RemainTime()/(m_timer->GetSetTime()-0.2f))) * 400.0f);
			}
			if(storyX > 880) {
				storyX = 880;
			}
			else {
				storyX = 480 + ((1.0f - (m_timer->RemainTime()/(m_timer->GetSetTime()-0.2f))) * 400.0f);
			}

			bTextRender = true;
		}

		m_status->Render((int)statusX, 0, 2);
		m_shader[0]->Render(m_status->GetTexture(), getOpacity());

		m_story->Render((int)storyX, 0, 2);
		m_shader[1]->Render(m_story->GetTexture(), getOpacity());

		if(bTextRender)
		{
			WCHAR hp[5]		= {NULL,};		wsprintf(hp,	L"%d", m_card->getStat().m_hp);
			WCHAR maxHp[5]	= {NULL,};		wsprintf(maxHp, L"%d", m_card->getStat().m_maxHp);
			WCHAR ap[5]		= {NULL,};		wsprintf(ap,	L"%d", m_card->getStat().m_ap);
			WCHAR maxAp[5]	= {NULL,};		wsprintf(maxAp, L"%d", m_card->getStat().m_maxAp);
			WCHAR atk[5]	= {NULL,};		wsprintf(atk,	L"%d", m_card->getStat().m_atk);
			WCHAR def[5]	= {NULL,};		wsprintf(def,	L"%d", m_card->getStat().m_def);
			WCHAR spd[5]	= {NULL,};		lstrcpy(spd, m_card->getSpdText());

			

			m_text->Draw(hp,	24, statusX+220, 112, GetColor(255, 255, 255, 255), NULL);
			m_text->Draw(maxHp, 24, statusX+290, 112, GetColor(255, 255, 255, 255), NULL);
			m_text->Draw(ap,	24, statusX+220, 160, GetColor(255, 255, 255, 255), NULL);
			m_text->Draw(maxAp, 24, statusX+290, 160, GetColor(255, 255, 255, 255), NULL);
			m_text->Draw(atk,	24, statusX+255, 210, GetColor(255, 255, 255, 255), NULL);
			m_text->Draw(def,	24, statusX+255, 262, GetColor(255, 255, 255, 255), NULL);
			m_text->Draw(spd,	24, statusX+255, 312, GetColor(255, 255, 255, 255), NULL);


			m_type[m_card->getType()]->Render((int)statusX+35, 570, 5, 1.49f, 1.49f);
			m_typeShader->Render(m_type[m_card->getType()]->GetTexture(), 1.0f);

			m_powerUp->Render((int)statusX+113, 340, 5, 1.0f, 1.0f);
			m_powerUpShader->Render(m_powerUp->GetTexture(), 1.0f);

			WCHAR skill1Name[10] = {NULL,};	lstrcpy(skill1Name, m_card->getSkillName(0));
			WCHAR skill2Name[10] = {NULL,};	lstrcpy(skill2Name, m_card->getSkillName(1));
			WCHAR skill3Name[10] = {NULL,};	lstrcpy(skill3Name, m_card->getSkillName(2));
			WCHAR skill1Ap[4]	= {NULL,};	wsprintf(skill1Ap,	L"%d", m_card->getUseAp(0));
			WCHAR skill2Ap[4]	= {NULL,};	wsprintf(skill2Ap,	L"%d", m_card->getUseAp(1));
			WCHAR skill3Ap[4]	= {NULL,};	wsprintf(skill3Ap,	L"%d", m_card->getUseAp(2));

			m_text->Draw(skill1Name,	20, statusX+185, 417, GetColor(255, 255, 255, 255), NULL);
			m_text->Draw(skill2Name,	20, statusX+105, 464, GetColor(255, 255, 255, 255), NULL);
			m_text->Draw(skill3Name,	20, statusX+262, 464, GetColor(255, 255, 255, 255), NULL);
			m_text->Draw(skill1Ap,		20, statusX+254, 417, GetColor(255, 255, 255, 255), NULL);
			m_text->Draw(skill2Ap,		20, statusX+175, 464, GetColor(255, 255, 255, 255), NULL);
			m_text->Draw(skill3Ap,		20, statusX+333, 464, GetColor(255, 255, 255, 255), NULL);
		}
	}
	if(m_card != NULL && getOpen())
	{
		m_card->CardRender(m_currentRect.posX1, m_currentRect.posY1, 2, m_currentRect.posX2-m_currentRect.posX1, m_currentRect.posY2-m_currentRect.posY1, NULL, getOpacity());
		m_gauge->SetCard(m_card);
		m_gauge->Render(m_currentRect.posX2-m_currentRect.posX1, m_currentRect.posY2-m_currentRect.posY1);
	}
}

void CObject_Status::setCard(CCard* card)
{
	m_card = card;

	if(card != NULL) {
		m_card->GetCardRect(m_firstSize);
		m_card->GetCardRect(m_currentRect);
		//m_finalSize.setRect(400, 0, 880, 720);
		m_finalSize.setRect(400, 92, 880, 628);
		
		
		setOpen(true);
	}
}
CCard* CObject_Status::getCard()
{
	return m_card;
}
void CObject_Status::setOpen(bool open)
{
	m_bOpen = open;
}

bool CObject_Status::getOpen()
{
	if(m_currentRect.posY1 < m_firstSize.posY1)
	{
		return true;
	}
	return m_bOpen;
}