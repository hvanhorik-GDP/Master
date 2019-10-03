#include "cAudio_DSPConnection_FMOD.h"
#include "cAudio_Exception_FMOD.h"
#include <cassert>

cAudio_DSPConnection_FMOD::cAudio_DSPConnection_FMOD()
{
}

cAudio_DSPConnection_FMOD::~cAudio_DSPConnection_FMOD()
{
	if (m_dspConnection)
	{
//		m_dspConnection->release();
		m_dspConnection = NULL;
	}
}

void cAudio_DSPConnection_FMOD::Release()
{
	if (m_dspConnection)
	{
//		m_dspConnection->release();
		m_dspConnection = NULL;
	}
}

std::ostream& operator<<(std::ostream& stream, const cAudio_DSPConnection_FMOD& val)
{
	// Todo - Dump the system information
	return stream;
}