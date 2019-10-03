#pragma once
#include <exception>
#include <fmod/fmod_common.h>

class cAudio_Exception_FMOD :
	public std::exception
{
public:
	cAudio_Exception_FMOD(FMOD_RESULT result);
	
	virtual const char* what() const throw ();

	static void throwIfError(FMOD_RESULT result);

private:
	cAudio_Exception_FMOD();
	FMOD_RESULT m_result;
};

