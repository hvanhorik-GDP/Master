#include "cObject_Texture.h"

cObject_Texture::cObject_Texture(const std::string& type,
	const std::string& name,
	const std::string& asset_id,
	rapidxml::xml_node<>* node)
	: cObject_Common(type, name, asset_id, node)
{

}
cObject_Texture::~cObject_Texture()
{
}

// For debugging purposes - dumps the contents in human readable form
std::ostream& operator<<(std::ostream& stream, const cObject_Texture& val)
{
	stream << "std::ostream& operator<<(std::ostream& stream, const cObject_Texture& val)" << "Not Implemented" << std::endl;
	return stream;
}
