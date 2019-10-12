#include "cObject_Audio.h"

cObject_Audio::cObject_Audio(const std::string& type,
	const std::string& name,
	const std::string& asset_id,
	rapidxml::xml_node<>* node)
	: cObject_Common(type, name, asset_id, node)
{

}
cObject_Audio::~cObject_Audio()
{
}

// For debugging purposes - dumps the contents in human readable form
std::ostream& operator<<(std::ostream& stream, const cObject_Audio& val)
{
	stream << "std::ostream& operator<<(std::ostream& stream, const cObject_Audio& val)" << "Not Implemented" << std::endl;
	return stream;
}
