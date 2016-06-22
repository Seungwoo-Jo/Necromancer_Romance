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

	// ���� �ð���ŭ ���̵� �� �� ����
	void Play(float fadeTime);

	// �ٷ� ����
	void Play();

	// ���� �ð���ŭ ���̵� �ƿ� �� ����
	void Stop(float fadeTime);

	// �ٷ� ����
	void Stop();

	// ���� ����
	void Volume(float);
};