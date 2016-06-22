#include "..\framework\common.h"
#include "CCardManager.h"

#include "..\objects\CCard.h"

CCardManager* CCardManager::s_cardManager = NULL;

CCardManager::CCardManager()
{
	m_cardMap = NULL;
}

CCardManager::CCardManager(const CCardManager& temp)
{
}

CCardManager::~CCardManager()
{
}

void CCardManager::Initialize()
{
	m_cardMap = new std::map<unsigned int, CCard*>;
}

void CCardManager::Shutdown()
{
	ClearMap();

	SAFE_DELETE(m_cardMap);
	SAFE_DELETE(s_cardManager);
}

void CCardManager::AddCard(CCard* card)
{
	std::pair<std::map<unsigned int, CCard*>::iterator, bool> result;
	result = m_cardMap->insert(std::map<unsigned int, CCard*>::value_type(card->getIdNum(), card));

	if(!result.second) {
		return;
	}
}

CCard* CCardManager::getCardWithNum(unsigned int num)
{
	m_it = m_cardMap->find(num);

	if(m_it != m_cardMap->end()) {
		return m_it->second;
	}
	else {
		return NULL;
	}
}

void CCardManager::ClearMap()
{
	for(m_it = m_cardMap->begin(); m_it != m_cardMap->end(); m_it++)
	{
		CCard* temp = m_it->second;
		temp->Shutdown();
		SAFE_DELETE(temp);
	}
	m_cardMap->clear();
}