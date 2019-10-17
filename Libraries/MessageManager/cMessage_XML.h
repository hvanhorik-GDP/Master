#pragma once
#include "iMessage.h"
#include<rapidxml/rapidxml.hpp>

class cMessage_XML : public iMessage
{
public:
	cMessage_XML(const std::string& reciever, const std::string& sender);
	virtual ~cMessage_XML();

	virtual const std::string& Reciever() const;
	virtual const std::string& Sender() const;

	virtual rapidxml::xml_node<>* GetNode() const;

	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const cMessage_XML& val);

	// TODO - Hack for now until I implement XML based version
	virtual const std::string& GetMessageString() const;
	virtual void SetMessageString(const std::string& in);

private:
	cMessage_XML();
	std::string m_sender;
	std::string m_reciever;
	rapidxml::xml_document<> m_document;
	// TODO - Hack for now until I implement XML based version
	std::string m_message;
};
