#include "cAudio_Reverb3D_FMOD.h"
#include "cAudio_Exception_FMOD.h"

cAudio_Reverb3D_FMOD::cAudio_Reverb3D_FMOD()
{
}

cAudio_Reverb3D_FMOD::~cAudio_Reverb3D_FMOD()
{
	if (m_Reverb3d)
	{
		m_Reverb3d->release();
		m_Reverb3d = NULL;
	}
}

void cAudio_Reverb3D_FMOD::Release()
{
	if (m_Reverb3d)
	{
		m_Reverb3d->release();
		m_Reverb3d = NULL;
	}
}

std::ostream& operator<<(std::ostream& stream, const cAudio_Reverb3D_FMOD& val)
{
	// Todo - Dump the system information
	return stream;
}