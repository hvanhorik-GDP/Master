#include "cObject_ChannelGroup.h"

cObject_ChannelGroup::cObject_ChannelGroup(const std::string& type,
	const std::string& name,
	const std::string& asset_id,
	rapidxml::xml_node<>* node)
	: cObject_ChannelControl(type, name, asset_id, node)
{

}
cObject_ChannelGroup::~cObject_ChannelGroup()
{
}

// For debugging purposes - dumps the contents in human readable form
std::ostream& operator<<(std::ostream& stream, const cObject_ChannelGroup& val)
{
	stream << "std::ostream& operator<<(std::ostream& stream, const cObject_ChannelGroup& val)" << "Not Implemented" << std::endl;
	return stream;
}
