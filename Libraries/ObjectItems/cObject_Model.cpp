#include "cObject_Model.h"
#include "MessageManager/iMessage.h"
#include "MessageManager/cMessageManager.h"
#include "Utilities/cFormat.h"
#include "GameLibrary/Object.h"
#include "GameLibrary/Properties.h"
#include "GameLibrary/Objects.h"

#include "GLCommon.h"
#include <sstream>
#include <iomanip>
#include <iostream>


// TODO - HACK
extern GLFWwindow* window;

cObject_Model::cObject_Model(const std::string& type,
	const std::string& name,
	const std::string& asset_id,
	rapidxml::xml_node<>* node)
	: cObject_Common(type, name, asset_id, node)
{
	matWorld = glm::mat4(1.0f);
	// Global registry of myself that I may recieve messages
	cMessageManager().Register(name, this);

}

cObject_Model::~cObject_Model()
{
}

void cObject_Model::IntegrationStep(float deltaTime)
{

	// Forward Explicit Euler Inetegration
	//NewVelocty += Velocity + ( Ax * DeltaTime )

	// 
//	accel = this->m_Gravity;

	velocity.x += accel.x * deltaTime;
	velocity.y += accel.y * deltaTime;
	velocity.z += accel.z * deltaTime;
	//		// Or you can do this...
	//		CurObj.velocity += CurObj.accel * deltaTime;

			//NewPosition = Posistion + ( Vx * DeltaTime )

	positionXYZ.x += velocity.x * deltaTime;
	positionXYZ.y += velocity.y * deltaTime;
	positionXYZ.z += velocity.z * deltaTime;

	// See if we fell off the map
	if (positionXYZ.y < -50.0f)
	{
		{
			int min = 50;
			int max = 255;
			int r = rand() % (max - min) + min;
			int g = rand() % (max - min) + min;
			int b = rand() % (max - min) + min;
			glm::vec4 rgb = glm::vec4(float(r) / max, float(g) / max, float(b) / max, 1);
			objectColourRGBA = rgb;
		}
		{
			int min = -5;
			int max = 5;
			int x = rand() % (max - min) + min;
			int y = rand() % (50) + 40;
			int z = rand() % (max - min) + min;
			glm::vec3 pos = glm::vec3(float(x), float(y), float(z));
			positionXYZ = pos;
		}
		velocity = glm::vec3(0.0f, 0.0f, 0.0f);
		accel = glm::vec3(0.0f, 0.0f, 0.0f);
		int newscale = rand() % 5;
		scale = float(newscale);
		SPHERE_radius = float(newscale);
	}
}

// For debugging purposes - dumps the contents in human readable form
std::ostream& operator<<(std::ostream& stream, const cObject_Model& val)
{
	stream << "std::ostream& operator<<(std::ostream& stream, const cObject_Model& val)" << "Not Implemented" << std::endl;
	return stream;
}

std::string cObject_Model::ShapeTypeToString(cObject_Model::eShapeTypes in)
{
	switch (in)
	{
	case eShapeTypes::AABB:
		return "AABB";
	case eShapeTypes::CAPSULE:
		return "CAPSULE";
	case eShapeTypes::MESH:
		return "MESH";
	case eShapeTypes::PLANE:
		return "PLANE";
	case eShapeTypes::SPHERE:
		return "SPHERE";
	}
	return "UNKNOWN";
}
cObject_Model::eShapeTypes cObject_Model::StringToShapeType(std::string& in)
{
	if (in == "AABB")
		return eShapeTypes::AABB;
	if (in == "CAPSULE")
		return eShapeTypes::CAPSULE;
	if (in == "MESH")
		return eShapeTypes::MESH;
	if (in == "PLANE")
		return eShapeTypes::PLANE;
	if (in == "SPHERE")
		return eShapeTypes::SPHERE;
	return eShapeTypes::UNKNOWN;
}

iObject* cObject_Model::Clone(const std::string& newName)
{
	// Copy everything and change the name
	cObject_Model* ret =
		new cObject_Model(*this);
	ret->m_name = newName;
	ret->m_node = NULL;			// No XML so it won't update
	return ret;
}


bool cObject_Model::RecieveMessage(const iMessage& message)
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
			<< "Model: "
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
			<< "Model: "
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
		objectColourRGBA[colour] += value;
		if (objectColourRGBA[colour] > 1.0f)
			objectColourRGBA[colour] = 1.0f;
		if (objectColourRGBA[colour] < 0.0f)
			objectColourRGBA[colour] = 0.0f;
		if (node)
			libObject.AddProperty("objectColourRGBA", "vec4", cFormat::PackVec4(objectColourRGBA));

	
		std::stringstream ssTitle;
		ssTitle << std::fixed << std::setprecision(4)
			<< "Model: "
			<< "Colour: "
			<< "Object: " << GetName().substr(0, 8)
			<< " r: " << objectColourRGBA.r
			<< " g: " << objectColourRGBA.g
			<< " b: " << objectColourRGBA.b;
		glfwSetWindowTitle(window, ssTitle.str().c_str());

	}
	else if (tokens[0] == "scale")
	{
		float value = cFormat::LoadFloat(tokens[1]);
		scale += value;
		libObject.AddProperty("scale", "float", cFormat::PackFloat(scale));

		std::stringstream ssTitle;
		ssTitle << std::fixed << std::setprecision(4)
			<< "Model: "
			<< "Scale: "
			<< "Object: " << GetName().substr(0, 8)
			<< " s: " << scale;
		glfwSetWindowTitle(window, ssTitle.str().c_str());
	}
	else if (tokens[0] == "wire")
	{
		float value = cFormat::LoadBool(tokens[1]);
		isWireframe = !isWireframe;
		libObject.AddProperty("isWireframe", "bool", cFormat::PackBool(isWireframe));

		std::stringstream ssTitle;
		ssTitle << std::fixed << std::setprecision(4)
			<< "Model: "
			<< "WireFrame: "
			<< "Object: " << GetName().substr(0, 8)
			<< " w: " << cFormat::PackBool(isWireframe);
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
bool cObject_Model::RecieveAndRespond(const iMessage& in, iMessage& reply)
{
	assert(false);			// Not implmented yet
	return false;
}
