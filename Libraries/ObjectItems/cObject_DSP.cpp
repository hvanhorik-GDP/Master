#include "cObject_DSP.h"

cObject_DSP::cObject_DSP(const std::string& type,
	const std::string& name,
	const std::string& asset_id,
	rapidxml::xml_node<>* node)
	: cObject_Common()
{
	// Hack for now
	LoadCommon(type, name, asset_id, node);
}

cObject_DSP::~cObject_DSP()
{
}

iObject* cObject_DSP::Clone(const std::string& newName)
{
	// Copy everything and change the name
	cObject_DSP* ret =
		new cObject_DSP(*this);
	ret->m_name = newName;
	ret->m_node = NULL;			// No XML so it won't update
	return ret;
}


// For debugging purposes - dumps the contents in human readable form
std::ostream& operator<<(std::ostream& stream, const cObject_DSP& val)
{
	stream << "std::ostream& operator<<(std::ostream& stream, const cObject_DSP& val)" << "Not Implemented" << std::endl;
	return stream;
}

//TODO - for now just implement them here.
// need to implement them in every class of iObject
// Recieve a message
bool cObject_DSP::RecieveMessage(const iMessage& message)
{
	return false;
}

// Recieve a message and reply
bool cObject_DSP::RecieveAndRespond(const iMessage& in, iMessage& reply)
{
	return false;

}
