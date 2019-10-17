#pragma once

#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_ext.hpp>
#include <string>
#include <vector>
#include <ostream>

#pragma comment (lib, "XML.lib")


namespace xmlindent
{
	class indent {
	public:
		indent(int level) : level(level) {}
		friend std::ostream& operator<<(std::ostream& stream, const indent& val);
		int level;
	};
}

class XMLNewNodeBase
{
public:

public:
	XMLNewNodeBase();
	XMLNewNodeBase(rapidxml::xml_node<>* node);
	virtual ~XMLNewNodeBase() {}

	// Get the actual recorded node name
	std::string GetNodeName() const;

	// Validate the node
	bool isValid() const { return (m_node);  }
	bool hasNode() const;

	// Add and Remove a node
	void Remove();
	void Add(const std::string& value = std::string(), bool insert = true);
	rapidxml::xml_node<>* Insert(const std::string& name, const std::string& value);

	// Get & Set Values of a node
	std::string GetValue() const;
	void SetValue(const std::string &value);

	friend std::ostream& operator << (std::ostream& out, const XMLNewNodeBase& node);
	virtual rapidxml::xml_node<>* GetNode() const;
	rapidxml::xml_node<>* GetParent() const;

protected:
	// virtual function for derived classes to specify their node name
	virtual const std::string& GetName() const = 0;
	bool hasParent() const;
	rapidxml::xml_document<>* GetDocument() const;
//	void SetParent(rapidxml::xml_node<>* parent);
private:
	rapidxml::xml_node<>* m_node;

};

