#include "cItem_Shader.h"

cItem_Shader::cItem_Shader(std::string id,
	std::string path,
	rapidxml::xml_node<>* parent,
	std::size_t index)
	: cItem_Common(id, path, parent, index)
{

}
cItem_Shader::~cItem_Shader()
{
}

// For debugging purposes - dumps the contents in human readable form
std::ostream& operator<<(std::ostream& stream, const cItem_Shader& val)
{
	stream << "std::ostream& operator<<(std::ostream& stream, const cItem_Shader& val)" << "Not Implemented" << std::endl;
	return stream;
}
