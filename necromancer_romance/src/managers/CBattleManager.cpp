#include "CBattleManager.h"
#include "CCardManager.h"
#include "CNero.h"

#include "..\objects\CCard.h"
#include "..\objects\CMonster.h"
#include "..\objects\CEffect.h"
#include "..\objects\CPassive.h"

CBattleManager* CBattleManager::s_battleManager = NULL;

CBattleManager::CBattleManager()
{
	m_turnQueue		= nullptr;
	m_bBattle		= false;
	m_monster		= nullptr;
	m_effectList	= nullptr;

}

CBattleManager::CBattleManager(const CBattleManager& temp)
{
}

CBattleManager::~CBattleManager()
{
}

void CBattleManager::Initialize()
{
	m_turnQueue = new std::deque<unsigned int>;
	m_effectList = new std::list<CEffect*>;

	for(int i=0; i<4; i++) {
		m_cardSlot[i].setPoint(384 + (128*i), 530);
	}
}

void CBattleManager::Shutdown()
{
	m_turnQueue->clear();
	m_effectList->clear();
	SAFE_DELETE(m_turnQueue);
	SAFE_DELETE(m_effectList);
	SAFE_DELETE(s_battleManager);
}

bool CBattleManager::GetBattleState()
{
	return m_bBattle;
}

void CBattleManager::SetBattleState(bool battle)
{
	m_bBattle = battle;
}

CCard* CBattleManager::GetTurnCard()
{
	if(GetQueueSize() != 0) {
		return CCardManager::getCardManager()->getCardWithNum(m_turnQueue->front());
	}
	else {
		return NULL;
	}
}

int CBattleManager::GetTurnCardNum()
{
	if(GetQueueSize() != 0) {
		return m_turnQueue->front();
	}
	else {
		return NULL;
	}
}

void CBattleManager::TurnCardEnqueue(CCard* card)
{
	if(card != NULL)
	{
		if(GetQueueSize() == 0) {
			m_turnQueue->push_back(card->getIdNum());
			return;
		}
		std::deque<unsigned int>::iterator it = m_turnQueue->begin();
		for(; it != m_turnQueue->end(); it++)
		{
			if(card->getIdNum() == (*it)) {
				return;
			}
		}
		m_turnQueue->push_back(card->getIdNum());
	}
}

void CBattleManager::TurnCardDequeue()
{
	m_turnQueue->pop_front();
}

bool CBattleManager::IsQueueCard(CCard* card)
{
	if(card == NULL) {
		return false;
	}
	if(GetQueueSize() != 0)
	{
		std::deque<unsigned int>::iterator it = m_turnQueue->begin();

		for(; it<m_turnQueue->end(); it++)
		{
			if(card->getIdNum() == (*it))
			{
				return true;
			}
		}
	}
	return false;
}

int CBattleManager::GetQueueSize()
{
	return m_turnQueue->size();
}

CMonster* CBattleManager::GetMonster()
{
	if(m_monster != NULL) {
		return m_monster;
	}
	else {
		return NULL;
	}
}

void CBattleManager::SetMonster(CMonster* monster)
{
	if(monster != NULL) {
		m_monster = monster;
	}
}

void CBattleManager::RotateSlot()
{
	CCard* tempCard = NULL;
	tempCard = CNero::getNero()->GetPartyCardWithSlot(3);
	CNero::getNero()->SetPartyCard(3, CNero::getNero()->GetPartyCardWithSlot(2));
	CNero::getNero()->SetPartyCard(2, CNero::getNero()->GetPartyCardWithSlot(1));
	CNero::getNero()->SetPartyCard(1, CNero::getNero()->GetPartyCardWithSlot(0));
	CNero::getNero()->SetPartyCard(0, tempCard);
}

void CBattleManager::RotateSlotRiv()
{
	CCard* tempCard = NULL;
	tempCard = CNero::getNero()->GetPartyCardWithSlot(0);
	CNero::getNero()->SetPartyCard(0, CNero::getNero()->GetPartyCardWithSlot(1));
	CNero::getNero()->SetPartyCard(1, CNero::getNero()->GetPartyCardWithSlot(2));
	CNero::getNero()->SetPartyCard(2, CNero::getNero()->GetPartyCardWithSlot(3));
	CNero::getNero()->SetPartyCard(3, tempCard);
}

void CBattleManager::PartyRender(float opacity)
{

}

void CBattleManager::EffectPush(CEffect* effect)
{
	m_effectList->push_back(effect);
}

void CBattleManager::EffectUpdate()
{
	std::list<CEffect*>::iterator it;
	for(it = m_effectList->begin() ; it != m_effectList->end(); it++)
	{
		(*it)->Update();
	}
}

void CBattleManager::EffectRender()
{
	std::list<CEffect*>::iterator it;
	for(it = m_effectList->begin() ; it != m_effectList->end(); it++)
	{
		if((*it)->GetAlive())
			(*it)->Render();
		}
}

void CBattleManager::EffectClear()
{
	m_effectList->clear();
}

void CBattleManager::EffectAutoRemove()
{

	CEffect* temp = nullptr;
	std::list<CEffect*>::iterator it = m_effectList->begin();
	for( ; it != m_effectList->end(); it++)
	{
		if(!(*it)->GetAlive())
		{
			temp = (*it);
			break;
		}
	}

	if(temp != nullptr) {
		m_effectList->remove(temp);
	}
}

void CBattleManager::PassivePush(CPassive* passive)
{

}

void CBattleManager::PassiveUpdate()
{

}

void CBattleManager::PassiveRender()
{

}

void CBattleManager::PassiveRemove(CPassive* passive)
{

}

void CBattleManager::PassiveClear()
{

}