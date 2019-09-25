#include "XMLNodeBase.h"


XMLNodeBase::XMLNodeBase()
	: pNode(NULL)
{
}

XMLNodeBase::XMLNodeBase(rapidxml::xml_node<>* node)
	: pNode(node)
{
}

bool XMLNodeBase::isValid() const 
{ 
	return (pNode) ? true : false; 
};

bool XMLNodeBase::hasParent() const
{
	assert(pNode);
	return (pNode) ? (pNode->parent() != NULL) : false;
} 

std::string XMLNodeBase::GetValue() const
{
	return (pNode) ? pNode->value() : std::string();
}

void XMLNodeBase::SetValue(const std::string& value)
{
	assert(pNode);
	if (pNode)
	{
		auto doc = pNode->document();
		auto newstring = doc->allocate_string(value.c_str());	// Must let rapidxml hold the strings
		pNode->value(newstring);
	}
}


rapidxml::xml_node<>* XMLNodeBase::GetParent() const
{
	assert(pNode);
	return (pNode) ? pNode->parent() : NULL;
}

void XMLNodeBase::Remove()
{
	assert(false);	// Todo
	assert(pNode);
	if (isValid())
	{
		auto parent = GetParent();
		assert(parent);
		// Remove this node from the parent and invalidate this node

//		if (parent
	}
}
