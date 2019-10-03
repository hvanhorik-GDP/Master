#pragma once
#include <fmod/fmod.hpp>
#include <ostream>

class cAudio_Reverb3D_FMOD
{
public:

	cAudio_Reverb3D_FMOD();
	virtual ~cAudio_Reverb3D_FMOD();

	void Release();

	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const cAudio_Reverb3D_FMOD& val);

private:
	FMOD::Reverb3D* m_Reverb3d;
	mutable FMOD_RESULT m_result;
	friend class cAudio_System_FMOD;
};
//
//FMOD_RESULT F_API release();
//
//// Reverb manipulation.
//FMOD_RESULT F_API set3DAttributes(const FMOD_VECTOR* position, float mindistance, float maxdistance);
//FMOD_RESULT F_API get3DAttributes(FMOD_VECTOR* position, float* mindistance, float* maxdistance);
//FMOD_RESULT F_API setProperties(const FMOD_REVERB_PROPERTIES* properties);
//FMOD_RESULT F_API getProperties(FMOD_REVERB_PROPERTIES* properties);
//FMOD_RESULT F_API setActive(bool active);
//FMOD_RESULT F_API getActive(bool* active);
//
//// Userdata set/get.
//FMOD_RESULT F_API setUserData(void* userdata);
//FMOD_RESULT F_API getUserData(void** userdata);
