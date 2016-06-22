#include "..\framework\common.h"
#include "CScriptManager.h"

#include "..\objects\CSkill.h"

CScriptManager* CScriptManager::s_scriptManager = NULL;

CScriptManager::CScriptManager()
{
	m_scriptMap = NULL;
}

CScriptManager::CScriptManager(const CScriptManager& temp)
{
}

CScriptManager::~CScriptManager()
{
}

void CScriptManager::Initialize()
{
	m_scriptMap = new std::map<int, wchar_t*>;
}

void CScriptManager::Shutdown()
{
	ClearMap();

	SAFE_DELETE(m_scriptMap);
	SAFE_DELETE(s_scriptManager);
}

void CScriptManager::AddScript(int num, wchar_t* script)
{
	wchar_t* text = new wchar_t[128];

	swprintf_s(text, 128, script);

	std::pair<std::map<int, wchar_t*>::iterator, bool> result;
	result = m_scriptMap->insert(std::map<int, wchar_t*>::value_type(num, text));

	if(!result.second) {
		return;
	}
}

wchar_t* CScriptManager::getScriptWithNum(int num)
{
	m_it = m_scriptMap->find(num);

	if(m_it != m_scriptMap->end()) {
		return m_it->second;
	}
	else {
		return NULL;
	}
}

void CScriptManager::ClearMap()
{
	for(m_it = m_scriptMap->begin(); m_it != m_scriptMap->end(); m_it++)
	{
		wchar_t* temp = m_it->second;
		SAFE_DELETE_ARRAY(temp);
	}
	m_scriptMap->clear();
}