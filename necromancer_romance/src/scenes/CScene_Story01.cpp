#include <thread>

// ..\framework
#include "..\framework\CBitmap.h"
#include "..\framework\CTextureShader.h"
#include "..\framework\CInput.h"
#include "..\framework\common.h"
#include "..\framework\CFont.h"
#include "..\framework\CTime.h"
#include "..\framework\CSound.h"

// ..\managers
#include "..\managers\CObjectManager.h"
#include "..\managers\CSceneManager.h"
#include "..\managers\CBattleManager.h"
#include "..\managers\CCardManager.h"
#include "..\managers\CMonsterManager.h"
#include "..\managers\CScriptManager.h"
#include "..\managers\CNero.h"

// ..\objects
#include "..\objects\CObject_Background.h"
#include "..\objects\CObject_Chain.h"
#include "..\objects\CObject_Monstergauge.h"
#include "..\objects\CObject_Skillselect.h"
#include "..\objects\CObject_PartySlot.h"
#include "..\objects\CObject_MemberChange.h"
#include "..\objects\CObject_Target.h"
#include "..\objects\CObject_ExploreBar.h"
#include "..\objects\CObject_ExploreButton.h"
#include "..\objects\CObject_TalkWindow.h"
#include "..\objects\CCard.h"
#include "..\objects\CMonster.h"

// ..\scenes
#include "CScene_Story01.h"

CScene_Story01::CScene_Story01()
{
	m_stage1Walk		= NULL;
	m_stage1BossWalk	= NULL;
	m_walkShader		= NULL;
	m_stage1Bg			= NULL;
	m_stage1BossBg		= NULL;
	m_chain				= NULL;
	m_Text				= NULL;
	m_fadeTimer			= NULL;
	m_monsterGauge		= NULL;
	//m_exploreBar		= NULL;
	//m_exploreBtn		= NULL;
	m_talkWindow		= NULL;
	m_resultTimer		= NULL;
	m_battleTimer		= NULL;
	m_walkTimer			= NULL;
	m_sound_Move		= NULL;
	m_bgm_stage1		= NULL;
	m_bgm_stage1_boss	= NULL;
	m_bFadeIn			= true;
	m_bExplore			= true;
	m_bBattle			= false;
	m_bTresure			= false;
	m_bTrap				= false;
	m_bWalk				= false;
	m_bBossClear		= false;
	m_skillNum			= 0;
	m_scriptNum			= 0;
}

CScene_Story01::CScene_Story01(const CScene_Story01& scene)
{
}

CScene_Story01::~CScene_Story01()
{
}

void CScene_Story01::Initialize()
{
	m_stage1Walk = new CBitmap();
	m_stage1Walk->Initialize(L"res/background/field_stage1_back.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	m_walkShader = new CTextureShader();
	m_walkShader->Initialize(NULL, L"shader/WalkShader.ps");

	m_stage1Bg = new CObject_Background();
	m_stage1Bg->Initalize(0, 0, 95, L"res/background/field_stage1_back.png");
	CObjectManager::getObjectManager()->AddObject(static_cast<CObject*>(m_stage1Bg));

	m_chain = new CObject_Chain();
	m_chain->Initialize();

	CMonster* tempMonster = CMonsterManager::getMonsterManager()->getMonsterWithNum(0);
	CBattleManager::getBattleManager()->SetMonster(tempMonster);

	m_monsterGauge = new CObject_Monstergauge();
	m_monsterGauge->Initalize(tempMonster);

	m_partySlot = new CObject_PartySlot();
	m_partySlot->Initalize();

	m_skillButton = new CObject_Skillselect();
	m_skillButton->Initalize();

	m_memberChange = new CObject_MemberChange();
	m_memberChange->Initalize(SCENE::FIELD);
	m_memberChange->SetActivate(false);

	m_targetMark = new CObject_Target();
	m_targetMark->Initalize(0, 0, 10);
	/*
	m_exploreBar = new CObject_ExploreBar();
	m_exploreBar->Initalize();

	m_exploreBtn = new CObject_ExploreButton();
	m_exploreBtn->Initialize();
	*/
	m_talkWindow = new CObject_TalkWindow();
	m_talkWindow->Initalize();
	m_talkWindow->Reset(0, CARD::NERO);

	m_sound_Move = new CSound();
	m_sound_Move->Initialize("res/sound/se/move.wav");
	m_sound_Move->Loop(false);

	m_bgm_stage1 = new CSound();
	m_bgm_stage1->Initialize("res/sound/bgm/1Stage_Forest.mp3");
	m_bgm_stage1->Loop(true);

	m_Text = new CFont();
	m_Text->Initialize(L"10X10");

	m_fadeTimer = new CTime();
	m_fadeTimer->SetTimer(0.75f, false);

	m_resultTimer = new CTime();
	m_battleTimer = new CTime();
	m_rotateDelay = new CTime();
	m_walkTimer	= new CTime();

	m_monsterDamage = 0;
	m_cardDamage = 0;
	m_scriptNum = 0;

	CNero::getNero()->SetStoryProgress(STORY::STORY01);
}

void CScene_Story01::Shutdown()
{	
	if(m_stage1Walk != NULL)
	{
		m_stage1Walk->Shutdown();
		SAFE_DELETE(m_stage1Walk);
	}
	if(m_stage1BossWalk != NULL)
	{
		m_stage1BossWalk->Shutdown();
		SAFE_DELETE(m_stage1BossWalk);
	}
	if(m_chain != NULL)
	{
		m_chain->Shutdown();
		SAFE_DELETE(m_chain);
	}
	if(m_walkShader != NULL)
	{
		m_walkShader->Shutdown();
		SAFE_DELETE(m_walkShader);
	}
	if(m_monsterGauge != NULL)
	{
		m_monsterGauge->Shutdown();
		SAFE_DELETE(m_monsterGauge);
	}
	if(m_skillButton != NULL)
	{
		m_skillButton->Shutdown();
		SAFE_DELETE(m_skillButton);
	}
	if(m_memberChange != NULL)
	{
		m_memberChange->Shutdown();
		SAFE_DELETE(m_memberChange);
	}
	if(m_targetMark != NULL)
	{
		m_targetMark->Shutdown();
		SAFE_DELETE(m_targetMark);
	}
	if(m_talkWindow != NULL)
	{
		m_talkWindow->Shutdown();
		SAFE_DELETE(m_talkWindow);
	}
	/*
	if(m_exploreBar != NULL)
	{
		m_exploreBar->Shutdown();
		SAFE_DELETE(m_exploreBar);
	}
	if(m_exploreBtn != NULL)
	{
		m_exploreBtn->Shutdown();
		SAFE_DELETE(m_exploreBtn);
	}
	*/
	if(m_Text != NULL)
	{
		m_Text->Shutdown();
		SAFE_DELETE(m_Text);
	}
	if(m_fadeTimer != NULL)
	{
		m_fadeTimer->StopTimer();
		SAFE_DELETE(m_fadeTimer);
	}
	if(m_resultTimer != NULL)
	{
		m_resultTimer->StopTimer();
		SAFE_DELETE(m_resultTimer);
	}
	if(m_battleTimer != NULL)
	{
		m_battleTimer->StopTimer();
		SAFE_DELETE(m_battleTimer);
	}
	if(m_rotateDelay != NULL)
	{
		m_rotateDelay->StopTimer();
		SAFE_DELETE(m_rotateDelay);
	}
	if(m_walkTimer != NULL)
	{
		m_walkTimer->StopTimer();
		SAFE_DELETE(m_walkTimer);
	}
	if(m_sound_Move != NULL)
	{
		m_sound_Move->Release();
		SAFE_DELETE(m_sound_Move);
	}
	if(m_bgm_stage1 != NULL)
	{
		m_bgm_stage1->Release();
		SAFE_DELETE(m_bgm_stage1);
	}
	if(m_bgm_stage1_boss != NULL)
	{
		m_bgm_stage1_boss->Release();
		SAFE_DELETE(m_bgm_stage1_boss);
	}
	m_bFadeIn = true;

	CNero::getNero()->OffStoryProgress(STORY::STORY01);
	CNero::getNero()->SetStoryProgress(STORY::STORY02);
	CScriptManager::getSkillManager()->ClearMap();
	CObjectManager::getObjectManager()->RemoveAllObjects();
}

void CScene_Story01::Update(CInput* input)
{
	m_input = input;
	CObjectManager::getObjectManager()->UpdateAllObjects(input);
	
	bool bDefeat = false;

	//m_exploreBar->Update(input);

	if(m_bExplore)
	{
		// 선택창 뜰 필요가 없음
		// 스크립트 끝나면 바로 전투

		//m_exploreBar->Show(true);
		
		//m_memberChange->SetActivate(false);
		//m_memberChange->Update(input);

		//m_exploreBtn->Update(input);

		//int select = m_exploreBtn->getSelect();

		if(input->IsLButtonUp()) {
			m_scriptNum++;

			if(m_scriptNum < 5 && m_scriptNum != -1)
			{
				switch(m_scriptNum)
				{
				case 0:	/*0번은 초기화에서 설정*/							break;
				case 1:	m_talkWindow->Reset(m_scriptNum, CARD::JOHN);		break;
				case 2:	m_talkWindow->Reset(m_scriptNum, CARD::NERO);		break;
				case 3: m_talkWindow->Reset(m_scriptNum, CARD::JOHN);		break;
				case 4: m_talkWindow->Reset(m_scriptNum, CARD::AYRIN);		break;
				default:													break;
				}
	
			}
		}

		if(m_scriptNum >= 5 && m_scriptNum != -1)
		{
			m_bBattle	= true;
			m_bTresure	= false;
			m_bTrap		= false;
			m_bWalk		= true;
			m_battleTimer->SetTimer(1.15f, false);
			m_walkTimer->SetTimer(1.0f, false);

			m_scriptNum = -1;
		}
		else
		{
			if(!m_bWalk) {
				
			}
		}
	}

	// 배틀! 배틀!! 배틀!!!
	if(m_bBattle && m_battleTimer->GetTimer())
	{
		// 전투 준비!!
		if(!CNero::getNero()->IsBattle())
		{
			CNero::getNero()->SetBattle(true);

			while(true)
			{
				if(CBattleManager::getBattleManager()->GetTurnCard() != NULL) {
					CBattleManager::getBattleManager()->TurnCardDequeue();
				}
				else {
					break;
				}
			}

			for(int i=0; i<4; i++)
			{
				CCard* tempCard = CNero::getNero()->GetPartyCardWithSlot(i);
				if(tempCard != NULL) {
					tempCard->setTurnTimer();
				}
			}

			// 몹 선택 (여기선 쇼아만)
			
			CBattleManager::getBattleManager()->SetMonster(CMonsterManager::getMonsterManager()->getMonsterWithNum(100));

			CBattleManager::getBattleManager()->GetMonster()->setTurnTimer(5.0f);
			CBattleManager::getBattleManager()->GetMonster()->UseSkill(m_skillNum);
			m_monsterGauge->setMonster(CBattleManager::getBattleManager()->GetMonster());
				
			m_targetMark->setMark();
			m_memberChange->SetActivate(false);
			m_chain->Reset();

		} // 전투 준비 끝!

		//m_exploreBar->Show(false);

		m_skillButton->Update(input);

		m_memberChange->SetActivate(false);
		m_memberChange->Update(input);

		m_targetMark->Update(input);
		m_chain->Update(input);
	
		CMonster* tempMonster = CBattleManager::getBattleManager()->GetMonster();

		

		tempMonster->UseSkill(m_skillNum);

		if(tempMonster->getMyTurn())
		{
			m_skillNum = rand()%2;
		}

		m_targetMark->setMark();

		if(tempMonster->getStat().m_ap >= 100) {
			tempMonster->setAp(0);
			tempMonster->setTurnTimer(15.0f);
		}

		for(int i=0; i<4; i++)
		{
			CCard* tempCard = CNero::getNero()->GetPartyCardWithSlot(i);
			if(tempCard != NULL)
			{
				if(tempCard != CBattleManager::getBattleManager()->GetTurnCard())
				{
					if(tempCard->getRemainToTurn() == 1.0f) {
						CBattleManager::getBattleManager()->TurnCardEnqueue(tempCard);
					}
				}
			}
		}
		if(input->IsWheelDown())
		{
			if(CNero::getNero()->GetRotate() > 0)
			{
				CNero::getNero()->SetRotate(CNero::getNero()->GetRotate()-1);
				CBattleManager::getBattleManager()->RotateSlot();
				m_chain->Move();
			}
		}

		CBattleManager::getBattleManager()->EffectUpdate();
		CBattleManager::getBattleManager()->EffectAutoRemove();
		
		if(CNero::getNero()->GetCardNero()->getStat().m_hp <= 0 && m_resultTimer->GetTimer())
		{
			m_resultTimer->SetTimer(2.0f, false);
			
			CNero::getNero()->SetBattle(false);

			m_bExplore = true;
			m_bBattle = false;

			if(m_fadeTimer->GetTimer())
			{
				m_fadeTimer->SetTimer(5.0f, false);
				m_bFadeIn = false;
			}
		}
	}

	CNero::getNero()->deathProcess();

	

	if(m_fadeTimer->GetTimer() && !m_bFadeIn)
	{
		CNero::getNero()->AllRestore();
		CNero::getNero()->GetPartyCardWithSlot(0)->setHp(CNero::getNero()->GetPartyCardWithSlot(0)->getStat().m_hp);
		CNero::getNero()->SetExploreNero(0.0f);
		m_memberChange->SetActivate(false);

		CBattleManager::getBattleManager()->EffectClear();

		CSceneManager::getSceneManager()->SetScene(SCENE::STORY2);
	}
	if(m_walkTimer->GetTimer()) {
		m_bWalk = false;
	}

	if(input->IsKeyDown(VK_ESCAPE))
	{
		if(m_fadeTimer->GetTimer())
		{
			m_fadeTimer->SetTimer(1.0f, false);
			m_bFadeIn = false;
		}
	}

	m_bgm_stage1->Play();
}

void CScene_Story01::Render()
{
	float opacity = 0.0f;
	if(m_bFadeIn) {
		opacity = 1.0f - (m_fadeTimer->RemainTime()/m_fadeTimer->GetSetTime());
		m_bgm_stage1->Volume(opacity);
	}
	else {
		opacity = (m_fadeTimer->RemainTime()/m_fadeTimer->GetSetTime());
		m_bgm_stage1->Volume(opacity);
	}


	if(m_bExplore)
	{
		if(opacity == 1.0f)
		{
			m_stage1Bg->setOpacity(1.0f);

			CObjectManager::getObjectManager()->RenderAllObjects();
			if(m_bWalk)
			{

				m_stage1Walk->Render(0, 0, 0);
				m_walkShader->Render(m_stage1Walk->GetTexture(), m_walkTimer->RemainTime());

			}

			CBattleManager::getBattleManager()->EffectRender();

			m_talkWindow->Update(m_input);
			m_talkWindow->Render();
		}
		else 
		{
			CObjectManager::getObjectManager()->RenderAllObjects(opacity);

			m_memberChange->acceptSceneOpacity(opacity);
		}
	}

	if(m_bBattle && m_battleTimer->GetTimer())
	{
		if(opacity == 1.0f)
		{
			m_stage1Bg->setOpacity(1.0f);

			CObjectManager::getObjectManager()->RenderAllObjects();

			CBattleManager::getBattleManager()->GetMonster()->MonsterRender(400, 50, 1.0f, 1.0f, opacity);
			
			m_monsterGauge->Render();
			m_targetMark->Render();

			if(m_bWalk)
			{
				m_stage1Walk->Render(0, 0, 0);
				m_walkShader->Render(m_stage1Walk->GetTexture(), m_walkTimer->RemainTime());
			}
			else {
				m_chain->Render();
			}
			
			
			m_partySlot->Render();
			m_memberChange->Render();
			
			CBattleManager::getBattleManager()->EffectRender();
			m_skillButton->Render();
		}
		else
		{
			CObjectManager::getObjectManager()->RenderAllObjects(opacity);

			m_chain->setOpacity(opacity);
			m_chain->Render();

			CBattleManager::getBattleManager()->GetMonster()->MonsterRender(400, 50, 1.0f, 1.0f, opacity);

			m_monsterGauge->setOpacity(opacity);
			m_monsterGauge->Render();
			
			m_targetMark->setOpacity(opacity);
			m_targetMark->Render();
			
			m_skillButton->setOpacity(opacity);
			m_skillButton->Render();
		
			m_partySlot->setOpacity(opacity);
			m_partySlot->Render();

			m_memberChange->setOpacity(opacity);
			m_memberChange->Render();
			m_memberChange->acceptSceneOpacity(opacity);
		}
	}
}