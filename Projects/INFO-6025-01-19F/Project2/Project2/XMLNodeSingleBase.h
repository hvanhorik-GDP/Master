#pragma once
#include "XMLNodeBase.h"

class XMLNodeSingleBase :
	public XMLNodeBase
{
public:
	XMLNodeSingleBase() {};
	virtual ~XMLNodeSingleBase() {};
	XMLNodeSingleBase(spXMLNode &parent, const std::string& name);
private:
	virtual void Load(spXMLNode& parent) { assert(false); };
};

