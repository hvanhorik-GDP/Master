#include "cObject_Common.h"
#include <sstream>
#include <algorithm>

cObject_Common::cObject_Common()
	: m_type()
	, m_name()
	, m_assetID()
	, m_node(NULL)
{
}

cObject_Common::cObject_Common(	const std::string &type,
								const std::string &name,
								const std::string &asset_id,
								rapidxml::xml_node<>* node)
	: m_type(type)
	, m_name(name)
	, m_assetID(asset_id)
	, m_node(node)
{
}

cObject_Common::~cObject_Common()
{

}

const std::string& cObject_Common::GetAssetID() const
{
	return m_assetID;
}

const std::string& cObject_Common::GetName() const
{
	return m_name;
}

const std::string& cObject_Common::GetType() const
{
	return m_type;
}

rapidxml::xml_node<>* cObject_Common::GetNode() const
{
	return m_node;
}

void cObject_Common::SetNode(rapidxml::xml_node<>* in)
{
	m_node = in;
}

bool cObject_Common::IsXMLValid() const
{
	return (m_node);
}

iItem* cObject_Common::GetItem() const
{
	return m_Item;
}

iObject* cObject_Common::GetParentObject() const
{
	return m_ParentObject;
}

void cObject_Common::SetParentObject(iObject* in)
{
	m_ParentObject = in;
}

// For debugging purposes - dumps the contents in human readable form
std::ostream& operator<<(std::ostream& stream, const cObject_Common& val)
{
	stream << "std::ostream& operator<<(std::ostream& stream, const cObject_Common& val)" << "Not Implemented" << std::endl;
	return stream;
}

// from iMessageInterface
// Everyone has a universal ID
const std::string& cObject_Common::GetMyUID() const
{
	// UID is our name
	return m_name;
}

// Recieve a message
bool cObject_Common::RecieveMessage(const iMessage& message)
{
	assert(false);				//  TODO - Implement
	return false;
}

// Recieve a message and reply
bool cObject_Common::RecieveAndRespond(const iMessage& in, iMessage& reply)
{
	assert(false);				// TODO - implement
	return false;
}
