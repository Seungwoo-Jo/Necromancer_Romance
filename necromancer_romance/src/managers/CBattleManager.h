#ifndef _CBATTLE_MANAGER_H_
#define _CBATTLE_MANAGER_H_

#include <deque>
#include <list>
#include "..\framework\common.h"

class CCard;
class CMonster;
class CEffect;
class CPassive;

class CBattleManager
{
private:
	static CBattleManager* s_battleManager;
	std::deque<unsigned int>* m_turnQueue;
	std::list<CEffect*>* m_effectList;

	bool m_bBattle;

	CMonster* m_monster;

	CBattleManager();
	CBattleManager(const CBattleManager&);

	Qusy::Point m_cardSlot[4];

public:
	~CBattleManager();

	static CBattleManager* getBattleManager()
	{
		if(s_battleManager == NULL)
		{
			s_battleManager = new CBattleManager();
			s_battleManager->Initialize();
		}
		return s_battleManager;
	}

	void Initialize();
	void Shutdown();

	bool GetBattleState();
	void SetBattleState(bool);

	CCard* GetTurnCard();
	int GetTurnCardNum();

	void TurnCardEnqueue(CCard*);
	void TurnCardDequeue();

	bool IsQueueCard(CCard*);
	int GetQueueSize();

	void MonsterReset();

	CMonster* GetMonster();
	void SetMonster(CMonster*);

	void RotateSlot();
	void RotateSlotRiv();
	void PartyRender(float);

	void EffectPush(CEffect*);
	void EffectUpdate();
	void EffectRender();
	void EffectClear();
	void EffectAutoRemove();

	void PassivePush(CPassive*);
	void PassiveUpdate();
	void PassiveRender();
	void PassiveClear();
	void PassiveRemove(CPassive*);
};

#endif