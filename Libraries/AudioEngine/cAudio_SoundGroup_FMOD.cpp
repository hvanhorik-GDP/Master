#include "cAudio_SoundGroup_FMOD.h"
#include "cAudio_Exception_FMOD.h"

cAudio_SoundGroup_FMOD::cAudio_SoundGroup_FMOD()
{
}

cAudio_SoundGroup_FMOD::~cAudio_SoundGroup_FMOD()
{
	if (m_soundGroup)
	{
		m_soundGroup->release();
		m_soundGroup = NULL;
	}
}

void cAudio_SoundGroup_FMOD::Release()
{
	if (m_soundGroup)
	{
		m_soundGroup->release();
		m_soundGroup = NULL;
	}
}

std::ostream& operator<<(std::ostream& stream, const cAudio_SoundGroup_FMOD& val)
{
	// Todo - Dump the system information
	return stream;
}