#pragma once
#include <string>
#include <rapidxml/rapidxml.hpp>

#pragma comment(lib, "MessageManager.lib")

// INFO6044 - iMesssage is a part of the iMesageManager

class iMessage
{
public:
	iMessage() {}
	virtual ~iMessage() {}

	virtual const std::string& Reciever() const = 0;
	virtual const std::string& Sender() const = 0;

	virtual rapidxml::xml_node<>* GetNode() const = 0;

	// TODO - Hack for now until I implement XML based version
	virtual const std::string& GetMessageString() const = 0;
	virtual void SetMessageString(const std::string& in) = 0;
};

