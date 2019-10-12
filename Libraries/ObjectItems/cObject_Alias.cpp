#include "cObject_Alias.h"

cObject_Alias::cObject_Alias(	const std::string &type,
								const std::string &name,
								const std::string &asset_id,
								rapidxml::xml_node<>* node)
	: cObject_Common(type, name, asset_id, node)
{

}
cObject_Alias::~cObject_Alias()
{
}

// For debugging purposes - dumps the contents in human readable form
std::ostream& operator<<(std::ostream& stream, const cObject_Alias& val)
{
	stream << "std::ostream& operator<<(std::ostream& stream, const cObject_Alias& val)" << "Not Implemented" << std::endl;
	return stream;
}
