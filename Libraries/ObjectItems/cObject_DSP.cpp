#include "cObject_DSP.h"

cObject_DSP::cObject_DSP(const std::string& type,
	const std::string& name,
	const std::string& asset_id,
	rapidxml::xml_node<>* node)
	: cObject_Common(type, name, asset_id, node)
{

}
cObject_DSP::~cObject_DSP()
{
}

// For debugging purposes - dumps the contents in human readable form
std::ostream& operator<<(std::ostream& stream, const cObject_DSP& val)
{
	stream << "std::ostream& operator<<(std::ostream& stream, const cObject_DSP& val)" << "Not Implemented" << std::endl;
	return stream;
}
