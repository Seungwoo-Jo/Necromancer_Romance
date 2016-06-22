#include <thread>

// ..\framework
#include "..\framework\CBitmap.h"
#include "..\framework\CTextureShader.h"
#include "..\framework\CInput.h"
#include "..\framework\common.h"
#include "..\framework\CFont.h"
#include "..\framework\CTime.h"

// ..\managers
#include "..\managers\CObjectManager.h"
#include "..\managers\CSceneManager.h"
#include "..\managers\CCardManager.h"
#include "..\managers\CMonsterManager.h"
#include "..\managers\CScriptManager.h"
#include "..\managers\CNero.h"

// ..\objects
#include "..\objects\CObject_Common.h"
#include "..\objects\CCard.h"
#include "..\objects\CSkill.h"

#include "..\objects\CMonster_Wolfrider.h"
#include "..\objects\CMonster_Warewolf.h"
#include "..\objects\CMonster_Lupus.h"
#include "..\objects\CMonster_Armored.h"
#include "..\objects\CMonster_Maid.h"
#include "..\objects\CMonster_Succubus.h"
#include "..\objects\CMonster_Shoa.h"
#include "..\objects\CMonster_Shoa2.h"
#include "..\objects\CMonster_God.h"

#include "..\objects\CCard_Aoife.h"
#include "..\objects\CCard_Ayrin.h"
#include "..\objects\CCard_Day.h"
#include "..\objects\CCard_Eadric.h"
#include "..\objects\CCard_Hilde.h"
#include "..\objects\CCard_Iron.h"
#include "..\objects\CCard_John.h"
#include "..\objects\CCard_Melrose.h"
#include "..\objects\CCard_Morrighu.h"
#include "..\objects\CCard_Nero.h"
#include "..\objects\CCard_Rene.h"
#include "..\objects\CCard_Scathach.h"
#include "..\objects\CCard_Sound.h"

// ..\scenes
#include "CScene_Preload.h"

CScene_Preload::CScene_Preload()
{
	m_anime	= NULL;
	m_Text			= NULL;
	m_fadeTimer		= NULL;
	m_bPreload		= true;
	m_bFadeIn		= true;
}

CScene_Preload::CScene_Preload(const CScene_Preload& scene)
{
}

CScene_Preload::~CScene_Preload()
{
}

void CScene_Preload::Initialize()
{
	m_anime = new CObject_Common();
	m_anime->Initalize(935, 635, 50, 1.0f, 1.0f, L"res/field/explore_hero.png");
	m_anime->GetBitmap()->SetSpriteAnimation(4, 1, 800, true);
	CObjectManager::getObjectManager()->AddObject(static_cast<CObject*>(m_anime));

	m_Text = new CFont();
	m_Text->Initialize(L"10X10");

	m_fadeTimer = new CTime();
	m_fadeTimer->SetTimer(0.2f, false);

	m_fakeTimer = new CTime();
	m_fakeTimer->SetTimer(0.2f, false);
}

void CScene_Preload::Shutdown()
{
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
	if(m_fakeTimer != NULL)
	{
		m_fakeTimer->StopTimer();
		SAFE_DELETE(m_fakeTimer);
	}
	m_bFadeIn = false;

	CObjectManager::getObjectManager()->RemoveAllObjects();
}

void CScene_Preload::Update(CInput* input)
{
	CObjectManager::getObjectManager()->UpdateAllObjects(input);

	if(m_fadeTimer->GetTimer() && m_bPreload)
	{
		std::thread Threads1( [] ()
        {
			CCard* tempCard = NULL;

			tempCard = new CCard_Aoife();
			tempCard->Initialize();
			CCardManager::getCardManager()->AddCard(tempCard);

			tempCard = new CCard_Ayrin();
			tempCard->Initialize();
			CCardManager::getCardManager()->AddCard(tempCard);

			tempCard = new CCard_Day();
			tempCard->Initialize();
			CCardManager::getCardManager()->AddCard(tempCard);

			tempCard = new CCard_Eadric();
			tempCard->Initialize();
			CCardManager::getCardManager()->AddCard(tempCard);

			tempCard = new CCard_Hilde();
			tempCard->Initialize();
			CCardManager::getCardManager()->AddCard(tempCard);

			tempCard = new CCard_Iron();
			tempCard->Initialize();
			CCardManager::getCardManager()->AddCard(tempCard);

        } );

		std::thread Threads2( [] ()
        {
			CCard* tempCard = NULL;

			tempCard = new CCard_John();
			tempCard->Initialize();
			CCardManager::getCardManager()->AddCard(tempCard);

			tempCard = new CCard_Melrose();
			tempCard->Initialize();
			CCardManager::getCardManager()->AddCard(tempCard);

			tempCard = new CCard_Morrighu();
			tempCard->Initialize();
			CCardManager::getCardManager()->AddCard(tempCard);

			tempCard = new CCard_Nero();
			tempCard->Initialize();
			CCardManager::getCardManager()->AddCard(tempCard);

			tempCard = new CCard_Rene();
			tempCard->Initialize();
			CCardManager::getCardManager()->AddCard(tempCard);

			tempCard = new CCard_Scathach();
			tempCard->Initialize();
			CCardManager::getCardManager()->AddCard(tempCard);
        } );

		std::thread Threads3( [] ()
        {
			CCard* tempCard = NULL;

			tempCard = new CCard_Sound();
			tempCard->Initialize();
			CCardManager::getCardManager()->AddCard(tempCard);


			CMonster* tempMonster = NULL;

			tempMonster = new CMonster_Wolfrider();
			tempMonster->Initialize();	
			CMonsterManager::getMonsterManager()->AddMonster(tempMonster);

			tempMonster = new CMonster_Warewolf();
			tempMonster->Initialize();	
			CMonsterManager::getMonsterManager()->AddMonster(tempMonster);
		
			tempMonster = new CMonster_Lupus();
			tempMonster->Initialize();
			CMonsterManager::getMonsterManager()->AddMonster(tempMonster);

			tempMonster = new CMonster_Shoa();
			tempMonster->Initialize();
			CMonsterManager::getMonsterManager()->AddMonster(tempMonster);
        } );

		std::thread Threads4( [] ()
        {
			// 몬스터 로드
			CMonster* tempMonster = NULL;

			tempMonster = new CMonster_Armored();
			tempMonster->Initialize();
			CMonsterManager::getMonsterManager()->AddMonster(tempMonster);

			tempMonster = new CMonster_Maid();
			tempMonster->Initialize();
			CMonsterManager::getMonsterManager()->AddMonster(tempMonster);

			tempMonster = new CMonster_Succubus();
			tempMonster->Initialize();
			CMonsterManager::getMonsterManager()->AddMonster(tempMonster);

			tempMonster = new CMonster_Shoa2();
			tempMonster->Initialize();
			CMonsterManager::getMonsterManager()->AddMonster(tempMonster);

			tempMonster = new CMonster_God();
			tempMonster->Initialize();
			CMonsterManager::getMonsterManager()->AddMonster(tempMonster);
        } );
		
		Threads1.join();
		Threads2.join();
		Threads3.join();
		Threads4.join();

		CCard* tempCard = NULL;
		CCard* neroCard = CCardManager::getCardManager()->getCardWithNum(13);

		tempCard = CCardManager::getCardManager()->getCardWithNum(12);
		CNero::getNero()->AddHaveCard(tempCard);
		tempCard = CCardManager::getCardManager()->getCardWithNum(13);
		CNero::getNero()->AddHaveCard(tempCard);

		CNero::getNero()->SetCardNero(neroCard);
		CNero::getNero()->SetPartyCard(0, 13);
		CNero::getNero()->SetPartyCard(1, 12);

		CScriptManager::getSkillManager()->AddScript(0, L"존. 저 남자가 가장 강하다는 인간이지?");
		CScriptManager::getSkillManager()->AddScript(1, L"소문에 의하면 그렇지.\n사도를 때려잡는 용사라고 불린다니까.");
		CScriptManager::getSkillManager()->AddScript(2, L"레나타를 되살리기 위해 저 자식의 영혼이 필요해.\n살점 붙이고 따라와.");
		CScriptManager::getSkillManager()->AddScript(3, L"제일 센 좀비인 내가 제일 센 인간을 혼내준다.\n엄청나게 쿨하군");
		CScriptManager::getSkillManager()->AddScript(4, L" ");

		m_bPreload = false;
	}
	
	if(m_fakeTimer->GetTimer() && m_bFadeIn)
	{
		m_fadeTimer->SetTimer(0.25f, false);
		m_bFadeIn = false;
	}
	if(m_fadeTimer->GetTimer() && !m_bFadeIn) {
		CSceneManager::getSceneManager()->SetScene(SCENE::TITLE);
	}
	
}

void CScene_Preload::Render()
{
	float opacity = 0.0f;
	if(m_bFadeIn) {
		opacity = 1.0f - (m_fadeTimer->RemainTime()/m_fadeTimer->GetSetTime());
	}
	else {
		opacity = (m_fadeTimer->RemainTime()/m_fadeTimer->GetSetTime());
	}
	
	if(opacity == 1.0f) {
		//CObjectManager::getObjectManager()->RenderAllObjects(1.0f);
		m_Text->Draw(L"LOADING......", 30, 1100, 675, GetColor(255, 255, 255, 255), NULL);
	}
	else {
		//CObjectManager::getObjectManager()->RenderAllObjects(opacity);
		m_Text->Draw(L"LOADING......", 30, 1100, 675, GetColor(255, 255, 255, (UINT8)(opacity*255.0f)), NULL);
	}
	
}