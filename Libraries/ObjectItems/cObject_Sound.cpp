#include "cObject_Sound.h"

cObject_Sound::cObject_Sound(const std::string& type,
	const std::string& name,
	const std::string& asset_id,
	rapidxml::xml_node<>* node)
	: cObject_Common(type, name, asset_id, node)
{

}
cObject_Sound::~cObject_Sound()
{
}

// For debugging purposes - dumps the contents in human readable form
std::ostream& operator<<(std::ostream& stream, const cObject_Sound& val)
{
	stream << "std::ostream& operator<<(std::ostream& stream, const cObject_Sound& val)" << "Not Implemented" << std::endl;
	return stream;
}
