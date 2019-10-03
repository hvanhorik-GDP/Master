#include "cAudio_ChannelGroup_FMOD.h"
#include "cAudio_Exception_FMOD.h"

cAudio_ChannelGroup_FMOD::cAudio_ChannelGroup_FMOD()
{
}

cAudio_ChannelGroup_FMOD::~cAudio_ChannelGroup_FMOD()
{
	if (m_channelGroup)
	{
		m_channelGroup->release();
		m_channelGroup = NULL;
	}
}

void cAudio_ChannelGroup_FMOD::Release()
{
	if (m_channelGroup)
	{
		m_channelGroup->release();
		m_channelGroup = NULL;
	}
}

std::ostream& operator<<(std::ostream& stream, const cAudio_ChannelGroup_FMOD& val)
{
	// Todo - Dump the system information
	return stream;
}
