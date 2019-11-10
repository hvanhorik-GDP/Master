#pragma once

#include "cObject_Common.h"
#include "cObject_ChannelControl.h"
#include "cObject_3d.h"
#include "cObject_Physics.h"
#include "AudioEngine/cAudio_System_FMOD.h"
#include "AudioEngine/cAudio_Channel_FMOD.h"
#include "AudioEngine/cAudio_Sound_FMOD.h"


#include <vector>

class cObject_Channel 
	: public cObject_Common							// Need common items
	, public cObject_ChannelControl					// Full channel control
	, public cObject_3d								// This is a 3d Object
	, public cObject_Physics						// and physics applies to it
{
public:
	// This structure matches the file, so that our life is
	//   simpler and happier, and we all get along.

	cObject_Channel();				// Get's filled in by physics

	virtual ~cObject_Channel();

	virtual void playSound(bool paused) final;



	virtual iObject* Clone(const std::string& newName) final;

	virtual void IntegrationStep(float deltaTime) final;

	// Recieve a message
	virtual bool RecieveMessage(const iMessage& message) final;

	// Recieve a message and reply
	virtual bool RecieveAndRespond(const iMessage& in, iMessage& reply) final;

	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const cObject_Channel& val);

public:
	cAudio_System_FMOD* m_system;
	cAudio_Channel_FMOD* m_channel;
	cAudio_Sound_FMOD* m_sound;
	cAudio_ChannelGroup_FMOD* m_channel_group;
	friend class cObjectManager_Channel;
};

