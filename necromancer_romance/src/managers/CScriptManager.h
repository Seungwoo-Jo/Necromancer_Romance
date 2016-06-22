#ifndef _CSKILL_MANAGER_H_
#define _CSKILL_MANAGER_H_

#include <map>

class CSkill;
class CObject_TalkWindow;

class CScriptManager
{
private:
	static CScriptManager* s_scriptManager;

	std::map<int, wchar_t*>* m_scriptMap;
	std::map<int, wchar_t*>::iterator m_it;

	CScriptManager();
	CScriptManager(const CScriptManager&);
	

public:
	~CScriptManager();

	static CScriptManager* getSkillManager()
	{
		if(!s_scriptManager) {
			s_scriptManager = new CScriptManager();
			s_scriptManager->Initialize();
		}
		return s_scriptManager;
	}

	void Initialize();
	void Shutdown();

	void AddScript(int, wchar_t*);
	wchar_t* getScriptWithNum(int);

	void ClearMap();
};

#endif