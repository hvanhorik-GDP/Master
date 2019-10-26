#include "cObject_ChannelGroup.h"

cObject_ChannelGroup::cObject_ChannelGroup(const std::string& type,
	const std::string& name,
	const std::string& asset_id,
	rapidxml::xml_node<>* node)
	: cObject_Common()							// Need common items
	, cObject_ChannelControl()					// Full channel control
	, cObject_3d()								// This is a 3d Object
	, cObject_Physics()							// and physics applies to it
	, cObject_Alias()							// This is a grouping
{
	LoadCommon(type, name, asset_id, node);
}

cObject_ChannelGroup::~cObject_ChannelGroup()
{
}


iObject* cObject_ChannelGroup::Clone(const std::string& newName)
{
	// Copy everything and change the name
	cObject_ChannelGroup* ret =
		new cObject_ChannelGroup(*this);
	ret->m_name = newName;
	ret->m_node = NULL;			// No XML so it won't update
	return ret;
}


void cObject_ChannelGroup::IntegrationStep(float deltaTime)
{
	assert(false);
}

// For debugging purposes - dumps the contents in human readable form
std::ostream& operator<<(std::ostream& stream, const cObject_ChannelGroup& val)
{
	stream << "std::ostream& operator<<(std::ostream& stream, const cObject_ChannelGroup& val)" << "Not Implemented" << std::endl;
	return stream;
}


//TODO - for now just implement them here.
// need to implement them in every class of iObject
// Recieve a message
bool cObject_ChannelGroup::RecieveMessage(const iMessage& message)
{
	return false;
}

// Recieve a message and reply
bool cObject_ChannelGroup::RecieveAndRespond(const iMessage& in, iMessage& reply)
{
	return false;

}
