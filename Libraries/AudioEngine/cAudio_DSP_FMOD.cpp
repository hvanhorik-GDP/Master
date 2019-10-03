#include "cAudio_DSP_FMOD.h"
#include "cAudio_Exception_FMOD.h"
#include <cassert>

cAudio_DSP_FMOD::cAudio_DSP_FMOD()
{
}

cAudio_DSP_FMOD::~cAudio_DSP_FMOD()
{
	if (m_dsp)
	{
		m_dsp->release();
		m_dsp = NULL;
	}
}

void cAudio_DSP_FMOD::Release()
{
	if (m_dsp)
	{
		m_dsp->release();
		m_dsp = NULL;
	}
}

bool cAudio_DSP_FMOD::GetBypass() const
{
	bool bypass = false;
	assert(m_dsp);
	if (m_dsp)
	{
		m_result = m_dsp->getBypass(&bypass);
		cAudio_Exception_FMOD::throwIfError(m_result);
	}
	return bypass;
}

void cAudio_DSP_FMOD::SetBypass(bool to)
{
	if (m_dsp)
	{
		m_result = m_dsp->setBypass(to);
		cAudio_Exception_FMOD::throwIfError(m_result);
	}
}

bool cAudio_DSP_FMOD::GetActive() const
{
	bool active = false;
	assert(m_dsp);
	if (m_dsp)
	{
		m_result = m_dsp->getActive(&active);
		cAudio_Exception_FMOD::throwIfError(m_result);
	}
	return active;
}

void cAudio_DSP_FMOD::SetActive(bool to)
{
	if (m_dsp)
	{
		m_result = m_dsp->setActive(to);
		cAudio_Exception_FMOD::throwIfError(m_result);
	}
}

std::ostream& operator<<(std::ostream& stream, const cAudio_DSP_FMOD& val)
{
	// Todo - Dump the system information
	return stream;
}