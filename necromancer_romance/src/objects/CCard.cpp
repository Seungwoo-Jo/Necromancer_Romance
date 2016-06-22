#include "..\framework\CBitmap.h"
#include "..\framework\CTextureShader.h"
#include "..\framework\CInput.h"
#include "..\framework\CTime.h"

#include "..\managers\CBattleManager.h"

#include "CCard.h"
#include "CSkill.h"
#include "CEffect.h"
#include "CEffect_SpeechBubble.h"

CCard::CCard()
{
	m_turnTimer = new CTime();
	m_remainToTurn = 1.0f;
}

CCard::CCard(const CCard& card)
{
}

CCard::~CCard()
{
	delete m_turnTimer;
	m_turnTimer = NULL;
}

void CCard::Initialize()
{
	//empty
}

void CCard::Shutdown()
{
	//empty
}

void CCard::PowerUp()
{
	//empty
}

UINT CCard::getIdNum()
{
	return m_idNum;
}

void CCard::setIdNum(UINT idNum)
{
	m_idNum = idNum;
}

UINT CCard::getTeamNum()
{
	
	return m_tempNum;
}

void CCard::setTeamNum(UINT teamNum)
{
	m_tempNum = teamNum;
}

void CCard::setCardName(WCHAR* name)
{
	lstrcpy(m_cardName, name);
}

WCHAR* CCard::getCardName()
{
	return m_cardName;
}

Stat CCard::getStat()
{
	return m_cardStat;
}

void CCard::setStat(int maxHp, int hp, int maxAp, int ap, int atk, int def, int spd)
{
	m_cardStat.m_maxHp	= maxHp;
	m_cardStat.m_hp		= hp;
	m_cardStat.m_maxAp	= maxAp;
	m_cardStat.m_ap		= ap;
	m_cardStat.m_atk	= atk;
	m_cardStat.m_def	= def;
	m_cardStat.m_spd	= spd;
}

void CCard::setHp(int hp)
{
	m_cardStat.m_hp = hp;
}

void CCard::setAp(int ap)
{
	m_cardStat.m_ap = ap;
}

int CCard::getUseAp(int num)
{
	return m_useAp[num];
}

void CCard::Restore()
{
	Stat temp = getStat();
	//setStat(temp.m_maxHp, temp.m_maxHp, temp.m_maxAp, temp.m_maxAp, temp.m_atk, temp.m_def, temp.m_spd);
	
	if(m_idNum == 13) {
		setHp(temp.m_maxHp);
	}
	else if(getStat().m_hp <= 0) {
		setHp(0);
	}
	else {
		setHp(temp.m_maxHp);
	}

	setAp(temp.m_maxAp);
	setHit(false);
	m_turnTimer->StopTimer();
}

void CCard::setType(int type)
{
	m_type = type;
}

int CCard::getType()
{
	return  m_type;
}

wchar_t* CCard::getSpdText()
{
	return m_spdText;
}

void CCard::setSpdText(WCHAR* spdText)
{
	lstrcpy(m_spdText, spdText);
}

wchar_t* CCard::getSkillName(int num)
{
	if(num == 0) {
		return m_skill1Name;
	}
	else if(num == 1) {
		return m_skill2Name;
	}
	else if(num == 2) {
		return m_skill3Name;
	}
	return NULL;
	
}

CBitmap* CCard::getCardImage()
{
	return m_cardImage;
}

void CCard::setCardImage(CBitmap* bitmap)
{
	m_cardImage = bitmap;
}

CTextureShader* CCard::getCardShader()
{
	return m_cardShader;
}

void CCard::setCardShader(CTextureShader* shader)
{
	m_cardShader = shader;
}

void CCard::GetCardRect(Qusy::Rect& rect)
{
	Qusy::Rect temp;
	m_cardImage->GetRect(temp);
	temp.posX2 = temp.posX1+m_outputWidth;
	temp.posY2 = temp.posY1+m_outputHeight;
	rect = temp;
}

void CCard::CardRender(int x, int y, int z, float widthRatio, float heightRatio, int shaderType, float opacity)
{
	m_pos.setPosition(x, y, z);
	m_outputWidth = static_cast<int>(CARD_WIDTH * widthRatio);
	m_outputHeight = static_cast<int>(CARD_HEIGHT * heightRatio);
	
	m_cardImage->Render(m_pos.posX, m_pos.posY, m_pos.posZ, widthRatio, heightRatio);

	switch(shaderType)
	{
	case SHADER::TURN:
		m_turnShader->Render(m_cardImage->GetTexture(), getRemainToTurn(), NULL, NULL, opacity);		break;
	case SHADER::BLACK:
		m_blackShader->Render(m_cardImage->GetTexture(), opacity);		break;
	case SHADER::SEPIA:
		m_sepiaShader->Render(m_cardImage->GetTexture(), opacity);		break;
	case SHADER::HIT:
		m_hitShader->Render(m_cardImage->GetTexture(), opacity);		break;
	default:
		m_cardShader->Render(m_cardImage->GetTexture(), opacity);		break;
	}
}

void CCard::CardRender(int x, int y, int z, int outputWidth, int outputHeight, int shaderType, float opacity)
{
	m_pos.setPosition(x, y, z);
	float width = static_cast<float>(outputWidth)/CARD_WIDTH;
	float height = static_cast<float>(outputHeight)/CARD_HEIGHT;
	m_outputWidth = outputWidth;
	m_outputHeight = outputHeight;

	m_cardImage->Render(m_pos.posX, m_pos.posY, m_pos.posZ, width, height);

	switch(shaderType)
	{
	case SHADER::TURN:
		m_turnShader->Render(m_cardImage->GetTexture(), getRemainToTurn(), NULL, NULL, opacity);		break;
	case SHADER::BLACK:
		m_blackShader->Render(m_cardImage->GetTexture(), opacity);		break;
	case SHADER::SEPIA:
		m_sepiaShader->Render(m_cardImage->GetTexture(), opacity);		break;
	case SHADER::HIT:
		m_hitShader->Render(m_cardImage->GetTexture(), opacity);		break;
	default:
		m_cardShader->Render(m_cardImage->GetTexture(), opacity);		break;
	}
}

void CCard::getCardPosition(int& x, int& y)
{
	x = m_pos.posX;
	y = m_pos.posY;
}

bool CCard::IsCardLButtonClick(CInput* input)
{
	Qusy::Point mouse;
	Qusy::Rect rect;

	input->GetMousePoint(mouse.posX, mouse.posY);
	rect.setRect(m_pos.posX, m_pos.posY, m_pos.posX+m_outputWidth, m_pos.posY+m_outputHeight);

	if(input->IsLButtonUp() && Qusy::Collision(mouse, rect)) {
		input->MouseReset();
		return true;
	}

	return false;
}

void CCard::setTurnTimer()
{
	m_turnTimer->SetTimer((float)m_cardStat.m_spd, false);
	m_remainToTurn = (float)m_cardStat.m_spd;
}

void CCard::stopTimer()
{
	m_turnTimer->StopTimer();
}

bool CCard::getMyTurn()
{
	if(CBattleManager::getBattleManager()->GetTurnCard() == this) {
		return true;
	}
	else {
		return false;
	}
}

float CCard::getRemainToTurn()
{
	float result = 0.0f;
	if(getMyTurn()) {
		result = 1.0f;
	}
	else {
		result = 1.0f - (m_turnTimer->RemainTime()/m_remainToTurn);
	}

	return result;
}

void CCard::setHit(bool hit)
{
	m_bHit = hit;
}

bool CCard::getHit()
{
	return m_bHit;
}

int CCard::UseSkill(int num)
{
	return -100;
}