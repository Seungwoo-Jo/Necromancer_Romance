#ifndef _CMONSTER_H_
#define _CMONSTER_H_

#ifndef _STAT_
#define _STAT_
struct Stat
{
	int m_maxHp;
	int m_hp;
	int m_maxAp;
	int m_ap;

	int m_atk;
	int m_def;
	int m_spd;
};
#endif

enum ARMOR
{
	SKIN = 0,
	LIGHT,
	HEAVY,
	PLATE,
	SPIRIT
};

class CBitmap;
class CTextureShader;
class CTime;
class CEffect;

class CMonster
{
private:
	// 고유 식별 번호
	unsigned int m_idNum;

	// 몬스터 스텟 (AP 안씀)
	Stat m_monsterStat;

	// 몬스터 이미지
	CBitmap* m_monsterImage;
	CTextureShader* m_monsterShader;
	CTextureShader* m_hitShader;

	

	// 타이머
	CTime* m_atkTimer;
	float m_remainToTimer;

	// 타겟
	int m_target;
	
	bool m_bHit;
	int m_armorType;

protected:
	CEffect* m_skillEffect[3];
	bool m_bTargeting;

public:
	CMonster();
	CMonster(const CMonster&);
	~CMonster();
	
	virtual void Initialize();
	void Shutdown();

	unsigned int getIdNum();
	void setIdNum(unsigned int);

	Stat getStat();
	void setStat(int maxHp, int hp, int atk, int def, int spd);
	void setHp(int hp);
	void setAp(int ap);

	void Restore();

	void setArmorType(int type);
	int getArmorType();

	CBitmap* getMonsterImage();
	void setMonsterImage(CBitmap*);

	CTextureShader* getMonsterShader();
	void setMonsterShader(CTextureShader*);
	void setMonsterRedShader(CTextureShader*);

	void MonsterRender(int x, int y, float widthRatio, float heightRatio, float opacity);

	void setTurnTimer(float);
	bool getMyTurn();
	float getRemainToTurn();
	float getRemainToTurnRatio();

	bool getHit();
	void setHit(bool);

	void setTarget(int);
	int getTarget();

	virtual void Update();
	virtual int UseSkill(int);
};

#endif