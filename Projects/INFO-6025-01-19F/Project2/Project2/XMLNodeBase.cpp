#include "XMLNodeBase.h"


XMLNodeBase::XMLNodeBase()
	: pNode(NULL)
	, spParent()
	, sName()
{
}

XMLNodeBase::XMLNodeBase(rapidxml::xml_node<>* node, const spXMLNode& parent, const std::string& name)
	: pNode(node)
	, spParent(parent)
	, sName(name)
{
}

bool XMLNodeBase::isValid() const 
{ 
	return (pNode) ? true : false; 
};

bool XMLNodeBase::hasParent() const
{
	return (spParent) ? true : false;
} 

void XMLNodeBase::Remove()
{
	if (isValid())
	{
		auto parent = GetParent();
		if (spParent->isValid())
			spParent->Remove(*this);
	}
}

void XMLNodeBase::Remove(XMLNodeBase& child)
{
	if (isValid())
	{
		if (child.isValid())
		{

		}
	}
}
