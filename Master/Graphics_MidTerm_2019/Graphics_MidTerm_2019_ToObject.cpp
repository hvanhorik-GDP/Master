#include "Graphics_MidTerm_2019_ToObject.h"
#include "MessageManager/cMessageManager.h"
#include "MessageManager/cMessage_XML.h"
#include "Utilities/cFormat.h"
#include "ObjectManager/cObjectManager.h"
#include "ObjectItems/cObject_Group.h"
#include "ObjectItems/cObject_Model.h"
#include "ObjectItems/cObject_World.h"
#include "ObjectItems/cObject_Light.h"
#include "Physics/cPhysics_Henky.h"

#include "GLCommon.h"
#include <sstream>
#include <iomanip>
#include <iostream>

// TODO - HACK
extern GLFWwindow* window;

static std::string gGraphicsObjectName("GraphicsObject");


Graphics_MidTerm_2019_ToObject::Graphics_MidTerm_2019_ToObject()
{
	cMessageManager().Register(gGraphicsObjectName, this);
	TargetWorld();
}

void Graphics_MidTerm_2019_ToObject::NextVisable()
{
	if (m_CurrentObject)
		m_CurrentObject->SetVisable(m_lastWasVisable);

	for (int i = m_NextOffset; i < m_Objects.size(); ++i)
	{
		auto object = m_Objects[i];
		if (object->IsVisable())
		{
			m_CurrentObject = object;
			m_NextOffset = i+1;
			m_lastWasVisable = true;

			std::stringstream ssTitle;
			ssTitle << "Object: "
				<< "Type: " << m_CurrentObject->GetType()
				<< "Object: " << m_CurrentObject->GetName();

			glfwSetWindowTitle(window, ssTitle.str().c_str());

			return;
		}
	}
	for (int i = 0; i < m_NextOffset; ++i)
	{
		auto object = m_Objects[i];
		if (object->IsVisable())
		{
			m_CurrentObject = object;
			m_NextOffset = i=1;
			m_lastWasVisable = true;
			std::stringstream ssTitle;
			ssTitle << "Object: "
				<< "Type: " << m_CurrentObject->GetType()
				<< "Object: " << m_CurrentObject->GetName();

			glfwSetWindowTitle(window, ssTitle.str().c_str());

			return;
		}
	}
}

void Graphics_MidTerm_2019_ToObject::NextInvisable()
{
	if (m_CurrentObject)
		m_CurrentObject->SetVisable(m_lastWasVisable);


	if (m_NextOffset >= m_Objects.size())
		m_NextOffset = 0;
	auto object = m_Objects[m_NextOffset];
	m_NextOffset++;
	m_CurrentObject = object;
	m_lastWasVisable = object->IsVisable();
	object->SetVisable(true);
	std::stringstream ssTitle;
	ssTitle << "Object: "
		<< "Type: " << m_CurrentObject->GetType()
		<< "Object: " << m_CurrentObject->GetName();

	glfwSetWindowTitle(window, ssTitle.str().c_str());

	return;
}


template <class T>
static T randInRange(T min, T max)
{
	double value =
		min + static_cast <double> (rand())
		/ (static_cast <double> (RAND_MAX / (static_cast<double>(max - min))));
	return static_cast<T>(value);
};

void Graphics_MidTerm_2019_ToObject::Duplicate()
{
	if (!m_CurrentObject)
		return;

	cObject_Model* model = dynamic_cast<cObject_Model*>(m_CurrentObject);
	// Only for models now
	if (!model)
		return;
	auto parent = model->GetNode()->parent();

	srand(time(NULL));
	static int start_number = randInRange(1000, 100000);
	std::string name = m_CurrentObject->GetName();
	std::string newName = name + "_" + std::to_string(start_number++);
	auto temp = m_CurrentObject->Clone(newName);
	assert(temp);
	model = dynamic_cast<cObject_Model*>(m_CurrentObject);
	// Only for models now
	if (!model)
		return;
	// Shift it a bit
	model->positionXYZ.z += 5;
	cObjectManager().SaveObject(temp, parent);

	m_Objects.push_back(temp);

	m_CurrentObject = temp;

	std::stringstream ssTitle;
	ssTitle << "Duplicate: Object: "
		<< "Type: " << m_CurrentObject->GetType()
		<< "Object: " << m_CurrentObject->GetName();

}


void Graphics_MidTerm_2019_ToObject::Rotate(int plane, float value)
{
	if (!m_CurrentObject)
		return;
	std::string name = m_CurrentObject->GetName();
	cMessage_XML msg(name, gGraphicsObjectName);
	std::string text = "rotate," + cFormat::PackInt(plane) + "," + cFormat::PackFloat(value);
	msg.SetMessageString(text);
	
	bool ok = cMessageManager().SendMessage(msg);
}

void Graphics_MidTerm_2019_ToObject::AdjustColour(int color, float value)
{
	if (!m_CurrentObject)
		return;
	std::string name = m_CurrentObject->GetName();
	cMessage_XML msg(name, gGraphicsObjectName);
	std::string text = "color," + cFormat::PackInt(color) + "," + cFormat::PackFloat(value);
	msg.SetMessageString(text);

	bool ok = cMessageManager().SendMessage(msg);


}
void Graphics_MidTerm_2019_ToObject::Scale(float value)
{
	if (!m_CurrentObject)
		return;
	std::string name = m_CurrentObject->GetName();
	cMessage_XML msg(name, gGraphicsObjectName);
	std::string text = "scale," + cFormat::PackFloat(value);
	msg.SetMessageString(text);

	bool ok = cMessageManager().SendMessage(msg);


}

void Graphics_MidTerm_2019_ToObject::Move(int plane, float value)
{
	if (!m_CurrentObject)
		return;
	std::string name = m_CurrentObject->GetName();
	cMessage_XML msg(name, gGraphicsObjectName);
	std::string text = "move," + cFormat::PackInt(plane) + "," + cFormat::PackFloat(value);
	msg.SetMessageString(text);

	bool ok = cMessageManager().SendMessage(msg);

}

void Graphics_MidTerm_2019_ToObject::Light(int type, float value)
{
	if (!m_CurrentObject)
		return;
	std::string name = m_CurrentObject->GetName();
	cMessage_XML msg(name, gGraphicsObjectName);
	std::string text = "light," + cFormat::PackInt(type) + "," + cFormat::PackFloat(value);
	msg.SetMessageString(text);

	bool ok = cMessageManager().SendMessage(msg);

}

void Graphics_MidTerm_2019_ToObject::SetDebug(bool value)
{
	bool m_debug = false;
	if (!m_CurrentObject)
		return;
	std::string name = m_CurrentObject->GetName();
	cMessage_XML msg(name, gGraphicsObjectName);
	std::string text = "debug," + cFormat::PackBool(value);
	msg.SetMessageString(text);

	bool ok = cMessageManager().SendMessage(msg);
}
void Graphics_MidTerm_2019_ToObject::SetWireFrame(bool value)
{
	bool m_debug = false;
	if (!m_CurrentObject)
		return;
	std::string name = m_CurrentObject->GetName();
	cMessage_XML msg(name, gGraphicsObjectName);
	std::string text = "wire," + cFormat::PackBool(value);
	msg.SetMessageString(text);

	bool ok = cMessageManager().SendMessage(msg);

}

void Graphics_MidTerm_2019_ToObject::Focus()
{
	if (!m_CurrentObject)
		return;
	cObjectManager objectManager;

	auto object = objectManager.FindObjectByName("world");
	assert(object);
	cObject_World* world = dynamic_cast<cObject_World*>(object);

	glm::vec3 targetPos;
	auto camera = world->cameraEye;
	iObject* parent = NULL;
	if (m_CurrentObject->GetType() == "model")
	{
		cObject_Model* model = dynamic_cast<cObject_Model*> (m_CurrentObject);
		targetPos = model->positionXYZ;
		parent = model->GetParentObject();
	}
	else if (m_CurrentObject->GetType() == "group")
	{
		cObject_Group* group = dynamic_cast<cObject_Group*> (m_CurrentObject);
		targetPos = group->positionXYZ;
		parent = group->GetParentObject();
	}
	else if (m_CurrentObject->GetType() == "light")
	{
		cObject_Light* light = dynamic_cast<cObject_Light*> (m_CurrentObject);
		targetPos = light->positionXYZ;
		parent = light->GetParentObject();
	}
	else
	{
		return;
	}
	// We need to transform the matrix if it's in a group
	glm::mat4x4 m(1);
	if (parent)
		m = cPhysics_Henky::calculateWorldMatrix(*parent);
	targetPos = m * glm::vec4(targetPos, 1.0f);

	auto camerposition = glm::vec3(targetPos.x + 30, targetPos.y, targetPos.z );
//	auto cameradirection = glm::vec3(0, 0, 10);

	world->cameraEye = camerposition;
	world->cameraTarget = targetPos;

	auto parentNode = world->GetNode()->parent();
	cObjectManager().SaveObject(world, parentNode);
}

const std::string& Graphics_MidTerm_2019_ToObject::GetMyUID() const
{
	return gGraphicsObjectName;
}

void Graphics_MidTerm_2019_ToObject::TargetModels()
{
	// Restore previous object
	if (m_CurrentObject)
		m_CurrentObject->SetVisable(m_lastWasVisable);

	m_Objects.clear();		// Clear the old, in with the new

	cObjectManager objectManager;
	auto objects = objectManager.GetObjects("model");

	// Make a nice linked list
	for (auto object : (*objects))
	{
		m_Objects.push_back(object.second);
	}
	m_CurrentObject = NULL;

	std::stringstream ssTitle;
	ssTitle << "Object: "
		<< "Type: " << "models";

	glfwSetWindowTitle(window, ssTitle.str().c_str());
	NextVisable();

}

void Graphics_MidTerm_2019_ToObject::SetCamera(glm::vec3 target, glm::vec3 eye)
{
	cObjectManager objectManager;

	auto object = objectManager.FindObjectByName("world");
	assert(object);
	cObject_World* world = dynamic_cast<cObject_World*>(object);

	glm::vec3 targetPos;
	auto camera = world->cameraEye;
	iObject* parent = NULL;
	world->cameraTarget = target;
	world->cameraEye = eye;
	auto parentNode = world->GetNode()->parent();
	cObjectManager().SaveObject(world, parentNode);

//	<Property name = "cameraEye" type = "vec3" value = "-123.111 184.748 -50.029" / >
}

//< Property name = "positionXYZ" type = "vec3" value = "-121.701 182.15 -65.0992" / >

void Graphics_MidTerm_2019_ToObject::TargetLights()
{
	// Restore previous object
	if (m_CurrentObject)
		m_CurrentObject->SetVisable(m_lastWasVisable);

	m_Objects.clear();		// Clear the old, in with the new

	cObjectManager objectManager;
	auto objects = objectManager.GetObjects("light");

	// Make a nice linked list
	for (auto object : (*objects))
	{
		m_Objects.push_back(object.second);
	}
	m_CurrentObject = NULL;

	std::stringstream ssTitle;
	ssTitle << "Object: "
		<< "Type: " << "lights";

	glfwSetWindowTitle(window, ssTitle.str().c_str());
	NextVisable();

}
void Graphics_MidTerm_2019_ToObject::TargetGroups()
{
	// Restore previous object
	if (m_CurrentObject)
		m_CurrentObject->SetVisable(m_lastWasVisable);

	m_Objects.clear();		// Clear the old, in with the new

	cObjectManager objectManager;
	auto objects = objectManager.GetObjects("group");

	// Make a nice linked list
	for (auto object : (*objects))
	{
		m_Objects.push_back(object.second);
	}
	m_CurrentObject = NULL;

	std::stringstream ssTitle;
	ssTitle << "Object: "
		<< "Type: " << "groups";

	glfwSetWindowTitle(window, ssTitle.str().c_str());
	NextVisable();

}

void Graphics_MidTerm_2019_ToObject::TargetWorld()
{
	// Restore previous object
	if (m_CurrentObject)
		m_CurrentObject->SetVisable(m_lastWasVisable);

	m_Objects.clear();		// Clear the old, in with the new

	cObjectManager objectManager;
	auto objects = objectManager.GetObjects("world");

	// Make a nice linked list
	for (auto object : (*objects))
	{
		m_Objects.push_back(object.second);
	}
	m_CurrentObject = NULL;

	std::stringstream ssTitle;
	ssTitle << "Object: "
		<< "Type: " << "world/camera";

	glfwSetWindowTitle(window, ssTitle.str().c_str());
	NextVisable();

}


void Graphics_MidTerm_2019_ShiftAllObjects(rapidxml::xml_node<>* parent)
{
	cObjectManager manager;

	static int shift = -200;
	auto objects = manager.GetObjects("model");

	for (auto object : *objects)
	{
		if (object.second->GetName() != "surface_output_01")
		{
			cObject_Model* object_model = dynamic_cast<cObject_Model*>(object.second);
			assert(object_model);
			shift += 15;
			object_model->positionXYZ.z += shift;
			object_model->m_isVisable = true;

			manager.SaveObject(object_model, parent);
		}
	}
}

void Graphics_MidTerm_2019_CalculateBounds(rapidxml::xml_node<>* parent)
{
	cObjectManager manager;

	auto objects = manager.GetObjects("model");

	for (auto object : *objects)
	{
		glm::vec3 object_min;
		glm::vec3 object_max;

		cObject_Model* object_model = dynamic_cast<cObject_Model*>(object.second);
		assert(object_model);
		cPhysics_Henky::boundsOfObject(*object_model, object_min, object_max);

		object_model->AABB_min = object_min;
		object_model->AABB_max = object_max;

		manager.SaveObject(object_model, parent);
	}
}


static const int interval = 45;		// every 10 seconds
static int g_count = 0;

void Graphics_MidTerm_2019_Flicker()
{
	if (g_count++ > interval)
		return;
	g_count = 0;
	cObjectManager manager;
	std::vector<std::string> names;
	names.push_back("cave_light");
	names.push_back("light_skull_01");
	names.push_back("light_skull_02");

	for (auto it : names)
	{ 
		auto temp = manager.FindObjectByName(it);
		cObject_Light* light = dynamic_cast<cObject_Light*>(temp);
		light->constantAttenuation = randInRange(0.08f, 0.1f);
		light->linearAttenuation = randInRange(1.0f, 1.9f);
		light->quadradicAttenuation = randInRange(0.01f, 0.15f);
	}

}

bool gFlyCamera = false;

float g_xPosition = 250;
float g_xCount = -1;
float g_zPosition = 210;
float g_zCount = -1;

void Graphics_MidTerm_2019_FlyCamera()
{
	if (gFlyCamera)
	{
		cObjectManager objectManager;

		auto object = objectManager.FindObjectByName("world");
		assert(object);
		cObject_World* world = dynamic_cast<cObject_World*>(object);

		auto newxPos = g_xPosition;
		auto newzPos = g_zPosition;
//		std::cout << "Position : " << newxPos << " , " << newzPos << std::endl;
		glm::vec3 eye(newxPos, 200, newzPos);
		g_xPosition += g_xCount;
		if (abs(g_xPosition) > 250)
			g_xCount = -g_xCount;
		g_zPosition += g_zCount;
		if (abs(g_zPosition) > 210)
			g_zCount = -g_zCount;

		glm::vec3 target(-121.111, 184.748-40, -64.01);
		world->cameraEye = eye;
		world->cameraTarget = target;
	}

}

void Graphics_MidTerm_2019_create_Fireflies()
{

}
