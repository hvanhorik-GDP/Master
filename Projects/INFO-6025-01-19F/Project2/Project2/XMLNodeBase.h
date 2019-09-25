#pragma once

#include <rapidxml/rapidxml.hpp>
#include <string>
#include <vector>

class XMLNodeBase
{
public:
	XMLNodeBase();
	XMLNodeBase(rapidxml::xml_node<>* node);
	virtual ~XMLNodeBase() {}
	virtual const std::string& GetName() const = 0;
	bool isValid() const;
	bool hasParent() const;
	void Remove();
	std::string GetValue() const;
	void SetValue(const std::string &value);

protected:
	rapidxml::xml_node<>* GetNode() const { return pNode; };
	void SetNode(rapidxml::xml_node<>* node) { pNode = node; };
	rapidxml::xml_node<>* GetParent() const;
private:
	rapidxml::xml_node<>* pNode;
};

