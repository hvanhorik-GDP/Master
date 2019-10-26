#include "cObject_Group.h"
#include "MessageManager/iMessage.h"
#include "MessageManager/cMessageManager.h"
#include "Utilities/cFormat.h"
#include "GameLibrary/Object.h"


#include "GLCommon.h"
#include <sstream>
#include <iomanip>
#include <iostream>


// TODO - HACK
extern GLFWwindow* window;


cObject_Group::cObject_Group(const std::string& type,
	const std::string& name,
	const std::string& asset_id,
	rapidxml::xml_node<>* node)
	: cObject_Common()
{
	LoadCommon(type, name, asset_id, node);
	// Global registry of myself that I may recieve messages
	cMessageManager().Register(name, this);
}

cObject_Group::~cObject_Group()
{
}


iObject* cObject_Group::Clone(const std::string& newName)
{
	// Copy everything and change the name
	cObject_Group* ret =
		new cObject_Group(*this);
	ret->m_name = newName;
	ret->m_node = NULL;			// No XML so it won't update
	return ret;
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
	rapidxml::xml_node<>* node = GetNode();
	gamelibrary::Object libObject(GetNode());

	std::string text = message.GetMessageString();
	std::vector<std::string> tokens;
	cFormat::Tokens(text, tokens, ", ");
	assert(tokens.size() >= 2);
	if (tokens[0] == "rotate")
	{
		int plane = cFormat::LoadInt(tokens[1]);
		float value = cFormat::LoadFloat(tokens[2]);
		rotationXYZ[plane] += value;
		if (node)
			libObject.AddProperty("rotationXYZ", "vec3", cFormat::PackVec3(rotationXYZ));

		std::stringstream ssTitle;
		ssTitle << std::fixed << std::setprecision(4)
			<< "Group : "
			<< "Rotation: "
			<< "Object: " << GetName().substr(0, 8)
			<< " x: " << rotationXYZ.x
			<< " y: " << rotationXYZ.y
			<< " z: " << rotationXYZ.z;
		glfwSetWindowTitle(window, ssTitle.str().c_str());

	}
	else if (tokens[0] == "move")
	{
		int plane = cFormat::LoadInt(tokens[1]);
		float value = cFormat::LoadFloat(tokens[2]);
		positionXYZ[plane] += value;
		if (node)
			libObject.AddProperty("positionXYZ", "vec3", cFormat::PackVec3(positionXYZ));

		std::stringstream ssTitle;
		ssTitle << std::fixed << std::setprecision(4)
			<< "Group : "
			<< "Move: "
			<< "Object: " << GetName().substr(0, 8)
			<< " x: " << positionXYZ.x
			<< " y: " << positionXYZ.y
			<< " z: " << positionXYZ.z;
		glfwSetWindowTitle(window, ssTitle.str().c_str());

	}
	else if (tokens[0] == "color")
	{

		std::cout << "cObject_Group::RecieveMessage - color not supported" << std::endl;

		std::stringstream ssTitle;
		ssTitle << std::fixed << std::setprecision(4)
			<< "Group : "
			<< "Color: "
			<< "Object: " << GetName().substr(0, 8)
			<< " c: " << "NOT supported";

		glfwSetWindowTitle(window, ssTitle.str().c_str());
	}
	else if (tokens[0] == "scale")
	{
		float value = cFormat::LoadFloat(tokens[1]);
		scale += value;
		libObject.AddProperty("scale", "float", cFormat::PackFloat(scale));

		std::stringstream ssTitle;
		ssTitle << std::fixed << std::setprecision(4)
			<< "Group : "
			<< "Scale: "
			<< "Object: " << GetName().substr(0, 8)
			<< " s: " << scale;
		glfwSetWindowTitle(window, ssTitle.str().c_str());
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
