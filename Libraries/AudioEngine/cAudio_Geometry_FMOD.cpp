#include "cAudio_Geometry_FMOD.h"
#include "cAudio_Exception_FMOD.h"

cAudio_Geometry_FMOD::cAudio_Geometry_FMOD()
{
}

cAudio_Geometry_FMOD::~cAudio_Geometry_FMOD()
{
	if (m_geometry)
	{
		m_geometry->release();
		m_geometry = NULL;
	}
}

void cAudio_Geometry_FMOD::Release()
{
	if (m_geometry)
	{
		m_geometry->release();
		m_geometry = NULL;
	}
}

std::ostream& operator<<(std::ostream& stream, const cAudio_Geometry_FMOD& val)
{
	// Todo - Dump the system information
	return stream;
}