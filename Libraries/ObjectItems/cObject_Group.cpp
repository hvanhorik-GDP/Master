#include "cObject_Group.h"
#include "MessageManager/iMessage.h"
#include "MessageManager/cMessageManager.h"
#include "Utilities/cFormat.h"
#include <iostream>


cObject_Group::cObject_Group(const std::string& type,
	const std::string& name,
	const std::string& asset_id,
	rapidxml::xml_node<>* node)
	: cObject_Common(type, name, asset_id, node)
{
	// Global registry of myself that I may recieve messages
	cMessageManager().Register(name, this);
}

cObject_Group::~cObject_Group()
{
}

void cObject_Group::IntegrationStep(float deltaTime)
{
}

void cObject_Group::AddChildObject(iObject* child)
{
	m_mapObjects[child->GetName()] = child;
}

cObject_Group::mapObjectsInGroup& cObject_Group::GetObjectsInGroup()
{
	return m_mapObjects;
}

// For debugging purposes - dumps the contents in human readable form
std::ostream& operator<<(std::ostream& stream, const cObject_Group& val)
{
	stream << "std::ostream& operator<<(std::ostream& stream, const cObject_Group& val)" << "Not Implemented" << std::endl;
	return stream;
}

bool cObject_Group::RecieveMessage(const iMessage& message)
{
	std::string text = message.GetMessageString();
	std::vector<std::string> tokens;
	cFormat::Tokens(text, tokens, ", ");
	assert(tokens.size() >= 2);
	if (tokens[0] == "rotate")
	{
		int plane = cFormat::LoadInt(tokens[1]);
		float value = cFormat::LoadFloat(tokens[2]);
		rotationXYZ[plane] += value;
	}
	else
	{
		std::cout << "cObject_Group::RecieveMessage(): "
			<< "Invalid Message command: " << tokens[0]
			<< ", " << tokens[1]
			<< ", " << tokens[2] << std::endl;
		return false;
	}
	return true;
}

// Recieve a message and reply
bool cObject_Group::RecieveAndRespond(const iMessage& in, iMessage& reply)
{
	assert(false);			// Not implmented yet
	return false;
}
