#include "..\framework\CInput.h"
#include "..\framework\CTime.h"
#include "..\framework\CFont.h"
#include "..\framework\CBitmap.h"
#include "..\framework\CTextureShader.h"
#include "..\framework\CSound.h"

#include "..\managers\CNero.h"
#include "..\managers\CSceneManager.h"

#include "CCard.h"
#include "CObject_ExploreButton.h"

CObject_ExploreButton::CObject_ExploreButton()
{
	m_button = NULL;
	m_buttonShader = NULL;
	m_result = NULL;
	m_resultShader = NULL;
	for(int i=0; i<5; i++) {
		m_resultMark[i] = NULL;
	}
	m_resultMarkShader = NULL;

	m_sound_Explore = NULL;
	m_sound_Trap = NULL;
	m_sound_Treasure = NULL;

	m_select = -1;
	m_resultNum = -1;
	m_bShow = true;
	m_exploreNow = 0;
	m_exploreMax = 0;
	m_input = NULL;
}

CObject_ExploreButton::~CObject_ExploreButton()
{
}

void CObject_ExploreButton::Initialize()
{
	setPosition(421, 177, 10);

	m_button = new CBitmap();
	m_button->Initialize(L"res/field/field_button.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	m_buttonShader = new CTextureShader();
	m_buttonShader->Initialize(NULL, NULL);

	m_buttonIcon[0] = new CBitmap();
	m_buttonIcon[1] = new CBitmap();
	m_buttonIcon[2] = new CBitmap();

	m_buttonIcon[0]->Initialize(L"res/field/field_icon_town.png",			0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	m_buttonIcon[1]->Initialize(L"res/field/field_icon_explore.png",		0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	m_buttonIcon[2]->Initialize(L"res/field/field_icon_hard_explore.png",	0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	for(int i=0; i<3; i++) {
		m_buttonIconShader[i] = new CTextureShader();
		m_buttonIconShader[i]->Initialize(NULL, NULL);
	}

	m_result = new CBitmap();
	m_result->Initialize(L"res/field/explore_result.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	m_resultShader = new CTextureShader();
	m_resultShader->Initialize(NULL, NULL);

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

	for(int i=0; i<5; i++)
	{
		m_resultTimer[i] = new CTime();
		m_resultTimer[i]->SetTimer(0.01f, false);
	}
	m_text = new CFont();
	m_text->Initialize(L"10X10");

	m_timer = new CTime();
	m_timer->SetTimer(2.0f, false);

	m_sound_Explore = new CSound();
	m_sound_Explore->Initialize("res/sound/se/explore.wav");
	m_sound_Explore->Loop(false);

	m_sound_Trap = new CSound();
	m_sound_Trap->Initialize("res/sound/se/trap.wav");
	m_sound_Trap->Loop(false);

	m_sound_Treasure = new CSound();
	m_sound_Treasure->Initialize("res/sound/se/chest.wav");
	m_sound_Treasure->Loop(false);

	m_rect[0].setRect(getPosition().posX+ 16, getPosition().posY+ 75, getPosition().posX+ 16+122, getPosition().posY+75+148);
	m_rect[1].setRect(getPosition().posX+157, getPosition().posY+ 75, getPosition().posX+157+122, getPosition().posY+75+148);
	m_rect[2].setRect(getPosition().posX+300, getPosition().posY+ 75, getPosition().posX+300+122, getPosition().posY+75+148);
	m_resultValue = 0;
	m_exploreNow = 0;
	m_exploreMax = 0;
}

void CObject_ExploreButton::Shutdown()
{
	if(m_button != NULL)
	{
		m_button->Shutdown();
		SAFE_DELETE(m_button);
	}
	if(m_buttonShader != NULL)
	{
		m_buttonShader->Shutdown();
		SAFE_DELETE(m_buttonShader);
	}
	if(m_result != NULL)
	{
		m_result->Shutdown();
		SAFE_DELETE(m_result);
	}
	if(m_resultShader != NULL)
	{
		m_resultShader->Shutdown();
		SAFE_DELETE(m_resultShader);
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
	for(int i=0; i<5; i++)
	{
		if(m_resultTimer[i] != NULL)
		{
			m_resultTimer[i]->StopTimer();
			SAFE_DELETE(m_resultTimer[i]);
		}
	}
	if(m_timer != NULL)
	{
		m_timer->StopTimer();
		SAFE_DELETE(m_timer);
	}
	if(m_sound_Explore != NULL)
	{
		m_sound_Explore->Release();
		SAFE_DELETE(m_sound_Explore);
	}
	if(m_sound_Trap != NULL)
	{
		m_sound_Trap->Release();
		SAFE_DELETE(m_sound_Trap);
	}
	if(m_sound_Treasure != NULL)
	{
		m_sound_Treasure->Release();
		SAFE_DELETE(m_sound_Treasure);
	}
	m_bShow = false;
}

void CObject_ExploreButton::Update(CInput* input)
{
	m_input = input;
	Qusy::Point mouse;
	input->GetMousePoint(mouse.posX, mouse.posY);

	m_select = -1;
	m_resultNum = -1;

	if(m_bShow)
	{
		bool result[5] = {false,};
		for(int i=0; i<5; i++) {
			result[i] = m_resultTimer[i]->GetTimer();
		}

		if(result[0] && result[1] && result[2] && result[3] && result[4])
		{
			if(Qusy::Collision(mouse, m_rect[0]))
			{
				if(input->IsLButtonUp())
				{
					if(Qusy::Collision(mouse, m_rect[0]))
					{
						// 마을
						m_select = 0;
						m_resultNum = 100;
					}
				}
			}
			else if(Qusy::Collision(mouse, m_rect[1]))
			{
				if(input->IsLButtonUp())
				{
					// 탐색
					m_sound_Explore->Reset();
					m_sound_Explore->Play();
					
					m_sound_Treasure->Reset();
					m_sound_Trap->Reset();

					m_exploreMax = 30;
					Show(false);

					CNero::getNero()->m_numExplore++;

					m_select = 1;

					if(CNero::getNero()->GetExploreNero() == BOSS1_PLACE || CNero::getNero()->GetExploreNero() == BOSS2_PLACE)
					{
						m_resultNum = RESULT::BATTLE;
					}
					else
					{
						int temp = rand()%100;

						if(temp < 50)
						{
							m_resultNum = RESULT::BATTLE;
						}
						else if(temp >=50 && temp < 80)
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
							
							m_resultNum = RESULT::TREASURE;
							CNero::getNero()->m_numGoldChest++;
							CNero::getNero()->SetGold(CNero::getNero()->GetGold()+m_resultValue);
						}
						else
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
							m_resultNum = RESULT::TRAP;
							m_resultTarget->setHp(m_resultTarget->getStat().m_hp - m_resultValue);
						}
					}
					for(int i=0; i<5; i++)
					{
						if(!m_resultTimer[i]->GetTimer()) {
							m_resultTimer[i]->StopTimer();
						}
					}
					m_resultTimer[m_resultNum]->SetTimer(2.8f, false);
					
				}
			}
			else if(Qusy::Collision(mouse, m_rect[2]))
			{
				if(input->IsLButtonUp())
				{
					// 강행군
					m_sound_Explore->Reset();
					m_sound_Explore->Play();

					m_sound_Treasure->Reset();
					m_sound_Trap->Reset();

					CNero::getNero()->SetSoul(CNero::getNero()->GetSoul()-1);
					m_exploreMax = 80;
					Show(false);
					
					CNero::getNero()->m_numExplore++;
					
					m_select = 2;

					if(CNero::getNero()->GetExploreNero() == BOSS1_PLACE || CNero::getNero()->GetExploreNero() == BOSS2_PLACE)
					{
						m_resultNum = RESULT::BATTLE;
					}
					else
					{
						int temp = rand()%100;

						if(temp < 50)
						{
							m_resultNum = RESULT::BATTLE;
						}
						else if(temp >=50 && temp < 80)
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

							m_resultNum = RESULT::TREASURE;
							CNero::getNero()->m_numGoldChest++;
							if(CNero::getNero()->m_numGoldChest == 3) {
								CNero::getNero()->SetStoryProgress(STORY::STORY06);
							}
							CNero::getNero()->SetGold(CNero::getNero()->GetGold()+m_resultValue);
						}
						else
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
							m_resultNum = RESULT::TRAP;
							m_resultTarget->setHp(m_resultTarget->getStat().m_hp - m_resultValue);
						}
					}
					for(int i=0; i<5; i++)
					{
						if(!m_resultTimer[i]->GetTimer()) {
							m_resultTimer[i]->StopTimer();
						}
					}
					m_resultTimer[m_resultNum]->SetTimer(2.8f, false);
				}
			}
			else if(input->IsKeyDown(VK_NUMPAD6))
			{
				CNero::getNero()->SetBossProgress(BOSS::SHOA);
				m_resultNum = RESULT::BATTLE;

				for(int i=0; i<5; i++)
				{
					if(!m_resultTimer[i]->GetTimer()) {
						m_resultTimer[i]->StopTimer();
					}
				}
				m_resultTimer[m_resultNum]->SetTimer(2.8f, false);
			}
			else if(input->IsKeyDown(VK_NUMPAD7))
			{
				CNero::getNero()->SetBossProgress(BOSS::GOD);
				m_resultNum = RESULT::BATTLE;

				for(int i=0; i<5; i++)
				{
					if(!m_resultTimer[i]->GetTimer()) {
						m_resultTimer[i]->StopTimer();
					}
				}
				m_resultTimer[m_resultNum]->SetTimer(2.8f, false);
			}
			else
			{
				m_resultNum = -1;
			}
		}
	}

	if(m_exploreMax == 30)
	{
		if(m_exploreNow < m_exploreMax)
		{
			CNero::getNero()->SetExploreNero(CNero::getNero()->GetExploreNero()+0.5f);
			m_exploreNow++;

			if(CNero::getNero()->GetGameProgress() == PROGRESS::STAGE1)
			{
				if(CNero::getNero()->GetExploreNero() + 15-(0.5f * m_exploreNow) >= BOSS1_PLACE) {
					CNero::getNero()->SetBossProgress(BOSS::LUPUS);
					CNero::getNero()->SetStoryProgress(STORY::STORY08);
				}
			}
			else if(CNero::getNero()->GetGameProgress() == PROGRESS::STAGE2)
			{
				if(CNero::getNero()->GetExploreNero() + 15-(0.5f * m_exploreNow) >= BOSS2_PLACE) {
					CNero::getNero()->SetExploreNero(BOSS2_PLACE);
					CNero::getNero()->SetBossProgress(BOSS::SUCCUBUS);
				}
				else if(CNero::getNero()->GetExploreNero() >= CNero::getNero()->GetExploreHero())
				{
					CNero::getNero()->SetBossProgress(BOSS::SHOA);
				}
			}
		}
		else
		{
			m_exploreNow = 0;
			m_exploreMax = 0;
		}
	}
	else if(m_exploreMax == 80)
	{
		if(m_exploreNow < m_exploreMax)
		{
			CNero::getNero()->SetExploreNero(CNero::getNero()->GetExploreNero()+0.5f);
			m_exploreNow++;
			if(CNero::getNero()->GetGameProgress() == PROGRESS::STAGE1)
			{
				if(CNero::getNero()->GetExploreNero() + 40-(0.5f * m_exploreNow) >= BOSS1_PLACE) {
					CNero::getNero()->SetBossProgress(BOSS::LUPUS);
				}
			}
			else if(CNero::getNero()->GetGameProgress() == PROGRESS::STAGE2)
			{
				if(CNero::getNero()->GetExploreNero() + 40-(0.5f * m_exploreNow) >= BOSS2_PLACE) {
					CNero::getNero()->SetExploreNero(BOSS2_PLACE);
					CNero::getNero()->SetBossProgress(BOSS::SUCCUBUS);
				}
				else if(CNero::getNero()->GetExploreNero() >= CNero::getNero()->GetExploreHero())
				{
					if(CNero::getNero()->m_bShoa) {
						CNero::getNero()->SetBossProgress(BOSS::SHOA);
					}
				}
			}
		}
		else
		{
			m_exploreNow = 0;
			m_exploreMax = 0;
		}
	}
}

void CObject_ExploreButton::Render()
{
	Qusy::Position pos = getPosition();
	Qusy::Position resultPos;
	float opacity = getOpacity();
	
	if(m_bShow) {
		opacity = getOpacity();
	}
	else {
		opacity = 0.0f;
	}
	
	resultPos.setPosition(373, 120, 8);
	
	if(!m_resultTimer[RESULT::BATTLE]->GetTimer())
	{
		//if(m_resultTimer[RESULT::BATTLE]->RemainTime() >= 1.75f)
		//{
			m_result->Render(resultPos.posX, resultPos.posY, resultPos.posZ, 1.0f, 1.0f);
			m_resultShader->Render(m_result->GetTexture(), opacity);
			m_resultMark[RESULT::BATTLE]->Render(resultPos.posX+200, resultPos.posY+61, resultPos.posZ, 1.0f, 1.0f);
			m_resultMarkShader->Render(m_resultMark[RESULT::BATTLE]->GetTexture(), opacity);

			m_text->Draw(L"전투 개시",	34, resultPos.posX+270, resultPos.posY+245, GetColor(255, 255, 255, (UINT8)(opacity*255.0f)), NULL);
		//}
	}
	else if(!m_resultTimer[RESULT::WON]->GetTimer())
	{
		if(m_resultTimer[RESULT::WON]->RemainTime() <= 2.00f)
		{
			m_result->Render(resultPos.posX, resultPos.posY, resultPos.posZ, 1.0f, 1.0f);
			m_resultShader->Render(m_result->GetTexture(), opacity);
			m_resultMark[RESULT::WON]->Render(resultPos.posX+200, resultPos.posY+61, resultPos.posZ, 1.0f, 1.0f);
			m_resultMarkShader->Render(m_resultMark[RESULT::WON]->GetTexture(), opacity);

			int temp = 1;
			WCHAR soul[15]	= {NULL,};	wsprintf(soul, L"영혼 %d개를 얻었다.", temp);

			m_text->Draw(L"전투 승리",	28, resultPos.posX+270, resultPos.posY+225, GetColor(255, 255, 255, (UINT8)(opacity*255.0f)), NULL);
			m_text->Draw(soul,			28, resultPos.posX+270, resultPos.posY+262, GetColor(255, 255, 255, (UINT8)(opacity*255.0f)), NULL);
		}
	}
	else if(!m_resultTimer[RESULT::LOST]->GetTimer())
	{
		if(m_resultTimer[RESULT::LOST]->RemainTime() <= 2.00f)
		{
			m_result->Render(resultPos.posX, resultPos.posY, resultPos.posZ, 1.0f, 1.0f);
			m_resultShader->Render(m_result->GetTexture(), opacity);
			m_resultMark[RESULT::LOST]->Render(resultPos.posX+200, resultPos.posY+61, resultPos.posZ, 1.0f, 1.0f);
			m_resultMarkShader->Render(m_resultMark[RESULT::LOST]->GetTexture(), opacity);

			m_text->Draw(L"전투 패배",			28, resultPos.posX+270, resultPos.posY+225, GetColor(255, 255, 255, (UINT8)(opacity*255.0f)), NULL);
			m_text->Draw(L"마을로 돌아갑니다.",	28, resultPos.posX+270, resultPos.posY+262, GetColor(255, 255, 255, (UINT8)(opacity*255.0f)), NULL);

		}
	}
	else if(!m_resultTimer[RESULT::TREASURE]->GetTimer())
	{
		if(m_resultTimer[RESULT::TREASURE]->RemainTime() <= 1.8f)
		{
			m_sound_Treasure->Play();
			m_result->Render(resultPos.posX, resultPos.posY, resultPos.posZ, 1.0f, 1.0f);
			m_resultShader->Render(m_result->GetTexture(), opacity);
			m_resultMark[RESULT::TREASURE]->Render(resultPos.posX+200, resultPos.posY+61, resultPos.posZ, 1.0f, 1.0f);
			m_resultMarkShader->Render(m_resultMark[RESULT::TREASURE]->GetTexture(), opacity);

			WCHAR gold[14]		= {NULL,};	wsprintf(gold, L"%d 골드 획득!", m_resultValue);
			m_text->Draw(gold, 30, resultPos.posX+270, resultPos.posY+250, GetColor(255, 255, 255, (UINT8)(opacity*255.0f)), NULL);
		}
	}
	else if(!m_resultTimer[RESULT::TRAP]->GetTimer())
	{
		if(m_resultTimer[RESULT::TRAP]->RemainTime() <= 1.8f)
		{
			m_sound_Trap->Play();
			m_result->Render(resultPos.posX, resultPos.posY, resultPos.posZ, 1.0f, 1.0f);
			m_resultShader->Render(m_result->GetTexture(), opacity);
			m_resultMark[RESULT::TRAP]->Render(resultPos.posX+202, resultPos.posY+61, resultPos.posZ, 1.0f, 1.0f);
			m_resultMarkShader->Render(m_resultMark[RESULT::TRAP]->GetTexture(), opacity);
		
			WCHAR name[6]		= {NULL,};	lstrcpy(name, m_resultTarget->getCardName());
			WCHAR damage[12]	= {NULL,};	wsprintf(damage, L"%d의 데미지", m_resultValue);

			m_text->Draw(L"함정에 걸렸다!!!", 28, resultPos.posX+270, resultPos.posY+225, GetColor(255, 255, 255, (UINT8)(opacity*255.0f)), NULL);

			m_text->Draw(name,			26, resultPos.posX+270 - 116, resultPos.posY+261, GetColor(255, 255, 255, 255), FW1_RIGHT|FW1_VCENTER);
			m_text->Draw(L"는(은)",		26, resultPos.posX+270 - 114, resultPos.posY+261, GetColor(255, 255, 255, 255), FW1_LEFT|FW1_VCENTER);
			m_text->Draw(damage,		26, resultPos.posX+270 +  99, resultPos.posY+262, GetColor(255,  55,  55, 255), FW1_RIGHT|FW1_VCENTER);
			m_text->Draw(L"를 입었다.", 26, resultPos.posX+270 + 101, resultPos.posY+261, GetColor(255, 255, 255, 255), FW1_LEFT|FW1_VCENTER);
		}
	}
	else
	{
		m_button->Render(pos.posX, pos.posY, pos.posZ, 1.0f, 1.0f);
		m_buttonShader->Render(m_button->GetTexture(), opacity);

		Qusy::Point mouse;
		m_input->GetMousePoint(mouse.posX, mouse.posY);

		for(int i=0; i<3; i++)
		{
			if(i==0) {
				m_buttonIcon[0]->Render(pos.posX+ 30, pos.posY+ 91, pos.posZ-1);
			}
			else if(i==1) {
				m_buttonIcon[1]->Render(pos.posX+165, pos.posY+ 91, pos.posZ-1);
			}
			else if(i==2) {
				m_buttonIcon[2]->Render(pos.posX+310, pos.posY+ 91, pos.posZ-1);
			}

			if(Qusy::Collision(mouse, m_rect[i])) {
				m_buttonIconShader[i]->Render(m_buttonIcon[i]->GetTexture(), opacity);
			}
			else {
				m_buttonIconShader[i]->Render(m_buttonIcon[i]->GetTexture(), opacity*0.5f);
			}
		}
	}
}

int CObject_ExploreButton::getSelect()
{
	return m_resultNum;
}

void CObject_ExploreButton::Show(bool show)
{
	m_bShow = show;
}

void CObject_ExploreButton::setBattleResult(int result)
{
	if(result == RESULT::WON)
	{
		m_resultNum = RESULT::WON;
		m_resultTimer[m_resultNum]->SetTimer(2.8f, false);
	}
	else if(result == RESULT::LOST)
	{
		m_resultNum = RESULT::LOST;
		m_resultTimer[m_resultNum]->SetTimer(2.8f, false);
	}
	else
	{
		m_resultNum = -1;
	}
}