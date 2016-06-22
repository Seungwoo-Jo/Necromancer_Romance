// ..\framework
#include "..\framework\common.h"

// ..\managers
#include "CNero.h"

// ..\objects
#include "..\objects\CCard.h"

CNero* CNero::s_nero = NULL;

CNero::CNero()
{
	m_haveCardList = NULL;
}

CNero::CNero(const CNero& nero)
{

}

CNero::~CNero()
{

}

void CNero::Initalize()
{
	m_haveCardList		= new std::list<CCard*>;
	m_neroCard			= NULL;
	m_partyMember[0]	= NULL;
	m_partyMember[1]	= NULL;
	m_partyMember[2]	= NULL;
	m_partyMember[3]	= NULL;

	m_gold = 111012;
	m_souls = 111012;

	m_exploreNero = 50.0f;
	m_exploreHero = 725.0f;

	m_gameProgress = PROGRESS::STAGE1;
	m_bossProgress = BOSS::NONE;
	m_storyProgress = 0;

	m_rotate = 0.0f;
	m_bBattle = false;

	m_numExplore = 0;
	m_numGoldChest = 0;
	m_numBattle = 0;
	m_numOut = 0;
	m_numInn = 0;
	m_numBoss = 0;
	m_bShoa = true;
}

void CNero::Shutdown()
{
	m_haveCardList->clear();
	SAFE_DELETE(m_haveCardList);
	
	m_neroCard = NULL;
	m_partyMember[0] = NULL;
	m_partyMember[1] = NULL;
	m_partyMember[2] = NULL;
	m_partyMember[3] = NULL;
}

void CNero::AddHaveCard(CCard* card)
{
	m_haveCardList->push_back(card);
}

CCard* CNero::GetHaveCard(unsigned int idNum)
{
	std::list<CCard*>::iterator it = m_haveCardList->begin();

	for(; it != m_haveCardList->end(); it++)
	{
		if((*it)->getIdNum() == idNum) {
			return (*it);
		}
	}
	return NULL;
}

CCard* CNero::GetHaveCardWithIndex(unsigned int index)
{
	if(index <= m_haveCardList->size()-1)
	{
		std::list<CCard*>::iterator it = m_haveCardList->begin();

		for(int i=0; i<index; i++) {
			it++;
		}
		if((*it) == NULL) {
			return NULL;
		}
		return (*it);
	}
	return NULL;
}

int CNero::GetHaveCardNum()
{
	return m_haveCardList->size();
}

void CNero::RemoveHaveCard(CCard* card)
{
	m_haveCardList->remove(card);
}

void CNero::deathProcess()
{
	std::list<CCard*>::iterator it = m_haveCardList->begin();

	for(; it != m_haveCardList->end(); it++)
	{
		if((*it)->getStat().m_hp < 0)
		{
			if((*it)->getIdNum() != 13)
			{
				for(int i=0; i<4; i++)
				{
					if((*it) == m_partyMember[i])
					{
						SetSoul(GetSoul()+1);
						m_partyMember[i] = NULL;
						//RemoveHaveCard((*it));
					}
				}
			}
			
		}
	}
}

void CNero::AllRestore()
{
	std::list<CCard*>::iterator it = m_haveCardList->begin();

	for(; it != m_haveCardList->end(); it++)
	{
		(*it)->Restore();
	}
}

CCard* CNero::GetPartyCardWithSlot(int slotNum)
{
	if(slotNum < 0 || slotNum > 3) {
		return NULL;
	}
	return m_partyMember[slotNum];
}

void CNero::SetPartyCard(int slotNum, int idNum)
{
	if(slotNum < 0 || slotNum > 3) {
		return;
	}
	if(idNum == -1){
		m_partyMember[slotNum] = NULL;
		return;
	}

	CCard* tempCard = GetHaveCard(idNum);

	
	if(tempCard == NULL) {
		return;
	}
	

	m_partyMember[slotNum] = tempCard;
}

void CNero::SetPartyCard(int slotNum, CCard* card)
{
	if(slotNum < 0 || slotNum > 3) {
		return;
	}

	m_partyMember[slotNum] = card;
}

CCard* CNero::GetCardNero()
{
	return m_neroCard;
}

void CNero::SetCardNero(CCard* card)
{
	m_neroCard = card;
}

int CNero::GetRotate()
{
	return m_rotate;
}

void CNero::SetRotate(int rotate)
{
	m_rotate = rotate;
}

void CNero::SetExploreNero(float exploreNero)
{
	m_exploreNero = exploreNero;
}

float CNero::GetExploreNero()
{
	return m_exploreNero;
}

void CNero::SetExploreHero(float exploreHero)
{
	m_exploreHero = exploreHero;
}

float CNero::GetExploreHero()
{
	return m_exploreHero;
}

int CNero::GetGameProgress()
{
	return m_gameProgress;
}

void CNero::SetGameProgress(int progress)
{
	m_gameProgress = progress;
}

int CNero::GetBossProgress()
{
	return m_bossProgress;
}

void CNero::SetBossProgress(int progress)
{
	m_bossProgress = progress;
}

bool CNero::GetStoryProgress(unsigned int storyFlag)
{
	bool result = ((m_storyProgress & storyFlag) == storyFlag)? true : false;
	return result;
}
void CNero::SetStoryProgress(unsigned int storyFlag)
{
	m_storyProgress = m_storyProgress | storyFlag;
}
void CNero::OffStoryProgress(unsigned int storyFlag)
{
	m_storyProgress = m_storyProgress | storyFlag;
	m_storyProgress -= storyFlag;
}

int CNero::GetGold()
{
	return m_gold;
}

void CNero::SetGold(int gold)
{
	m_gold = gold;
}

int CNero::GetSoul()
{
	return m_souls;
}

void CNero::SetSoul(int soul)
{
	m_souls = soul;
}

bool CNero::IsBattle()
{
	return m_bBattle;
}

void CNero::SetBattle(bool battle)
{
	m_bBattle = battle;
}