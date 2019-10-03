#include "cAudio_Channel_FMOD.h"
#include "cAudio_Exception_FMOD.h"

cAudio_Channel_FMOD::cAudio_Channel_FMOD()
{

}
cAudio_Channel_FMOD::~cAudio_Channel_FMOD()
{

}

bool cAudio_Channel_FMOD::isPaused() const
{
	bool paused = false;
	if (m_channel) {

		m_result = m_channel->getPaused(&paused);
		cAudio_Exception_FMOD::throwIfError(m_result);

	}
	return paused;
}

void cAudio_Channel_FMOD::Pause(bool new_is_paused)
{
	if (m_channel) {
		m_result = m_channel->setPaused(new_is_paused);
		cAudio_Exception_FMOD::throwIfError(m_result);
	}
}

bool cAudio_Channel_FMOD::isPlaying() const
{
	bool playing = false;
	if (m_channel) {
		m_result = m_channel->isPlaying(&playing);
		cAudio_Exception_FMOD::throwIfError(m_result);
	}
	return playing;
}

unsigned int cAudio_Channel_FMOD::GetPosition(FMOD_TIMEUNIT units) const
{
	unsigned int pos = 0;
	if (m_channel)
	{
		m_result = m_channel->getPosition(&pos, units);
		cAudio_Exception_FMOD::throwIfError(m_result);
	}
	return pos;
}

void cAudio_Channel_FMOD::SetPosition(unsigned int pos, FMOD_TIMEUNIT units)
{
	if (m_channel)
	{
		m_result = m_channel->setPosition(pos, units);
		cAudio_Exception_FMOD::throwIfError(m_result);
	}
}

float cAudio_Channel_FMOD::GetVolume() const
{
	float volume = 0;
	if (m_channel)
	{
		m_result = m_channel->getVolume(&volume);
		cAudio_Exception_FMOD::throwIfError(m_result);
	}

	return volume;
}

void cAudio_Channel_FMOD::SetVolume(float newVol)
{
	if (m_channel) 
	{
		m_result = m_channel->setVolume(newVol);
		cAudio_Exception_FMOD::throwIfError(m_result);
	}
}

float cAudio_Channel_FMOD::GetPitch() const
{
	float pitch = 0;
	if (m_channel)
	{
		m_result = m_channel->getPitch(&pitch);
		cAudio_Exception_FMOD::throwIfError(m_result);
	}

	return pitch;
}

void cAudio_Channel_FMOD::SetPitch(float nePitch)
{
	if (m_channel) 
	{
		m_result = m_channel->setPitch(nePitch);
		cAudio_Exception_FMOD::throwIfError(m_result);
	}
}

std::ostream& operator<<(std::ostream& stream, const cAudio_Channel_FMOD& val)
{
	// Todo - Dump the system information
	return stream;
}
