#pragma once

#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>
#include <string>
#include <boost/shared_ptr.hpp>


class XMLNodeBase
{
public:
	typedef  boost::shared_ptr<XMLNodeBase> spXMLNode;
	XMLNodeBase();
	XMLNodeBase(rapidxml::xml_node<>* node, const spXMLNode& parent, const std::string& name);
	virtual ~XMLNodeBase() {}
	virtual void Load(spXMLNode &me) = 0;
	bool isValid() const;
	bool hasParent() const;
	void Remove();
	void Remove(XMLNodeBase &child);

	rapidxml::xml_node<>* GetNode() const { return pNode; };
	void SetNode(rapidxml::xml_node<>* node) { pNode = node; };
	spXMLNode GetParent() const { return spParent; }
	void SetParent(const spXMLNode& parent) { spParent = parent; }
	const std::string& GetName() const { return sName; };
	void SetName(const std::string& name) { sName = name; };

protected:
	rapidxml::xml_node<>* pNode;
	spXMLNode spParent;
	std::string sName;
};

