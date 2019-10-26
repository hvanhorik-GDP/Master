#include "cObject_ChannelControl.h"

cObject_ChannelControl::cObject_ChannelControl()
	: iObject_ChannelControl()
{
}

cObject_ChannelControl::~cObject_ChannelControl()
{
}

// For debugging purposes - dumps the contents in human readable form
std::ostream& operator<<(std::ostream& stream, const cObject_ChannelControl& val)
{
	stream << "std::ostream& operator<<(std::ostream& stream, const cObject_ChannelControl& val)" << "Not Implemented" << std::endl;
	return stream;
}

bool cObject_ChannelControl::getPaused()
{
	return m_Paused;
}

float cObject_ChannelControl::getVolume()
{
	return m_Volume;
}
bool cObject_ChannelControl::getVolumeRamp()
{
	return m_VolunmeRamp;
}

float cObject_ChannelControl::getAudibility()
{
	return m_Audibility;
}

float cObject_ChannelControl::getPitch()
{
	return 	m_Pitch;
}

bool cObject_ChannelControl::getMute()
{
	return m_Mute;
}

bool cObject_ChannelControl::isPlaying()
{
	return m_Playing;
}
