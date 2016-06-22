#include "..\framework\common.h"
#include "CSkillManager.h"

#include "..\objects\CSkill.h"

CSkillManager* CSkillManager::s_skillManager = NULL;

CSkillManager::CSkillManager()
{
	m_skillMap = NULL;
}

CSkillManager::CSkillManager(const CSkillManager& temp)
{
}

CSkillManager::~CSkillManager()
{
}

void CSkillManager::Initialize()
{
	m_skillMap = new std::map<unsigned int, CSkill*>;
}

void CSkillManager::Shutdown()
{
	ClearMap();

	SAFE_DELETE(m_skillMap);
	SAFE_DELETE(s_skillManager);
}

void CSkillManager::AddSkill(CSkill* skill)
{
	std::pair<std::map<unsigned int, CSkill*>::iterator, bool> result;
	result = m_skillMap->insert(std::map<unsigned int, CSkill*>::value_type(skill->getIdNum(), skill));

	if(!result.second) {
		return;
	}
}

CSkill* CSkillManager::getSkillWithNum(unsigned int num)
{
	m_it = m_skillMap->find(num);

	if(m_it != m_skillMap->end()) {
		return m_it->second;
	}
	else {
		return NULL;
	}
}

void CSkillManager::ClearMap()
{
	for(m_it = m_skillMap->begin(); m_it != m_skillMap->end(); m_it++)
	{
		CSkill* temp = m_it->second;
		SAFE_DELETE(temp);
	}
	m_skillMap->clear();
}