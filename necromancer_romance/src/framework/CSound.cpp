#include "CSound.h"
#include "CTime.h"

FMOD::System* CSound::s_soundSystem = 0;

void ERRCHECK(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {

    }
}

CSound::CSound()
{
	m_sound = 0;
	m_key = 0;
	m_version = 0;
	m_bPlay = false;
	m_bLoop = true;

	m_fadeTimer = nullptr;
}

CSound::~CSound()
{

}

void CSound::Initialize(char* fileName)
{
	FMOD_RESULT result;
	if(s_soundSystem == 0)
	{
		result = FMOD::System_Create(&s_soundSystem);
		ERRCHECK(result);

		result = s_soundSystem->getVersion(&m_version);
		ERRCHECK(result);

		s_soundSystem->init(32, FMOD_INIT_NORMAL, 0);
	}

	m_fadeTimer = new CTime();
	m_bFirstStop = true;
	result = s_soundSystem->createSound(fileName, FMOD_HARDWARE, 0, &m_sound);
}

void CSound::Shutdown()
{
	FMOD_RESULT result;
	if(s_soundSystem != 0) {
		result = s_soundSystem->close();
		result = s_soundSystem->release();
		ERRCHECK(result);
		s_soundSystem = 0;
	}

	if(m_fadeTimer != nullptr)
	{
		m_fadeTimer->StopTimer();
		delete m_fadeTimer;
		m_fadeTimer = nullptr;
	}
}

void CSound::Release()
{
	FMOD_RESULT result;
	if(m_sound != 0) {
		result = m_sound->release();
		ERRCHECK(result);
		m_sound = 0;
	}
}

void CSound::Loop(bool loop)
{
	m_bLoop = loop;

	if(m_bLoop) {
		m_Channel->setMode(FMOD_HARDWARE|FMOD_LOOP_NORMAL);
		m_bPlay = false;
	}
	else {
		m_Channel->setMode(FMOD_HARDWARE|FMOD_LOOP_OFF);
	}
}

void CSound::Reset()
{
	m_bPlay = false;
	m_bLoop = false;
	m_bFirstStop = true;
}

void CSound::Play(float fadeTime)
{
	bool b_playing = false;
	m_Channel->isPlaying(&b_playing);

	if(!b_playing)
	{
		if(!m_bPlay) {
			s_soundSystem->playSound(FMOD_CHANNEL_FREE, m_sound, false, &m_Channel);

			if(m_bLoop) {
				m_bPlay = false;
			}
			else {
				m_bPlay = true;
			}
		}

		m_fadeTimer->SetTimer(fadeTime, false);
		Volume( 1.0f - (m_fadeTimer->RemainTime() / m_fadeTimer->GetSetTime()) );
	}
}

void CSound::Play()
{
	bool b_playing = false;
	m_Channel->isPlaying(&b_playing);

	if(!b_playing)
	{
		if(!m_bPlay) {
			s_soundSystem->playSound(FMOD_CHANNEL_FREE, m_sound, false, &m_Channel);

			if(m_bLoop) {
				m_bPlay = false;
			}
			else {
				m_bPlay = true;
			}
		}
	}
}

void CSound::Stop(float fadeTime)
{
	bool b_playing = false;
	m_Channel->isPlaying(&b_playing);

	if(m_bFirstStop) {
		m_fadeTimer->SetTimer(fadeTime, false);
		m_bFirstStop = false;
	}
	
	if(b_playing)
	{
		if((m_fadeTimer->RemainTime() / m_fadeTimer->GetSetTime()) == 0.0f) {
			m_Channel->stop();
		}
		else {
			Volume( (m_fadeTimer->RemainTime() / m_fadeTimer->GetSetTime()) );
		}
	}

	
}

void CSound::Stop()
{
	bool b_playing = false;
	m_Channel->isPlaying(&b_playing);

	if(b_playing)
	{
		m_Channel->stop();
	}
}

void CSound::Volume(float volume)
{
	m_Channel->setVolume(volume);
}