#include "cAudio_System_FMOD.h"
#include "cAudio_Exception_FMOD.h"
#include "cAudio_Sound_FMOD.h"
#include <exception>
#include <sstream>
#include <cassert>


cAudio_System_FMOD::cAudio_System_FMOD()
{
}

cAudio_System_FMOD::~cAudio_System_FMOD()
{
	if (m_system)
	{
		// No Error checking during destruction
		if (m_isInit)
		{
			m_result = m_system->close();
		}
		m_result = m_system->release();
	}
}


void cAudio_System_FMOD::Init(int maxchannels, iAudio_System::InitFlags flags)
{
	m_result = FMOD::System_Create(&m_system);
	cAudio_Exception_FMOD::throwIfError(m_result);

	m_result = m_system->init(maxchannels, flags, NULL);
	cAudio_Exception_FMOD::throwIfError(m_result);
	m_isInit = true;
}

 void cAudio_System_FMOD::Close()
 {
	 if (m_system) {
		 if (m_isInit)
		 {
			 m_result = m_system->close();
			 cAudio_Exception_FMOD::throwIfError(m_result);
		 }
		 m_isInit = false;
		 m_result = m_system->release();
		 cAudio_Exception_FMOD::throwIfError(m_result);
	 }
 }


 void cAudio_System_FMOD::Update()
 {
	 assert(m_system != NULL);
	 if (m_system)
	 {
		 m_result = m_system->update();
		 cAudio_Exception_FMOD::throwIfError(m_result);
	 }
 }


 cAudio_System_FMOD::sCPUUsage cAudio_System_FMOD::GetCPUUsage() const
 {
	 cAudio_System_FMOD::sCPUUsage cpu;
	 assert(m_system);
	 if (m_system)
	 {
		 m_result = m_system->getCPUUsage(&cpu.dsp, &cpu.stream, &cpu.geometry, &cpu.update, &cpu.total);
		 cAudio_Exception_FMOD::throwIfError(m_result);
	 }
	 return cpu;
 }

 void cAudio_System_FMOD::CreateSound(cAudio_Sound_FMOD& sound, const std::string path, FMOD_MODE mode)
 {
	 assert(m_system);
	 if (m_system)
	 {
		 m_result = m_system->createSound(path.c_str(), mode, 0, &sound.m_sound);
		 cAudio_Exception_FMOD::throwIfError(m_result);
	 }
 }

 void cAudio_System_FMOD::PlaySound(const cAudio_Sound_FMOD& sound, cAudio_Channel_FMOD& channel)
 {
	 assert(m_system);
	 if (m_system)
	 {
		 // TODO ChannelGroup
		 FMOD::ChannelGroup* group = NULL;
		 m_result = m_system->playSound(sound.m_sound, group, channel.isPaused(), &channel.m_channel);
		 cAudio_Exception_FMOD::throwIfError(m_result);
	 }
 }

 void cAudio_System_FMOD::CreateDSP(cAudio_DSP_FMOD& dsp, const std::string path, FMOD_MODE mode)
 {
	 assert(m_system);
	 if (m_system)
	 {
		 m_result = m_system->createDSP(0, &dsp.m_dsp);
		 cAudio_Exception_FMOD::throwIfError(m_result);
	 }
 }

 //FMOD_RESULT F_API createChannelGroup(const char* name, ChannelGroup** channelgroup);
 void cAudio_System_FMOD::CreateChannelGroup(const std::string& name, cAudio_ChannelGroup_FMOD& group)
 {
	 assert(m_system);
	 if (m_system)
	 {
		 m_result = m_system->createChannelGroup(name.c_str(), &group.m_channelGroup);
		 cAudio_Exception_FMOD::throwIfError(m_result);
	 }

 }

 //FMOD_RESULT F_API createSoundGroup(const char* name, SoundGroup** soundgroup);
 void cAudio_System_FMOD::CreateSoundGroup(const std::string& name, cAudio_SoundGroup_FMOD& group)
 {
	 assert(m_system);
	 if (m_system)
	 {
		 m_result = m_system->createSoundGroup(name.c_str(), &group.m_soundGroup);
		 cAudio_Exception_FMOD::throwIfError(m_result);
	 }
 }

 //FMOD_RESULT F_API createReverb3D(Reverb3D** reverb);
 void cAudio_System_FMOD::CreateReverb3D(cAudio_Reverb3D_FMOD& reverb)
 {
	 assert(m_system);
	 if (m_system)
	 {
		 m_result = m_system->createReverb3D(&reverb.m_Reverb3d);
		 cAudio_Exception_FMOD::throwIfError(m_result);
	 }

 }

 //FMOD_RESULT F_API playDSP(DSP* dsp, ChannelGroup* channelgroup, bool paused, Channel** channel);
 void cAudio_System_FMOD::PlayDSP(const cAudio_DSP_FMOD& dsp, const cAudio_ChannelGroup_FMOD& group, bool paused, cAudio_Channel_FMOD& outChannel)
 {
	 assert(m_system);
	 if (m_system)
	 {
		 m_result = m_system->playDSP(dsp.m_dsp , group.m_channelGroup, paused, &outChannel.m_channel);
		 cAudio_Exception_FMOD::throwIfError(m_result);
	 }
 }

 //FMOD_RESULT F_API getChannel(int channelid, Channel** channel);
 void cAudio_System_FMOD::GetChannel(int id, cAudio_Channel_FMOD& out)
 {

 }

 //FMOD_RESULT F_API getMasterChannelGroup(ChannelGroup** channelgroup);
 void cAudio_System_FMOD::GetMasterChannelGroup(cAudio_ChannelGroup_FMOD& out)
 {
	 assert(m_system);
	 if (m_system)
	 {
		 m_result = m_system->getMasterChannelGroup(&out.m_channelGroup);
		 cAudio_Exception_FMOD::throwIfError(m_result);
	 }

 }

 //FMOD_RESULT F_API getMasterSoundGroup(SoundGroup** soundgroup);
 void cAudio_System_FMOD::GetMasterSoundGroup(cAudio_SoundGroup_FMOD& out)
 {
	 assert(m_system);
	 if (m_system)
	 {
		 m_result = m_system->getMasterSoundGroup(&out.m_soundGroup);
		 cAudio_Exception_FMOD::throwIfError(m_result);
	 }

 }

 std::ostream& operator<<(std::ostream& stream, const cAudio_System_FMOD& val)
 {
	 // Todo - Dump the system information
	 return stream;
 }
