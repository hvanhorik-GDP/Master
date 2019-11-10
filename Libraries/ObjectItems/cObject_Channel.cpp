#include "cObject_Channel.h"
#include "AudioEngine/cAudio_System.h"
#include "AudioEngine/cAudio_System_FMOD.h"
#include "AssetItems/cItem_Audio.h"
#include <iostream>

cObject_Channel::cObject_Channel()
	: cObject_Common()							// Need common items
	, cObject_ChannelControl()					// Full channel control
	, cObject_3d()								// This is a 3d Object
	, cObject_Physics()							// and physics applies to it
{
	cAudio_System audio;
	iAudio_System* impl = audio.Get_impl();
	m_system = dynamic_cast<cAudio_System_FMOD*>(impl);
	m_sound = new cAudio_Sound_FMOD();
	m_channel = new cAudio_Channel_FMOD();
}

cObject_Channel::~cObject_Channel()
{
	delete m_sound;
	delete m_channel;
}

iObject* cObject_Channel::Clone(const std::string& newName)
{
	// Copy everything and change the name
	cObject_Channel* ret =
		new cObject_Channel(*this);
	ret->m_name = newName;
	ret->m_node = NULL;			// No XML so it won't update
	ret->m_channel = new cAudio_Channel_FMOD();
	ret->m_sound = new cAudio_Sound_FMOD();
	return ret;
}

void cObject_Channel::playSound( bool paused )
{
	assert(m_channel);
	assert(m_system);
	assert(m_sound);
	cItem_Audio* item = dynamic_cast<cItem_Audio*>(m_Item);
	assert(item);
	FMOD_MODE mode = FMOD_CREATESTREAM;

	m_system->CreateSound(*m_sound, item->m_fullPath, mode);
	m_system->PlaySound(*m_sound, m_channel_group, paused, *m_channel);
	std::cout << "Playing " << m_sound->m_sound << " channel ID: " << m_channel->m_channel << std::endl;
}

void cObject_Channel::IntegrationStep(float deltaTime)
{
	assert(false);
}

// For debugging purposes - dumps the contents in human readable form
std::ostream& operator<<(std::ostream& stream, const cObject_Channel& val)
{
	stream << "std::ostream& operator<<(std::ostream& stream, const cObject_Channel& val)" << "Not Implemented" << std::endl;
	return stream;
}


//TODO - for now just implement them here.
// need to implement them in every class of iObject
// Recieve a message
bool cObject_Channel::RecieveMessage(const iMessage& message)
{
	return false;
}

// Recieve a message and reply
bool cObject_Channel::RecieveAndRespond(const iMessage& in, iMessage& reply)
{
	return false;

}
