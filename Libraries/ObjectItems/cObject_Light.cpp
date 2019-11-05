#include "cObject_Light.h"
#include "MessageManager/iMessage.h"
#include "MessageManager/iMessageInterface.h"
#include "MessageManager/cMessageManager.h"
#include "Utilities/cFormat.h"
#include "GameLibrary/Object.h"

#include "gl/GLCommon.h"
#include <sstream>
#include <iomanip>
#include <iostream>
#include <string>

// TODO - HACK
extern GLFWwindow* window;

cObject_Light::cObject_Light(const std::string& type,
	const std::string& name,
	const std::string& asset_id,
	rapidxml::xml_node<>* node)
	: cObject_Common()
{
	// Hack for now
	LoadCommon(type, name, asset_id, node);

	cMessageManager().Register(name, this);
}

cObject_Light::~cObject_Light()
{
}

iObject* cObject_Light::Clone(const std::string& newName)
{
	// Copy everything and change the name
	cObject_Light* ret =
		new cObject_Light(*this);
	ret->m_name = newName;
	ret->m_node = NULL;			// No XML so it won't update
	return ret;
}


// For debugging purposes - dumps the contents in human readable form
std::ostream& operator<<(std::ostream& stream, const cObject_Light& val)
{
	stream << "std::ostream& operator<<(std::ostream& stream, const cObject_Light& val)" << "Not Implemented" << std::endl;
	return stream;
}

std::string cObject_Light::LightTypeToString(cObject_Light::eLightType in)
{
	switch (in)
	{
	case eLightType::POINT:
		return "POINT";
	case eLightType::DIRECTIONAL:
		return "DIRECTIONAL";
	case eLightType::SPOT:
		return "SPOT";
	}

	return "UNKNOWN";

}

cObject_Light::eLightType cObject_Light::StringToLightType(std::string& in)
{
		if (in == "POINT")
			return eLightType::POINT;
		else if (in == "POINT")
			return eLightType::DIRECTIONAL;
		else if (in == "SPOT")
			return eLightType::SPOT;
		
		return eLightType::UNKNOWN;
}


bool cObject_Light::RecieveMessage(const iMessage& message)
{
	rapidxml::xml_node<>* node = GetNode();
	gamelibrary::Object libObject(GetNode());

	std::string text = message.GetMessageString();
	std::vector<std::string> tokens;
	cFormat::Tokens(text, tokens, ", ");
	assert(tokens.size() >= 2);

	
	if (tokens[0] == "light")
	{
		int type = cFormat::LoadInt(tokens[1]);
		float value = cFormat::LoadFloat(tokens[2]);

		if (type == 0)
		{
			// Constant attnuation
			constantAttenuation *= value;
			if (node)
				libObject.AddProperty("constantAttenuation", "float", cFormat::PackFloat(constantAttenuation));
		}
		else if (type == 1)
		{
			// Constant attnuation
			linearAttenuation *= value;
			if (node)
				libObject.AddProperty("linearAttenuation", "float", cFormat::PackFloat(linearAttenuation));
		}
		else if (type == 2)
		{
			// Constant attnuation
			quadradicAttenuation *= value;
			if (node)
				libObject.AddProperty("quadradicAttenuation", "float", cFormat::PackFloat(quadradicAttenuation));
		}

		std::stringstream ssTitle;
		ssTitle << std::fixed << std::setprecision(7)
			<< "Light : "
			<< "attenuation: "
			<< "Object: " << GetName().substr(0, 8)
			<< " c: " << constantAttenuation
			<< " l: " << linearAttenuation
			<< " q: " << quadradicAttenuation;

		glfwSetWindowTitle(window, ssTitle.str().c_str());
	}
	else if (tokens[0] == "rotate")
	{
		int plane = cFormat::LoadInt(tokens[1]);
		float value = cFormat::LoadFloat(tokens[2]);
		direction[plane] += value;
		if (node)
			libObject.AddProperty("direction", "vec3", cFormat::PackVec3(direction));

		std::stringstream ssTitle;
		ssTitle << std::fixed << std::setprecision(4)
			<< "Light : "
			<< "Direction: "
			<< "Object: " << GetName().substr(0, 8)
			<< " x: " << direction.x
			<< " y: " << direction.y
			<< " z: " << direction.z;

		glfwSetWindowTitle(window, ssTitle.str().c_str());

	}
	else if (tokens[0] == "move")
	{
		int plane = cFormat::LoadInt(tokens[1]);
		float value = cFormat::LoadFloat(tokens[2]);

	/*	{
			direction[plane] += value;
			if (node)
				libObject.AddProperty("direction", "vec3", cFormat::PackVec3(direction));

			std::stringstream ssTitle;
			ssTitle << std::fixed << std::setprecision(4)
				<< "Light : "
				<< "Move: "
				<< "Object: " << GetName().substr(0, 8)
				<< " x: " << direction.x
				<< " y: " << direction.y
				<< " z: " << direction.z;
			glfwSetWindowTitle(window, ssTitle.str().c_str());
		}*/

		positionXYZ[plane] += value;
		if (node)
			libObject.AddProperty("positionXYZ", "vec3", cFormat::PackVec3(positionXYZ));

		std::stringstream ssTitle;
		ssTitle << std::fixed << std::setprecision(4)
			<< "Light : "
			<< "Move: "
			<< "Object: " << GetName().substr(0, 8)
			<< " x: " << positionXYZ.x
			<< " y: " << positionXYZ.y
			<< " z: " << positionXYZ.z;
		glfwSetWindowTitle(window, ssTitle.str().c_str());

	}
	else if (tokens[0] == "color")
	{
		int colour = cFormat::LoadInt(tokens[1]);
		float value = cFormat::LoadFloat(tokens[2]);
		diffuseColour[colour] += value;
		if (diffuseColour[colour] > 1.0f)
			diffuseColour[colour] = 1.0f;
		if (diffuseColour[colour] < 0.0f)
			diffuseColour[colour] = 0.0f;
		specularColour = diffuseColour;			// TODO - Hack - same for now
		if (node)
			libObject.AddProperty("diffuseColour", "vec4", cFormat::PackVec4(diffuseColour));

		std::stringstream ssTitle;
		ssTitle << std::fixed << std::setprecision(4)
			<< "Light : "
			<< "Diff Colour: "
			<< "Object: " << GetName().substr(0, 8)
			<< " r: " << diffuseColour.r
			<< " g: " << diffuseColour.g
			<< " b: " << diffuseColour.b;
		glfwSetWindowTitle(window, ssTitle.str().c_str());

	}
	else if (tokens[0] == "scale")
	{
		std::cout << "cObject_Light::RecieveMessage - scale not supported" << std::endl;

		std::stringstream ssTitle;
		ssTitle << std::fixed << std::setprecision(4)
			<< "Light : "
			<< "Scale: "
			<< "Object: " << GetName().substr(0, 8)
			<< " s: " << "NOT supported";

		glfwSetWindowTitle(window, ssTitle.str().c_str());
	}
	else if (tokens[0] == "debug")
	{
		DebugSpheres = cFormat::LoadBool(tokens[1]);
		std::stringstream ssTitle;
		ssTitle << std::fixed << std::setprecision(4)
			<< "Light : "
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
bool cObject_Light::RecieveAndRespond(const iMessage& in, iMessage& reply)
{
	assert(false);			// Not implmented yet
	return false;
}
