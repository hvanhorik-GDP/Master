#include "cObject_World.h"
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

cObject_World::cObject_World(const std::string& type,
	const std::string& name,
	const std::string& asset_id,
	rapidxml::xml_node<>* node)
	: cObject_Common(type, name, asset_id, node)
{
	cMessageManager().Register(name, this);

}
cObject_World::~cObject_World()
{
}

// For debugging purposes - dumps the contents in human readable form
std::ostream& operator<<(std::ostream& stream, const cObject_World& val)
{
	stream << "std::ostream& operator<<(std::ostream& stream, const cObject_World& val)" << "Not Implemented" << std::endl;
	return stream;
}

void cObject_World::IntegrationStep(float deltaTime)
{
	return;				// Nothing to do for integration
}


bool cObject_World::RecieveMessage(const iMessage& message)
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
		cameraTarget[plane] += value;
		if (node)
			libObject.AddProperty("cameraTarget", "vec3", cFormat::PackVec3(cameraTarget));

		std::stringstream ssTitle;
		ssTitle << std::fixed << std::setprecision(4)
			<< "Camera : "
			<< "target: "
			<< "Object: " << GetName().substr(0, 8)
			<< " x: " << cameraTarget.x
			<< " y: " << cameraTarget.y
			<< " z: " << cameraTarget.z;

		glfwSetWindowTitle(window, ssTitle.str().c_str());

	}
	else if (tokens[0] == "move")
	{
		int plane = cFormat::LoadInt(tokens[1]);
		float value = cFormat::LoadFloat(tokens[2]);
		cameraEye[plane] += value;
		if (node)
			libObject.AddProperty("cameraEye", "vec3", cFormat::PackVec3(cameraEye));

		std::stringstream ssTitle;
		ssTitle << std::fixed << std::setprecision(4)
			<< "Camera : "
			<< "Move: "
			<< "Object: " << GetName().substr(0, 8)
			<< " x: " << cameraEye.x
			<< " y: " << cameraEye.y
			<< " z: " << cameraEye.z;
		glfwSetWindowTitle(window, ssTitle.str().c_str());

	}
	else if (tokens[0] == "color")
	{
		std::cout << "cObject_World::RecieveMessage - color not supported" << std::endl;

		std::stringstream ssTitle;
		ssTitle << std::fixed << std::setprecision(4)
			<< "World : "
			<< "Color: "
			<< "Object: " << GetName().substr(0, 8)
			<< " c: " << "NOT supported";

		glfwSetWindowTitle(window, ssTitle.str().c_str());

	}
	else if (tokens[0] == "scale")
	{
		std::cout << "cObject_World::RecieveMessage - scale not supported" << std::endl;

		std::stringstream ssTitle;
		ssTitle << std::fixed << std::setprecision(4)
			<< "World : "
			<< "Scale: "
			<< "Object: " << GetName().substr(0, 8)
			<< " s: " << "NOT supported";

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
bool cObject_World::RecieveAndRespond(const iMessage& in, iMessage& reply)
{
	assert(false);			// Not implmented yet
	return false;
}
