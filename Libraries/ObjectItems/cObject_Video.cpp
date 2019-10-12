#include "cObject_Video.h"

cObject_Video::cObject_Video(	const std::string &type,
								const std::string &name,
								const std::string &asset_id,
								rapidxml::xml_node<>* node)
	: cObject_Common(type, name, asset_id, node)
{

}
cObject_Video::~cObject_Video()
{
}

// For debugging purposes - dumps the contents in human readable form
std::ostream& operator<<(std::ostream& stream, const cObject_Video& val)
{
	stream << "std::ostream& operator<<(std::ostream& stream, const cObject_Video& val)" << "Not Implemented" << std::endl;
	return stream;
}
