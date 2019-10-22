#include "cObject_Camera.h"

cObject_Camera::cObject_Camera(const std::string& type,
	const std::string& name,
	const std::string& asset_id,
	rapidxml::xml_node<>* node)
	: cObject_Common(type, name, asset_id, node)
{

}
cObject_Camera::~cObject_Camera()
{
}

// For debugging purposes - dumps the contents in human readable form
std::ostream& operator<<(std::ostream& stream, const cObject_Camera& val)
{
	stream << "std::ostream& operator<<(std::ostream& stream, const cObject_Camera& val)" << "Not Implemented" << std::endl;
	return stream;
}
