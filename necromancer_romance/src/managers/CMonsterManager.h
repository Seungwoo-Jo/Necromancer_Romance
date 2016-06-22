#ifndef _CMONSTER_MANAGER_H_
#define _CMONSTER_MANAGER_H_

#include <map>

#define TOTAL_MONSTER	3

class CMonster;

class CMonsterManager
{
private:
	static CMonsterManager* s_monsterManager;

	std::map<unsigned int, CMonster*>* m_monsterMap;
	std::map<unsigned int, CMonster*>::iterator m_it;

	CMonsterManager();
	CMonsterManager(const CMonsterManager&);
	

public:
	~CMonsterManager();

	static CMonsterManager* getMonsterManager()
	{
		if(!s_monsterManager) {
			s_monsterManager = new CMonsterManager();
			s_monsterManager->Initialize();
		}
		return s_monsterManager;
	}

	void Initialize();
	void Shutdown();

	void AddMonster(CMonster*);
	CMonster* getMonsterWithNum(unsigned int);

	void ClearMap();
};

#endif