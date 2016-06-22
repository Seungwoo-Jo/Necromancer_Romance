#include "CObjectManager.h"
#include "..\framework\CInput.h"
#include "..\objects\CObject.h"

CObjectManager* CObjectManager::s_objectManager = NULL;

CObjectManager::CObjectManager()
{

}

CObjectManager::CObjectManager(const CObjectManager& objectmanager)
{

}

CObjectManager::~CObjectManager()
{

}

void CObjectManager::Initialize()
{
	m_objectList = new std::list<CObject*>;
}

void CObjectManager::Shutdown()
{
	RemoveAllObjects();
	SAFE_DELETE(m_objectList);
	SAFE_DELETE(s_objectManager);
}

void CObjectManager::AddObject(CObject* object)
{
	m_objectList->push_front(object);
	SortByZOrder();
}

void CObjectManager::RemoveObject(CObject* object)
{
	CObject* temp = object;
	object->Shutdown();
	m_objectList->remove(object);

	SAFE_DELETE(temp);
}

void CObjectManager::UpdateAllObjects(CInput* input)
{
	for(m_it = m_objectList->begin(); m_it != m_objectList->end(); m_it++)
	{
		(*m_it)->Update(input);
	}
}

void CObjectManager::RenderAllObjects()
{
	for(m_it = m_objectList->begin(); m_it != m_objectList->end(); m_it++)
	{
		(*m_it)->Render();
	}
}

void CObjectManager::RenderAllObjects(float opacity)
{
	for(m_it = m_objectList->begin(); m_it != m_objectList->end(); m_it++)
	{
		(*m_it)->setOpacity(opacity);
		(*m_it)->Render();
	}
}

void CObjectManager::RemoveAllObjects()
{
	for(m_it = m_objectList->begin(); m_it != m_objectList->end(); m_it++)
	{
		CObject* temp = (*m_it);
		(*m_it)->Shutdown();
		SAFE_DELETE(temp);
	}
	m_objectList->clear();
}

bool Sort(CObject* front, CObject* back)
{
	if(front->getPosition().posZ <= back->getPosition().posZ) {
		return false;
	}
	else {
		return true;
	}
}

void CObjectManager::SortByZOrder()
{
	m_objectList->sort(Sort);
}