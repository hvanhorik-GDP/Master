#pragma once
#include <fmod/fmod.hpp>
#include <ostream>

class cAudio_DSPConnection_FMOD
{
public:


	cAudio_DSPConnection_FMOD();
	virtual ~cAudio_DSPConnection_FMOD();

	void Release();

	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const cAudio_DSPConnection_FMOD& val);

private:
	FMOD::DSPConnection* m_dspConnection;
	mutable FMOD_RESULT m_result;
	friend class cAudio_System_FMOD;
};

//FMOD_RESULT F_API getInput(DSP** input);
//FMOD_RESULT F_API getOutput(DSP** output);
//FMOD_RESULT F_API setMix(float volume);
//FMOD_RESULT F_API getMix(float* volume);
//FMOD_RESULT F_API setMixMatrix(float* matrix, int outchannels, int inchannels, int inchannel_hop = 0);
//FMOD_RESULT F_API getMixMatrix(float* matrix, int* outchannels, int* inchannels, int inchannel_hop = 0);
//FMOD_RESULT F_API getType(FMOD_DSPCONNECTION_TYPE* type);
//
//// Userdata set/get.
//FMOD_RESULT F_API setUserData(void* userdata);
//FMOD_RESULT F_API getUserData(void** userdata);
