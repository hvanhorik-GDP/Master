#pragma once
#include <fmod/fmod.hpp>
#include <ostream>

class cAudio_SoundGroup_FMOD
{
public:

	cAudio_SoundGroup_FMOD();
	virtual ~cAudio_SoundGroup_FMOD();

	void Release();

	friend std::ostream& operator<<(std::ostream& stream, const cAudio_SoundGroup_FMOD& val);

private:
	FMOD::SoundGroup* m_soundGroup = NULL;
	mutable FMOD_RESULT m_result;
	friend class cAudio_System_FMOD;
};

//FMOD_RESULT F_API release();
//FMOD_RESULT F_API getSystemObject(System** system);
//
//// SoundGroup control functions.
//FMOD_RESULT F_API setMaxAudible(int maxaudible);
//FMOD_RESULT F_API getMaxAudible(int* maxaudible);
//FMOD_RESULT F_API setMaxAudibleBehavior(FMOD_SOUNDGROUP_BEHAVIOR behavior);
//FMOD_RESULT F_API getMaxAudibleBehavior(FMOD_SOUNDGROUP_BEHAVIOR* behavior);
//FMOD_RESULT F_API setMuteFadeSpeed(float speed);
//FMOD_RESULT F_API getMuteFadeSpeed(float* speed);
//FMOD_RESULT F_API setVolume(float volume);
//FMOD_RESULT F_API getVolume(float* volume);
//FMOD_RESULT F_API stop();
//
//// Information only functions.
//FMOD_RESULT F_API getName(char* name, int namelen);
//FMOD_RESULT F_API getNumSounds(int* numsounds);
//FMOD_RESULT F_API getSound(int index, Sound** sound);
//FMOD_RESULT F_API getNumPlaying(int* numplaying);
//
//// Userdata set/get.
//FMOD_RESULT F_API setUserData(void* userdata);
//FMOD_RESULT F_API getUserData(void** userdata);