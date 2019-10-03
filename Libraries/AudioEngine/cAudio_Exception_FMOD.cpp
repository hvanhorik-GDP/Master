#include "cAudio_Exception_FMOD.h"
#include <sstream>
#include <iostream>

cAudio_Exception_FMOD::cAudio_Exception_FMOD(FMOD_RESULT result)
	: std::exception()
	, m_result(result)
{
}

const char* cAudio_Exception_FMOD::what() const throw ()
{
	std::stringstream ss;
	ss << "FMOD exception: Value = " << m_result;
	static std::string msg = ss.str();
	return msg.c_str();
}

void cAudio_Exception_FMOD::throwIfError(FMOD_RESULT result)
{
	if (result != FMOD_OK) {
		std::cout << "FMOD error: " << result << std::endl;
		throw cAudio_Exception_FMOD(result);
	}
}
