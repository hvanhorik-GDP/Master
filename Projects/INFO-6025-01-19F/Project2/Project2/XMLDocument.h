#pragma once

#include "XMLNodeBase.h"
#include <rapidxml/rapidxml.hpp>
#include <string>
#include <vector>

class XMLDocument
{
public:
	XMLDocument() {};
	~XMLDocument() {};
	virtual const std::string& GetName() const { return std::string(); };
	void Read(const std::string& inFile);
	void Write(const std::string& outFile) const;
	rapidxml::xml_node<>* GetRoot(const std::string &root) const;
	rapidxml::xml_node<>* GetDocument();

private:
	rapidxml::xml_document<> m_document;
	std::vector<char> m_buffer;				// Need to keep read buffer perm
};

