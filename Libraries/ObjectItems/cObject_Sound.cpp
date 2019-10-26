#include "cObject_Sound.h"

cObject_Sound::cObject_Sound(const std::string& type,
	const std::string& name,
	const std::string& asset_id,
	rapidxml::xml_node<>* node)
	: cObject_Common()
{
	// Hack for now
	LoadCommon(type, name, asset_id, node);

}

cObject_Sound::~cObject_Sound()
{
}

iObject* cObject_Sound::Clone(const std::string& newName)
{
	// Copy everything and change the name
	cObject_Sound* ret =
		new cObject_Sound(*this);
	ret->m_name = newName;
	ret->m_node = NULL;			// No XML so it won't update
	return ret;
}


// For debugging purposes - dumps the contents in human readable form
std::ostream& operator<<(std::ostream& stream, const cObject_Sound& val)
{
	stream << "std::ostream& operator<<(std::ostream& stream, const cObject_Sound& val)" << "Not Implemented" << std::endl;
	return stream;
}

//TODO - for now just implement them here.
// need to implement them in every class of iObject
// Recieve a message
bool cObject_Sound::RecieveMessage(const iMessage& message)
{
	return false;
}

// Recieve a message and reply
bool cObject_Sound::RecieveAndRespond(const iMessage& in, iMessage& reply)
{
	return false;

}
