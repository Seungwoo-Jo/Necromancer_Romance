#ifndef _CNERO_H_
#define _CNERO_H_

#include <list>

#define BOSS1_PLACE		440.0f
#define BOSS2_PLACE		940.0f

enum PROGRESS
{
	START,
	STAGE1,
	STAGE2
};

enum BOSS
{
	NONE,
	LUPUS,
	SUCCUBUS,
	SHOA,
	GOD
};

enum STORY
{
	STORY00 = (1 <<  0),
	STORY01 = (1 <<  1),
	STORY02 = (1 <<  2),
	STORY03 = (1 <<  3),
	STORY04 = (1 <<  4),
	STORY05 = (1 <<  5),
	STORY06 = (1 <<  6),
	STORY07 = (1 <<  7),
	STORY08 = (1 <<  8),
	STORY09 = (1 <<  9),
	STORY10 = (1 << 10),
	STORY11 = (1 << 11),
	STORY12 = (1 << 12),
	STORY13 = (1 << 13),
	STORY14 = (1 << 14),
	STORY15 = (1 << 15),
	STORY16 = (1 << 16),
	STORY17 = (1 << 17),
};

class CCard;

class CNero
{
private:
	static CNero* s_nero;

	// 가지고 있는 카드들
	std::list<CCard*>* m_haveCardList;

	// 네로 본인
	CCard* m_neroCard;

	// 파티 구성원
	CCard* m_partyMember[4];

	// 회전
	int m_rotate;

	// 가지고 있는 골드
	int m_gold;

	

	// 가지고 있는 영혼 수
	int m_souls;

	float m_exploreNero;
	float m_exploreHero;

	int m_gameProgress;
	int m_bossProgress;
	int m_storyProgress;

	bool m_bBattle;

	CNero();
	CNero(const CNero&);

public:
	~CNero();

	int m_numExplore;
	int m_numGoldChest;
	int m_numBattle;
	int m_numOut;
	int m_numInn;
	int m_numBoss;
	bool m_bShoa;

	static CNero* getNero()
	{
		if(!s_nero) {
			s_nero = new CNero();
			s_nero->Initalize();
		}
		return s_nero;
	}
	void Initalize();
	void Shutdown();
	void AddHaveCard(CCard*);
	CCard* GetHaveCard(unsigned int idNum);
	CCard* GetHaveCardWithIndex(unsigned int index);
	int GetHaveCardNum();
	void RemoveHaveCard(CCard*);

	void deathProcess();
	void AllRestore();

	CCard* GetPartyCardWithSlot(int);
	void SetPartyCard(int, int);
	void SetPartyCard(int, CCard*);

	CCard* GetCardNero();
	void SetCardNero(CCard*);

	int GetRotate();
	void SetRotate(int);

	float GetExploreNero();
	void SetExploreNero(float);

	float GetExploreHero();
	void SetExploreHero(float);

	int GetGameProgress();
	void SetGameProgress(int);

	int GetBossProgress();
	void SetBossProgress(int);

	bool GetStoryProgress(unsigned int);
	void SetStoryProgress(unsigned int);
	void OffStoryProgress(unsigned int);

	int GetGold();
	void SetGold(int);

	int GetSoul();
	void SetSoul(int);

	bool IsBattle();
	void SetBattle(bool);
};

#endif