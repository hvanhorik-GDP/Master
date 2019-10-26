#pragma once
#include "cObject_Common.h"
#include <vector>

class iObject_ChannelControl
{
public:
	// This structure matches the file, so that our life is
	//   simpler and happier, and we all get along.

	iObject_ChannelControl() {};				// Get's filled in by physics
	virtual ~iObject_ChannelControl() {}

	virtual void IntegrationStep(float deltaTime) = 0;

	// Recieve a message
	virtual bool RecieveMessage(const iMessage& message) final;

	// Recieve a message and reply
	virtual bool RecieveAndRespond(const iMessage& in, iMessage& reply) final;

	//FMOD_RESULT F_API stop();
	//FMOD_RESULT F_API setPaused(bool paused);
	virtual bool getPaused() = 0;
	//FMOD_RESULT F_API setVolume(float volume);
	virtual float getVolume() = 0;
	//FMOD_RESULT F_API setVolumeRamp(bool ramp);
	virtual bool getVolumeRamp() = 0;

	virtual float getAudibility() = 0;
	//FMOD_RESULT F_API setPitch(float pitch);
	virtual float getPitch() = 0;
	//FMOD_RESULT F_API setMute(bool mute);
	virtual bool getMute() = 0;
	//FMOD_RESULT F_API setReverbProperties(int instance, float wet);
	//FMOD_RESULT F_API getReverbProperties(int instance, float* wet);
	//FMOD_RESULT F_API setLowPassGain(float gain);
	//FMOD_RESULT F_API getLowPassGain(float* gain);
	//FMOD_RESULT F_API setMode(FMOD_MODE mode);
	//FMOD_RESULT F_API getMode(FMOD_MODE* mode);
	//FMOD_RESULT F_API setCallback(FMOD_CHANNELCONTROL_CALLBACK callback);
	virtual bool isPlaying() = 0;

	//// Panning and level adjustment.
	//// Note all 'set' functions alter a final matrix, this is why the only get function is getMixMatrix, to avoid other get functions returning incorrect/obsolete values.
	//FMOD_RESULT F_API setPan(float pan);
	//FMOD_RESULT F_API setMixLevelsOutput(float frontleft, float frontright, float center, float lfe, float surroundleft, float surroundright, float backleft, float backright);
	//FMOD_RESULT F_API setMixLevelsInput(float* levels, int numlevels);
	//FMOD_RESULT F_API setMixMatrix(float* matrix, int outchannels, int inchannels, int inchannel_hop = 0);
	//FMOD_RESULT F_API getMixMatrix(float* matrix, int* outchannels, int* inchannels, int inchannel_hop = 0);

	//// Clock based functionality.
	//FMOD_RESULT F_API getDSPClock(unsigned long long* dspclock, unsigned long long* parentclock);
	//FMOD_RESULT F_API setDelay(unsigned long long dspclock_start, unsigned long long dspclock_end, bool stopchannels = true);
	//FMOD_RESULT F_API getDelay(unsigned long long* dspclock_start, unsigned long long* dspclock_end, bool* stopchannels = 0);
	//FMOD_RESULT F_API addFadePoint(unsigned long long dspclock, float volume);
	//FMOD_RESULT F_API setFadePointRamp(unsigned long long dspclock, float volume);
	//FMOD_RESULT F_API removeFadePoints(unsigned long long dspclock_start, unsigned long long dspclock_end);
	//FMOD_RESULT F_API getFadePoints(unsigned int* numpoints, unsigned long long* point_dspclock, float* point_volume);

	//// DSP effects.
	//FMOD_RESULT F_API getDSP(int index, DSP** dsp);
	//FMOD_RESULT F_API addDSP(int index, DSP* dsp);
	//FMOD_RESULT F_API removeDSP(DSP* dsp);
	//FMOD_RESULT F_API getNumDSPs(int* numdsps);
	//FMOD_RESULT F_API setDSPIndex(DSP* dsp, int index);
	//FMOD_RESULT F_API getDSPIndex(DSP* dsp, int* index);

	//// 3D functionality.
	//FMOD_RESULT F_API set3DAttributes(const FMOD_VECTOR* pos, const FMOD_VECTOR* vel);
	//FMOD_RESULT F_API get3DAttributes(FMOD_VECTOR* pos, FMOD_VECTOR* vel);
	//FMOD_RESULT F_API set3DMinMaxDistance(float mindistance, float maxdistance);
	//FMOD_RESULT F_API get3DMinMaxDistance(float* mindistance, float* maxdistance);
	//FMOD_RESULT F_API set3DConeSettings(float insideconeangle, float outsideconeangle, float outsidevolume);
	//FMOD_RESULT F_API get3DConeSettings(float* insideconeangle, float* outsideconeangle, float* outsidevolume);
	//FMOD_RESULT F_API set3DConeOrientation(FMOD_VECTOR* orientation);
	//FMOD_RESULT F_API get3DConeOrientation(FMOD_VECTOR* orientation);
	//FMOD_RESULT F_API set3DCustomRolloff(FMOD_VECTOR* points, int numpoints);
	//FMOD_RESULT F_API get3DCustomRolloff(FMOD_VECTOR** points, int* numpoints);
	//FMOD_RESULT F_API set3DOcclusion(float directocclusion, float reverbocclusion);
	//FMOD_RESULT F_API get3DOcclusion(float* directocclusion, float* reverbocclusion);
	//FMOD_RESULT F_API set3DSpread(float angle);
	//FMOD_RESULT F_API get3DSpread(float* angle);
	//FMOD_RESULT F_API set3DLevel(float level);
	//FMOD_RESULT F_API get3DLevel(float* level);
	//FMOD_RESULT F_API set3DDopplerLevel(float level);
	//FMOD_RESULT F_API get3DDopplerLevel(float* level);
	//FMOD_RESULT F_API set3DDistanceFilter(bool custom, float customLevel, float centerFreq);
	//FMOD_RESULT F_API get3DDistanceFilter(bool* custom, float* customLevel, float* centerFreq);

	//// Userdata set/get.
	//FMOD_RESULT F_API setUserData(void* userdata);
	//FMOD_RESULT F_API getUserData(void** userdata);

	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const iObject_ChannelControl& val);

private:
	friend class cObjectManager_Channel;
};

