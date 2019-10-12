#include "cObject_Physics.h"

cObject_Physics::cObject_Physics(const std::string& type,
	const std::string& name,
	const std::string& asset_id,
	rapidxml::xml_node<>* node)
	: cObject_Common(type, name, asset_id, node)
{

}
cObject_Physics::~cObject_Physics()
{
}

// For debugging purposes - dumps the contents in human readable form
std::ostream& operator<<(std::ostream& stream, const cObject_Physics& val)
{
	stream << "std::ostream& operator<<(std::ostream& stream, const cObject_Physics& val)" << "Not Implemented" << std::endl;
	return stream;
}
