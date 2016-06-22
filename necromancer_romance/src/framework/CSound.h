#include "fmod.hpp"
#include "fmod_errors.h"

class CTime;

class CSound 
{
private:
	static FMOD::System     *s_soundSystem;
	FMOD::Channel			*m_Channel;
    FMOD::Sound				*m_sound;
    
    int						m_key;
    unsigned int			m_version;

	CTime* m_fadeTimer;

	bool m_bPlay;
	bool m_bLoop;
	bool m_bFirstStop;

public:
	CSound();
	~CSound();
	
	void Initialize(char*);
	void Initialize(char*, int);
	void Shutdown();
	void Release();
	void Loop(bool);
	void Reset();

	// 일정 시간만큼 페이드 인 후 시작
	void Play(float fadeTime);

	// 바로 시작
	void Play();

	// 일정 시간만큼 페이드 아웃 후 정지
	void Stop(float fadeTime);

	// 바로 정지
	void Stop();

	// 볼륨 조절
	void Volume(float);
};