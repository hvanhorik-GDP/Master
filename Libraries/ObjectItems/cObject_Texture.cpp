#include "cObject_Texture.h"

cObject_Texture::cObject_Texture(const std::string& type,
	const std::string& name,
	const std::string& asset_id,
	rapidxml::xml_node<>* node)
	: cObject_Common()
{
	// Hack for now
	LoadCommon(type, name, asset_id, node);
}

cObject_Texture::~cObject_Texture()
{
}


iObject* cObject_Texture::Clone(const std::string& newName)
{
	// Copy everything and change the name
	cObject_Texture* ret =
		new cObject_Texture(*this);
	ret->m_name = newName;
	ret->m_node = NULL;			// No XML so it won't update
	return ret;
}

// For debugging purposes - dumps the contents in human readable form
std::ostream& operator<<(std::ostream& stream, const cObject_Texture& val)
{
	stream << "std::ostream& operator<<(std::ostream& stream, const cObject_Texture& val)" << "Not Implemented" << std::endl;
	return stream;
}

// TODO - for now just implement them here.
// need to implement them in every class of iObject
// Recieve a message
bool cObject_Texture::RecieveMessage(const iMessage & message)
{
	return false;
}

// Recieve a message and reply
bool cObject_Texture::RecieveAndRespond(const iMessage & in, iMessage & reply)
{
	return false;

}
