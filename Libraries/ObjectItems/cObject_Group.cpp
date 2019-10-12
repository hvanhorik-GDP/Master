#include "cObject_Group.h"

cObject_Group::cObject_Group(const std::string& type,
	const std::string& name,
	const std::string& asset_id,
	rapidxml::xml_node<>* node)
	: cObject_Common(type, name, asset_id, node)
{

}
cObject_Group::~cObject_Group()
{
}

// For debugging purposes - dumps the contents in human readable form
std::ostream& operator<<(std::ostream& stream, const cObject_Group& val)
{
	stream << "std::ostream& operator<<(std::ostream& stream, const cObject_Group& val)" << "Not Implemented" << std::endl;
	return stream;
}
