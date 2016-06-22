// ..\framework
#include "..\framework\CInput.h"
#include "..\framework\common.h"
#include "..\framework\CBitmap.h"
#include "..\framework\CTextureShader.h"
#include "..\framework\CFont.h"

// ..\managers
#include "..\managers\CNero.h"
#include "..\managers\CBattleManager.h"

// ..\objects
#include "CObject_Skillselect.h"
#include "CMonster.h"
#include "CSkill.h"
#include "CCard.h"

CObject_Skillselect::CObject_Skillselect()
{
	m_skillButton[0] = NULL;
	m_skillButton[1] = NULL;
	m_skillButton[2] = NULL;
	m_skillButton[3] = NULL;
	m_skillButtonOver = NULL;
	m_shader = NULL;
	m_skillText = NULL;

	for(int i=0; i<4; i++) {
		m_over[i] = false;
	}
}

CObject_Skillselect::CObject_Skillselect(const CObject_Skillselect& object)
{
}

CObject_Skillselect::~CObject_Skillselect()
{
}

void CObject_Skillselect::Initalize()
{
	setPosition(358, 280, 10);

	for(int i=0; i<4; i++)
	{
		m_skillButton[i] = new CBitmap();
		m_skillButton[i]->Initialize(L"res/battle/skill_button_normal.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	}

	m_skillButtonOver = new CBitmap();
	m_skillButtonOver->Initialize(L"res/battle/skill_button_over.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	m_shader = new CTextureShader();
	m_shader->Initialize(NULL, NULL);

	m_skillText = new CFont();
	m_skillText->Initialize(L"10X10");

	for(int i=0; i<4; i++) {
		m_over[i] = false;
	}
}

void CObject_Skillselect::Shutdown()
{
	for(int i=0; i<4; i++)
	{
		if(m_skillButton != NULL)
		{
			m_skillButton[i]->Shutdown();
			SAFE_DELETE(m_skillButton[i]);
		}
	}
	if(m_shader != NULL)
	{
		m_shader->Shutdown();
		SAFE_DELETE(m_shader);
	}

	if(m_skillText != NULL)
	{
		m_skillText->Shutdown();
		SAFE_DELETE(m_skillText);
	}
}

void CObject_Skillselect::Update(CInput* input)
{
	Qusy::Point mouse;
	Qusy::Position pos = getPosition();
	Qusy::Rect skillBtn[4];
	input->GetMousePoint(mouse.posX, mouse.posY);
	for(int i=0; i<4; i++) {
		m_skillButton[i]->GetRect(skillBtn[i]);
	}
	/*
	skillBtn[0].setRect(pos.posX+0, pos.posY+25, pos.posX+186, pos.posY+72);
	skillBtn[1].setRect(pos.posX+189, pos.posY+0, pos.posX+375, pos.posY+47);
	skillBtn[2].setRect(pos.posX+378, pos.posY+25, pos.posX+564, pos.posY+72);
	skillBtn[3].setRect(pos.posX+189, pos.posY+50, pos.posX+375, pos.posY+97);
	*/

	for(int i=0; i<4; i++)
	{
		if(Qusy::Collision(mouse, skillBtn[i]))
		{
			m_over[i] = true;

			if(input->IsLButtonUp())
			{
				CMonster* tempMonster = CBattleManager::getBattleManager()->GetMonster();
				if(tempMonster->getStat().m_hp > 0)
				{
					CCard* tempCard = CBattleManager::getBattleManager()->GetTurnCard();
					if(tempCard != NULL)
					{
						if(i == 3) {
							tempCard->setTurnTimer();
							CBattleManager::getBattleManager()->TurnCardDequeue();
							if(CNero::getNero()->GetRotate() < 3) {
								CNero::getNero()->SetRotate(CNero::getNero()->GetRotate()+1);
							}
						}
						else 
						{
							int damage = tempCard->UseSkill(i);
							if(damage != -10) {
								tempCard->setTurnTimer();
								CBattleManager::getBattleManager()->TurnCardDequeue();
							}
						}
					}
				}
			}
		}
		else
		{
			m_over[i] = false;
		}
	}
}

void CObject_Skillselect::Render()
{
	CCard* tempCard = CBattleManager::getBattleManager()->GetTurnCard();
	if(tempCard != NULL)
	{
		for(int i=0; i<4; i++)
		{
			if(tempCard == CNero::getNero()->GetPartyCardWithSlot(i))
			{
				setPosition(261 + (200.5f*i), 431, getPosition().posZ);
			}
		}

		Qusy::Position pos = getPosition();

		for(int i=0; i<4; i++)
		{
			if(!m_over[i])
			{
				m_skillButton[i]->Render(pos.posX, pos.posY+(25*i), pos.posZ, 1.0f, 1.0f);
				m_shader->Render(m_skillButton[i]->GetTexture(), getOpacity());
			}
			else
			{
				m_skillButtonOver->Render(pos.posX, pos.posY+(25*i), pos.posZ, 1.0f, 1.0f);
				m_shader->Render(m_skillButton[i]->GetTexture(), getOpacity());
			}
		}

		WCHAR skill1Name[10] = {NULL,};	lstrcpy(skill1Name, tempCard->getSkillName(0));
		WCHAR skill2Name[10] = {NULL,};	lstrcpy(skill2Name, tempCard->getSkillName(1));
		WCHAR skill3Name[10] = {NULL,};	lstrcpy(skill3Name, tempCard->getSkillName(2));
		WCHAR skill4Name[10] = {NULL,}; lstrcpy(skill4Name, L"´ë±â");

		WCHAR skill1Ap[4]	= {NULL,};	wsprintf(skill1Ap,	L"%d", tempCard->getUseAp(0));
		WCHAR skill2Ap[4]	= {NULL,};	wsprintf(skill2Ap,	L"%d", tempCard->getUseAp(1));
		WCHAR skill3Ap[4]	= {NULL,};	wsprintf(skill3Ap,	L"%d", tempCard->getUseAp(2));

		m_skillText->Draw(skill1Name,	18, pos.posX+56, pos.posY+ 0+14, GetColor(255, 255, 255, (UINT8)(getOpacity()*255)), NULL);
		m_skillText->Draw(skill2Name,	18, pos.posX+56, pos.posY+25+14, GetColor(255, 255, 255, (UINT8)(getOpacity()*255)), NULL);
		m_skillText->Draw(skill3Name,	18, pos.posX+56, pos.posY+50+14, GetColor(255, 255, 255, (UINT8)(getOpacity()*255)), NULL);
		m_skillText->Draw(skill4Name,	18, pos.posX+56, pos.posY+75+14, GetColor(255, 255, 255, (UINT8)(getOpacity()*255)), NULL);

		m_skillText->Draw(skill1Ap,		18, pos.posX+134, pos.posY+ 0+14, GetColor(255, 255, 255, (UINT8)(getOpacity()*255)), NULL);
		m_skillText->Draw(skill2Ap,		18, pos.posX+134, pos.posY+25+14, GetColor(255, 255, 255, (UINT8)(getOpacity()*255)), NULL);
		m_skillText->Draw(skill3Ap,		18, pos.posX+134, pos.posY+50+14, GetColor(255, 255, 255, (UINT8)(getOpacity()*255)), NULL);
	}
}