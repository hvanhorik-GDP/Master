#include "cObject_Window.h"

cObject_Window::cObject_Window(const std::string& type,
	const std::string& name,
	const std::string& asset_id,
	rapidxml::xml_node<>* node)
	: cObject_Common(type, name, asset_id, node)
{

}
cObject_Window::~cObject_Window()
{
}

// For debugging purposes - dumps the contents in human readable form
std::ostream& operator<<(std::ostream& stream, const cObject_Window& val)
{
	stream << "std::ostream& operator<<(std::ostream& stream, const cObject_Window& val)" << "Not Implemented" << std::endl;
	return stream;
}
