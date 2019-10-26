#include "cObject_Channel.h"

cObject_Channel::cObject_Channel(const std::string& type,
	const std::string& name,
	const std::string& asset_id,
	rapidxml::xml_node<>* node)
	: cObject_Common()							// Need common items
	, cObject_ChannelControl()					// Full channel control
	, cObject_3d()								// This is a 3d Object
	, cObject_Physics()							// and physics applies to it
{
}

cObject_Channel::~cObject_Channel()
{
}

iObject* cObject_Channel::Clone(const std::string& newName)
{
	// Copy everything and change the name
	cObject_Channel* ret =
		new cObject_Channel(*this);
	ret->m_name = newName;
	ret->m_node = NULL;			// No XML so it won't update
	return ret;
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
