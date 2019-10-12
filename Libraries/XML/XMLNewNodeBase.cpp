#include "XMLNewNodeBase.h"
#include <ostream>


XMLNewNodeBase::XMLNewNodeBase(rapidxml::xml_node<>* node)
	: m_node(node)
{
	assert(m_node);
}

XMLNewNodeBase::XMLNewNodeBase()
	: m_node(NULL)
{
}


std::string XMLNewNodeBase::GetNodeName() const
{
	assert(m_node != NULL);
	return (m_node) ? m_node->name() : std::string();
}

bool XMLNewNodeBase::hasNode() const
{
	return (m_node);
}

rapidxml::xml_node<>* XMLNewNodeBase::GetNode() const 
{ 
	assert(m_node != NULL);
	return (m_node);
};

bool XMLNewNodeBase::hasParent() const
{
	assert(m_node != NULL);
	return (m_node->parent());
} 

std::string XMLNewNodeBase::GetValue() const
{
	assert(m_node != NULL);
	return (m_node) ? m_node->value() : std::string();
}


rapidxml::xml_node<>* XMLNewNodeBase::GetParent() const
{
	assert(m_node != NULL);
	return (m_node->parent());
}

rapidxml::xml_document<>* XMLNewNodeBase::GetDocument() const
{
	assert(m_node != NULL);
	return (m_node) ? m_node->document() : NULL;
}

void XMLNewNodeBase::SetValue(const std::string& value)
{
	assert(m_node != NULL);
	if (m_node)
	{
		if (m_node)
		{
			auto doc = GetDocument();
			auto newstring = doc->allocate_string(value.c_str());	// Must let rapidxml hold the strings
			m_node->value(newstring);
		}
		else
		{
			Add(value);
		}
	}
}

std::ostream& operator << (std::ostream& out, const XMLNewNodeBase& node)
{
	if (node.isValid())
	{
		out << "<" << node.GetNodeName() << ">" << node.GetValue() << "</" << node.GetNodeName() << ">";
	}
	return out;
}
//
//void XMLNewNodeBase::SetParent(rapidxml::xml_node<>* parent)
//{
//	m_parent = parent;
//}

rapidxml::xml_node<>* XMLNewNodeBase::Insert(const std::string& name, const std::string& value)
{
	// Use existing node if it exists and just overwrite it's values
	// We need to allocate the memory out of the document pool
	auto document = GetDocument();
	assert(document != NULL);
	char* newValue = NULL;
	if (value.size() > 0)
		newValue = document->allocate_string(value.c_str());	// Must let rapidxml hold the strings
	auto newName = document->allocate_string(name.c_str());	// Must let rapidxml hold the strings
	rapidxml::xml_node<>* node = document->allocate_node(rapidxml::node_element, newName, newValue);

	m_node->append_node(node);								// Put at the end
	return node;
}


void XMLNewNodeBase::Add(const std::string& value, bool insert)
{
	assert(false);			//TODO  implement
	assert(m_node != NULL);
	if (m_node && !insert)
	{
		SetValue(value);
	}
	else
	{
		// Use existing node if it exists and just overwrite it's values
		// We need to allocate the memory out of the document pool
		auto document = GetDocument();
		assert(document != NULL);
		auto newValue = document->allocate_string(value.c_str());	// Must let rapidxml hold the strings
		auto newName = document->allocate_string(GetName().c_str());	// Must let rapidxml hold the strings
		rapidxml::xml_node<> *node = document->allocate_node( rapidxml::node_element, newName, newValue);

		assert(false);
		// this is wrong. We need the parent
//		m_parent->append_node(node);								// Put at the end
	}
}


void XMLNewNodeBase::Remove()
{
	assert(false);	// Todo
	assert(m_node != NULL);
	if (isValid())
	{
		auto parent = GetParent();
		assert(parent != NULL);
	}
}

namespace xmlindent
{
	std::ostream& operator<<(std::ostream& stream, const xmlindent::indent& val)
	{
		for (int i = 0; i < val.level; i++) {
			stream << " ";
		}
		return stream;
	}

}