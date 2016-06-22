// ..\framework
#include "..\framework\CInput.h"
#include "..\framework\common.h"
#include "..\framework\CBitmap.h"
#include "..\framework\CTextureShader.h"
#include "..\framework\CTime.h"

// ..\managers
#include "..\managers\CNero.h"

// ..\objects
#include "CObject_ExploreBar.h"

CObject_ExploreBar::CObject_ExploreBar()
{
	m_exploreBar = NULL;
	m_nero = NULL;
	m_hero = NULL;
	for(int i=0; i<3; i++) {
		m_shader[i] = NULL;
	}
	m_fadeTimer = NULL;
	m_bShow = false;
}

CObject_ExploreBar::CObject_ExploreBar(const CObject_ExploreBar& object)
{
}

CObject_ExploreBar::~CObject_ExploreBar()
{
}

void CObject_ExploreBar::Initalize()
{
	setPosition(75, 15, 10);
	m_exploreBar = new CBitmap();
	m_exploreBar->Initialize(L"res/field/explore_bar.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	
	m_hero = new CBitmap();
	m_hero->Initialize(L"res/field/explore_hero.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	m_hero->SetSpriteAnimation(4, 1, 800, true);

	m_nero = new CBitmap();
	m_nero->Initialize(L"res/field/explore_nero.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	for(int i=0; i<3; i++) {
		m_shader[i] = new CTextureShader();
		m_shader[i]->Initialize(NULL, NULL);
	}
	m_heroTimer = new CTime();
	m_heroTimer->SetTimer(1.2f, false);
	m_fadeTimer = new CTime();
}

void CObject_ExploreBar::Shutdown()
{
	if(m_exploreBar != NULL)
	{
		m_exploreBar->Shutdown();
		SAFE_DELETE(m_exploreBar);
	}

	for(int i=0; i<3; i++)
	{
		if(m_shader[i] != NULL)
		{
			m_shader[i]->Shutdown();
			SAFE_DELETE(m_shader[i]);
		}
	}

	if(m_heroTimer != NULL)
	{
		m_heroTimer->StopTimer();
		SAFE_DELETE(m_heroTimer);
	}
	if(m_fadeTimer != NULL)
	{
		m_fadeTimer->StopTimer();
		SAFE_DELETE(m_fadeTimer);
	}
}

void CObject_ExploreBar::Update(CInput* input)
{
	if(m_heroTimer->GetTimer())
	{
		m_heroTimer->SetTimer(1.0f, true);
		CNero::getNero()->SetExploreHero(CNero::getNero()->GetExploreHero() + 0.5f);
	}
}

void CObject_ExploreBar::Render()
{
	if(m_bShow)
	{
		Qusy::Position pos = getPosition();
		m_exploreBar->Render(pos.posX, pos.posY, pos.posZ);
		m_shader[0]->Render(m_exploreBar->GetTexture(), getOpacity());

		float tempX = CNero::getNero()->GetExploreHero();
		if(tempX >= 999.9f) {
			tempX = 999.9f;
		}
		if(CNero::getNero()->m_bShoa) {
			m_hero->Render((int)(pos.posX+tempX+40.0f), pos.posY, pos.posZ-1);
			m_shader[1]->Render(m_hero->GetTexture(), getOpacity());
		}
		tempX = CNero::getNero()->GetExploreNero();
		if(tempX >= 999.9f) {
			tempX = 999.9f;
		}
		m_nero->Render((int)(pos.posX+tempX+40.0f), pos.posY, pos.posZ-1);
		m_shader[2]->Render(m_nero->GetTexture(), getOpacity());
	}
}

void CObject_ExploreBar::Show(bool show)
{
	if(m_bShow != show)
	{
		m_fadeTimer->SetTimer(1.0f, false);
		m_bShow = show;
	}
}