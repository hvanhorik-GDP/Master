#include "cObject_Model.h"
#include "MessageManager/iMessage.h"
#include "MessageManager/cMessageManager.h"
#include "Utilities/cFormat.h"
#include "GameLibrary/Object.h"
#include "GameLibrary/Properties.h"
#include "GameLibrary/Objects.h"

// TODO - Hack - remove me
#include "Physics/cPhysics_Henky.h"
#include "ObjectManager/cObjectManager.h"
#include "cObject_World.h"

#include "gl/GLCommon.h"
#include <sstream>
#include <iomanip>
#include <iostream>


// TODO - HACK
extern GLFWwindow* window;

cObject_Model::cObject_Model()
	: cObject_Common()							// Need common items
	, cObject_3d()								// This is a 3d Object
	, cObject_Physics()							// and physics applies to it
	, cObject_Alias()							// Allow models to contain other objects
{
	objectColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	debugColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
}

cObject_Model::~cObject_Model()
{
}

void cObject_Model::IntegrationStep(float deltaTime)
{

	// Save our previous position to unstick things
	// Keep it handy for everyone
	if (inverseMass == 0.0f)
	{
		previousPosition = positionXYZ;		// Store this just for sake of other people testing it
		return;
	}

	// Forward Explicit Euler Inetegration
	//NewVelocty += Velocity + ( Ax * DeltaTime )

	// 
//	accel = this->m_Gravity;
	// Don't adjust velocity of we have not moved
	if (inverseMass != 0.0f)
	{
		previousVelocity = velocity;

		velocity.x += acceleration.x * deltaTime;
		velocity.y += acceleration.y * deltaTime;
		velocity.z += acceleration.z * deltaTime;
	
		//		// Or you can do this...
		//		CurObj.velocity += CurObj.accel * deltaTime;

		previousPosition = positionXYZ;

		//NewPosition = Posistion + ( Vx * DeltaTime )
		positionXYZ.x += velocity.x * deltaTime;
		positionXYZ.y += velocity.y * deltaTime;
		positionXYZ.z += velocity.z * deltaTime;

		// TODO - Remove - if we are off the map then just make it vanish
		if (positionXYZ.x < -8000)
		{
			m_isVisable = false;
			inverseMass = 0.0f;
		}
		// See if we fell off the map
//		if (positionXYZ.y < -50.0f)
//		{
//			{
//				int min = 50;
//				int max = 255;
//				int r = rand() % (max - min) + min;
//				int g = rand() % (max - min) + min;
//				int b = rand() % (max - min) + min;
//				glm::vec4 rgb = glm::vec4(float(r) / max, float(g) / max, float(b) / max, 1);
//				objectColourRGBA = rgb;
//			}
//			{
//				int min = -50;
//				int max = 50;
//				int x = rand() % (max - min) + min;
//				int y = rand() % (50) + 40;
//				int z = rand() % (max - min) + min;
//				glm::vec3 pos = glm::vec3(float(x), float(y), float(z));
//				positionXYZ = pos;
//			}
//			velocity = glm::vec3(0.0f, 0.0f, 0.0f);
//			acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
//			int newscale = rand() % 5;
//			// hack - turn off scale
////			scale = float(newscale);
////			SPHERE_radius = float(newscale);
//		}
	}

	if (debugHackTrackingMe)
	{
		// HACK - TODO - set the focus to us
			// We need to transform the matrix if it's in a group
		cObjectManager objectManager;

		auto object = objectManager.FindObjectByName("world");
		assert(object);
		cObject_World* world = dynamic_cast<cObject_World*>(object);

		auto camera = world->cameraEye;
		glm::mat4x4 m(1);
		if (m_ParentObject)
			m = cPhysics_Henky::calculateWorldMatrix(*m_ParentObject);
		glm::vec3 targetPos = m * glm::vec4(positionXYZ, 1.0f);

		auto camerposition = glm::vec3(targetPos.x - 20, targetPos.y, targetPos.z);

		world->cameraEye = camerposition;
		world->cameraTarget = targetPos;
	}
}

// For debugging purposes - dumps the contents in human readable form
std::ostream& operator<<(std::ostream& stream, const cObject_Model& val)
{
	stream << "std::ostream& operator<<(std::ostream& stream, const cObject_Model& val)" << "Not Implemented" << std::endl;
	return stream;
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
//	assert(tokens.size() >= 2);
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
	else if (tokens[0] == "track")
	{
		debugHackTrackingMe = !debugHackTrackingMe;
		std::stringstream ssTitle;
		ssTitle << std::fixed << std::setprecision(4)
			<< "Model: "
			<< "Tracking: "
			<< "Object: " << GetName()
			<< " t: " << cFormat::PackBool(debugHackTrackingMe);
		glfwSetWindowTitle(window, ssTitle.str().c_str());
	}
	else if (tokens[0] == "hit")
	{
		// Hitting the ball - apply apropriate force
		int plane = cFormat::LoadInt(tokens[1]);
		float value = cFormat::LoadFloat(tokens[2]);
		// Need some multiplyer 
		value *= 2000;
		velocity[plane] += value;

		std::stringstream ssTitle;
		ssTitle << std::fixed << std::setprecision(4)
			<< "Model: "
			<< "Hit: "
			<< "Obj: " << GetName().substr(0, 8)
			<< " x: " << velocity.x
			<< " y: " << velocity.y
			<< " z: " << velocity.z;
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
