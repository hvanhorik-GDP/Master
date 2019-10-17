#include "cMessage_XML.h"
#include <rapidxml/rapidxml_ext.hpp>

cMessage_XML::cMessage_XML(const std::string& reciever, const std::string& sender)
	: m_reciever(reciever)
	, m_sender(sender)
{
}

cMessage_XML::~cMessage_XML()
{
}

const std::string& cMessage_XML::Reciever() const
{
	return m_reciever;
}

const std::string& cMessage_XML::Sender() const 
{
	return m_sender;
}

rapidxml::xml_node<>* cMessage_XML::GetNode() const
{
	return m_document.first_node();
}

std::ostream& operator<<(std::ostream& stream, const cMessage_XML& val)
{
	stream << *val.GetNode();
	return stream;
}

// TODO - Hack for now until I implement XML based version
const std::string& cMessage_XML::GetMessageString() const
{
	return m_message;
}

void cMessage_XML::SetMessageString(const std::string& in)
{
	m_message = in;
}
