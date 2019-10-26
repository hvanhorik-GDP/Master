#include "cObject_Camera.h"

cObject_Camera::cObject_Camera(const std::string& type,
	const std::string& name,
	const std::string& asset_id,
	rapidxml::xml_node<>* node)
	: cObject_Common()
{
	// Hack for now
	LoadCommon(type, name, asset_id, node);
}

cObject_Camera::~cObject_Camera()
{
}


iObject* cObject_Camera::Clone(const std::string& newName)
{
	// Copy everything and change the name
	cObject_Camera* ret =
		new cObject_Camera(*this);
	ret->m_name = newName;
	ret->m_node = NULL;			// No XML so it won't update
	return ret;
}

// For debugging purposes - dumps the contents in human readable form
std::ostream& operator<<(std::ostream& stream, const cObject_Camera& val)
{
	stream << "std::ostream& operator<<(std::ostream& stream, const cObject_Camera& val)" << "Not Implemented" << std::endl;
	return stream;
}


//TODO - for now just implement them here.
// need to implement them in every class of iObject
// Recieve a message
bool cObject_Camera::RecieveMessage(const iMessage& message)
{
	return false;		// TODO
}

// Recieve a message and reply
bool cObject_Camera::RecieveAndRespond(const iMessage& in, iMessage& reply)
{
	return false;		// TODO
}