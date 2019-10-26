#include "cObject_Audio.h"

cObject_Audio::cObject_Audio(const std::string& type,
	const std::string& name,
	const std::string& asset_id,
	rapidxml::xml_node<>* node)
	: cObject_Common()
{
	// Hack for now
	LoadCommon(type, name, asset_id, node);
}

cObject_Audio::~cObject_Audio()
{
}


iObject* cObject_Audio::Clone(const std::string& newName)
{
	// Copy everything and change the name
	cObject_Audio* ret =
		new cObject_Audio(*this);
	ret->m_name = newName;
	ret->m_node = NULL;			// No XML so it won't update
	return ret;
}

// For debugging purposes - dumps the contents in human readable form
std::ostream& operator<<(std::ostream& stream, const cObject_Audio& val)
{
	stream << "std::ostream& operator<<(std::ostream& stream, const cObject_Audio& val)" << "Not Implemented" << std::endl;
	return stream;
}

//TODO - for now just implement them here.
// need to implement them in every class of iObject
// Recieve a message
bool cObject_Audio::RecieveMessage(const iMessage& message)
{
	return false;
}

// Recieve a message and reply
bool cObject_Audio::RecieveAndRespond(const iMessage& in, iMessage& reply)
{
	return false;

}
