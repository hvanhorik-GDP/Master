#include "cObject_Image.h"

cObject_Image::cObject_Image(const std::string& type,
	const std::string& name,
	const std::string& asset_id,
	rapidxml::xml_node<>* node)
	: cObject_Common(type, name, asset_id, node)
{

}
cObject_Image::~cObject_Image()
{
}

// For debugging purposes - dumps the contents in human readable form
std::ostream& operator<<(std::ostream& stream, const cObject_Image& val)
{
	stream << "std::ostream& operator<<(std::ostream& stream, const cObject_Image& val)" << "Not Implemented" << std::endl;
	return stream;
}
