#include "cObject_Font.h"

cObject_Font::cObject_Font(const std::string& type,
	const std::string& name,
	const std::string& asset_id,
	rapidxml::xml_node<>* node)
	: cObject_Common(type, name, asset_id, node)
{

}
cObject_Font::~cObject_Font()
{
}

// For debugging purposes - dumps the contents in human readable form
std::ostream& operator<<(std::ostream& stream, const cObject_Font& val)
{
	stream << "std::ostream& operator<<(std::ostream& stream, const cObject_Font& val)" << "Not Implemented" << std::endl;
	return stream;
}
