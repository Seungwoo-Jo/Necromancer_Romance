#ifndef _CCARD_H_
#define _CCARD_H_

#include "..\framework\common.h"

class CBitmap;
class CTextureShader;
class CSkill;
class CInput;
class CTime;
class CEffect;
class CEffect_SpeechBubble;

#define CARD_WIDTH	155
#define CARD_HEIGHT	173
#define CARD_ASPECT_RATIO	CARD_WIDTH/CARD_HEIGHT

enum CARDTYPE
{
	SWORD = 0,
	SPEAR,
	BLUNT,
	BOW,
	MAGIC
};

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

class CCard
{
private:
	// 고유번호 / 출신
	unsigned int m_idNum;
	unsigned int m_tempNum;
	int m_type;
	
	wchar_t m_cardName[6];

	// 스텟 (최대체력, 체력, 최대AP, AP, 공격력, 방어력, 속도)
	Stat m_cardStat;
	wchar_t m_spdText[4];

	// 위치
	Qusy::Position m_pos;
	int m_outputWidth, m_outputHeight;

	// 타이머
	CTime* m_turnTimer;
	float m_remainToTurn;

	bool m_bHit;
protected:
	int m_useAp[3];
	wchar_t m_skill1Name[10];
	wchar_t m_skill2Name[10];
	wchar_t m_skill3Name[10];

	//wchar_t m_cardExplaination[255];
	//wchar_t m_fromExplaination[255];

	// 카드 이미지
	CBitmap* m_cardImage;
	CTextureShader* m_cardShader;
	CTextureShader* m_blackShader;
	CTextureShader* m_sepiaShader;
	CTextureShader* m_hitShader;
	CTextureShader* m_turnShader;

	CEffect* m_skillEffect[3];
	CEffect_SpeechBubble* m_speechBubble;

public:
	CCard();
	CCard(const CCard& card);
	~CCard();

	virtual void Initialize();
	virtual void Shutdown();
	virtual void PowerUp();


	unsigned int getIdNum();
	void setIdNum(unsigned int);

	unsigned int getTeamNum();
	void setTeamNum(unsigned int);

	void setCardName(wchar_t*);
	wchar_t* getCardName();

	Stat getStat();
	void setStat(int maxHp, int hp, int maxAp, int ap, int atk, int def, int spd);
	void setHp(int hp);
	void setAp(int ap);
	
	int getUseAp(int num);

	void Restore();

	void setType(int);
	int getType();
	
	wchar_t* getSpdText();
	void setSpdText(wchar_t*);

	wchar_t* getSkillName(int);

	CBitmap* getCardImage();
	void setCardImage(CBitmap*);

	CTextureShader* getCardShader();
	void setCardShader(CTextureShader*);

	void GetCardRect(Qusy::Rect&);

	void CardRender(int x, int y, int z, float widthRatio, float heightRatio, int shaderType, float opacity);
	void CardRender(int x, int y, int z, int outputWidth, int outputHeight, int shaderType, float opacity);

	void getCardPosition(int&, int&);
	bool IsCardLButtonClick(CInput*);

	void setTurnTimer();
	void stopTimer();
	bool getMyTurn();
	float getRemainToTurn();

	void setHit(bool);
	bool getHit();

	virtual int UseSkill(int num);
};


#endif