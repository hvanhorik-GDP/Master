#include "cObject_Channel.h"

cObject_Channel::cObject_Channel(const std::string& type,
	const std::string& name,
	const std::string& asset_id,
	rapidxml::xml_node<>* node)
	: cObject_ChannelControl(type, name, asset_id, node)
{

}
cObject_Channel::~cObject_Channel()
{
}

// For debugging purposes - dumps the contents in human readable form
std::ostream& operator<<(std::ostream& stream, const cObject_Channel& val)
{
	stream << "std::ostream& operator<<(std::ostream& stream, const cObject_Channel& val)" << "Not Implemented" << std::endl;
	return stream;
}
