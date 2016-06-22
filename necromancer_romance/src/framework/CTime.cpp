#include <Windows.h>
#include "CTime.h"

CTime::CTime()
{
	m_time = 0;
	m_sec = 0;
	m_pause = 0;
	m_bRepeat = false;
}

CTime::CTime(const CTime& temp)
{
}

CTime::~CTime()
{
}

void CTime::SetTimer(float sec, bool repeat = false)
{
	m_sec = sec;
	m_bRepeat = repeat;

	m_time = GetTickCount() + static_cast<unsigned int>(1000 * m_sec);
}

void CTime::AddTime(float sec)
{
	m_time += static_cast<unsigned int>(1000 * m_sec);
}

void CTime::SubTime(float sec)
{
	m_time -= static_cast<unsigned int>(1000 * m_sec);
}

float CTime::GetSetTime()
{
	return m_sec;
}

bool CTime::GetTimer()
{
	if(m_time != 0)
	{
		if(GetTickCount() >= m_time)
		{
			if(m_bRepeat) {
				m_time = GetTickCount() + static_cast<unsigned int>(1000 * m_sec);	
			}
			else  {
				m_time = 0;
			}
			return true;
		}
		else
		{
			return false;
		}
	}
	else 
	{
		return true;
	}
}

void CTime::StopTimer()
{
	m_time = GetTickCount();
}

void CTime::PauseTimer(bool pause)
{
	if(pause) {
		//m_pause = m_time - GetTickCount();
	}
	else {

	}
}

float CTime::RemainTime()
{
	if(m_time != 0)
	{
		if(!GetTimer()) {
			unsigned int temp = m_time - GetTickCount();
			return static_cast<float>(temp * 0.001f);
		}
	}
	return 0;
}