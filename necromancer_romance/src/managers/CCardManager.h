#ifndef _CCARD_MANAGER_H_
#define _CCARD_MANAGER_H_

#include <map>

#define TOTAL_CARD	13

enum CARD
{
	NOCARD		= 0,
	DAY			= 1,
	HILDE		= 2,
	AYRIN		= 3,
	RENE		= 4,
	SOUND		= 5,
	IRON		= 6,
	MORRIGHU	= 7,
	SCATHACH	= 8,
	AOIFE		= 9,
	MELROSE		= 10,
	EADRIC		= 11,
	JOHN		= 12,
	NERO		= 13,
	ILL_SHOA	= 14,
};

class CCard;

class CCardManager
{
private:
	static CCardManager* s_cardManager;

	std::map<unsigned int, CCard*>* m_cardMap;
	std::map<unsigned int, CCard*>::iterator m_it;

	CCardManager();
	CCardManager(const CCardManager&);
	

public:
	~CCardManager();

	static CCardManager* getCardManager()
	{
		if(!s_cardManager) {
			s_cardManager = new CCardManager();
			s_cardManager->Initialize();
		}
		return s_cardManager;
	}

	void Initialize();
	void Shutdown();

	void AddCard(CCard*);
	CCard* getCardWithNum(unsigned int);

	void ClearMap();
};

#endif