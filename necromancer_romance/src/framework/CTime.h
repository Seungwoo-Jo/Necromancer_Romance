#ifndef _CTIME_H_
#define _CTIME_H_

// Class name: CTime //
class CTime
{	
private:
	unsigned int m_time;
	float m_sec;
	float m_pause;
	bool m_bRepeat;

public:
	CTime();
	CTime(const CTime&);
	~CTime();

	void SetTimer(float, bool);
	void AddTime(float);
	void SubTime(float);
	float GetSetTime();
	bool GetTimer();
	void StopTimer();
	void PauseTimer(bool);
	float RemainTime();
};

#endif