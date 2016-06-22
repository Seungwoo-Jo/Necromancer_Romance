#ifndef _CSKILL_MANAGER_H_
#define _CSKILL_MANAGER_H_

#include <map>

class CSkill;

class CSkillManager
{
private:
	static CSkillManager* s_skillManager;

	std::map<unsigned int, CSkill*>* m_skillMap;
	std::map<unsigned int, CSkill*>::iterator m_it;

	CSkillManager();
	CSkillManager(const CSkillManager&);
	

public:
	~CSkillManager();

	static CSkillManager* getSkillManager()
	{
		if(!s_skillManager) {
			s_skillManager = new CSkillManager();
			s_skillManager->Initialize();
		}
		return s_skillManager;
	}

	void Initialize();
	void Shutdown();

	void AddSkill(CSkill*);
	CSkill* getSkillWithNum(unsigned int);

	void ClearMap();
};

#endif