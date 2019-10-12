#include "cObject_World.h"

cObject_World::cObject_World(const std::string& type,
	const std::string& name,
	const std::string& asset_id,
	rapidxml::xml_node<>* node)
	: cObject_Group(type, name, asset_id, node)
{

}
cObject_World::~cObject_World()
{
}

// For debugging purposes - dumps the contents in human readable form
std::ostream& operator<<(std::ostream& stream, const cObject_World& val)
{
	stream << "std::ostream& operator<<(std::ostream& stream, const cObject_World& val)" << "Not Implemented" << std::endl;
	return stream;
}
