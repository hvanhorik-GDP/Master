#pragma once
#include <fmod/fmod.hpp>
#include <ostream>

class cAudio_ChannelGroup_FMOD
{
public:
	cAudio_ChannelGroup_FMOD();
	virtual ~cAudio_ChannelGroup_FMOD();

	void Release();
	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const cAudio_ChannelGroup_FMOD& val);

private:
	FMOD::ChannelGroup* m_channelGroup;
	mutable FMOD_RESULT m_result;

	friend class cAudio_System_FMOD;
};

//FMOD_RESULT F_API release();
//
//// Nested channel groups.
//FMOD_RESULT F_API addGroup(ChannelGroup* group, bool propagatedspclock = true, DSPConnection** connection = 0);
//FMOD_RESULT F_API getNumGroups(int* numgroups);
//FMOD_RESULT F_API getGroup(int index, ChannelGroup** group);
//FMOD_RESULT F_API getParentGroup(ChannelGroup** group);
//
//// Information only functions.
//FMOD_RESULT F_API getName(char* name, int namelen);
//FMOD_RESULT F_API getNumChannels(int* numchannels);
//FMOD_RESULT F_API getChannel(int index, Channel** channel);
