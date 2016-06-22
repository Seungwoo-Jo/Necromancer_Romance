#ifndef _COBJECT_MANAGER_H_
#define _COBJECT_MANAGER_H_

// INCLUDES //
#include <list>

class CObject;
class CInput;

// Class name: CObjectManager //
class CObjectManager
{
private:
	static CObjectManager* s_objectManager;

	std::list<CObject*>* m_objectList;
	std::list<CObject*>::iterator m_it;

	CObjectManager();
	CObjectManager(const CObjectManager&);

public:
	~CObjectManager();

	static CObjectManager* getObjectManager()
	{
		if(s_objectManager == NULL) {
			s_objectManager = new CObjectManager();
			s_objectManager->Initialize();
		}
		return s_objectManager;
	}

	void Initialize();
	void Shutdown();
	void AddObject(CObject*);
	void RemoveObject(CObject*);
	void UpdateAllObjects(CInput*);
	void RenderAllObjects();
	void RenderAllObjects(float);
	void RemoveAllObjects();

	void SortByZOrder();
};

#endif