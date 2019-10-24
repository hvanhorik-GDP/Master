#include "cObject_ChannelControl.h"

cObject_ChannelControl::cObject_ChannelControl(const std::string& type,
	const std::string& name,
	const std::string& asset_id,
	rapidxml::xml_node<>* node)
	: cObject_Common(type, name, asset_id, node)
{
}

cObject_ChannelControl::~cObject_ChannelControl()
{
}

// For debugging purposes - dumps the contents in human readable form
std::ostream& operator<<(std::ostream& stream, const cObject_ChannelControl& val)
{
	stream << "std::ostream& operator<<(std::ostream& stream, const cObject_ChannelControl& val)" << "Not Implemented" << std::endl;
	return stream;
}
