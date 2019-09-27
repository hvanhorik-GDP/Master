#include "XMLAttribute.h"
#include <ostream>

XMLAttribute::XMLAttribute()
{
}

XMLAttribute::XMLAttribute(rapidxml::xml_node<>* node)
	: m_node(node)
{
}

bool XMLAttribute::hasNode() const
{
	return (m_node);
}

std::string XMLAttribute::GetValue() const
{
	if (!hasNode())
		return std::string();
	auto attribute = m_node->first_attribute(GetName().c_str());
	return (attribute) ? attribute->value() : std::string();
}


std::ostream& operator << (std::ostream& out, const XMLAttribute& attribute)
{
	if (attribute.isValid())
	{
		out << attribute.GetName() << " = \"" << attribute.GetValue() << "\" ";
	}
	return out;
}

rapidxml::xml_node<>* XMLAttribute::GetNode() const
{
	return m_node;
}
