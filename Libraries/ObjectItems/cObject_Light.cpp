#include "cObject_Light.h"

cObject_Light::cObject_Light(const std::string& type,
	const std::string& name,
	const std::string& asset_id,
	rapidxml::xml_node<>* node)
	: cObject_Common(type, name, asset_id, node)
{

}
cObject_Light::~cObject_Light()
{
}

// For debugging purposes - dumps the contents in human readable form
std::ostream& operator<<(std::ostream& stream, const cObject_Light& val)
{
	stream << "std::ostream& operator<<(std::ostream& stream, const cObject_Light& val)" << "Not Implemented" << std::endl;
	return stream;
}
