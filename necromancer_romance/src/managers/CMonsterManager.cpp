#include "..\framework\common.h"
#include "CMonsterManager.h"

#include "..\objects\CMonster.h"

CMonsterManager* CMonsterManager::s_monsterManager = NULL;

CMonsterManager::CMonsterManager()
{
	m_monsterMap = NULL;
}

CMonsterManager::CMonsterManager(const CMonsterManager& temp)
{
}

CMonsterManager::~CMonsterManager()
{
}

void CMonsterManager::Initialize()
{
	m_monsterMap = new std::map<unsigned int, CMonster*>;
}

void CMonsterManager::Shutdown()
{
	ClearMap();

	SAFE_DELETE(m_monsterMap);
	SAFE_DELETE(s_monsterManager);
}

void CMonsterManager::AddMonster(CMonster* card)
{
	std::pair<std::map<unsigned int, CMonster*>::iterator, bool> result;
	result = m_monsterMap->insert(std::map<unsigned int, CMonster*>::value_type(card->getIdNum(), card));

	if(!result.second) {
		return;
	}
}

CMonster* CMonsterManager::getMonsterWithNum(unsigned int num)
{
	m_it = m_monsterMap->find(num);

	if(m_it != m_monsterMap->end()) {
		return m_it->second;
	}
	else {
		return NULL;
	}
}

void CMonsterManager::ClearMap()
{
	for(m_it = m_monsterMap->begin(); m_it != m_monsterMap->end(); m_it++)
	{
		CMonster* temp = m_it->second;
		temp->Shutdown();
		SAFE_DELETE(temp);
	}
	m_monsterMap->clear();
}