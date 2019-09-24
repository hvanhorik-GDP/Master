#include "XMLNodeSingleBase.h"

XMLNodeSingleBase::XMLNodeSingleBase(spXMLNode& parent, const std::string& name)
	: XMLNodeBase()
{
	if (parent->isValid())
	{
		rapidxml::xml_node<>* node = parent->GetNode()->first_node(name.c_str());
		if (node)
		{
			SetNode(node);
			SetParent(parent);
			SetName(name);
		}
	}
}