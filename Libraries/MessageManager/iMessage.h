#pragma once
#include <string>
#include <rapidxml/rapidxml.hpp>

#pragma comment(lib, "MessageManager.lib")

class iMessage
{
public:
	iMessage() {}
	virtual ~iMessage() {}

	virtual const std::string& Reciever() const = 0;
	virtual const std::string& Sender() const = 0;

	virtual rapidxml::xml_node<>* GetNode() const = 0;
};

