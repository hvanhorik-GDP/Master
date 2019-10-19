#include "cGraphicsToObject.h"
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

// TODO - HACK
extern GLFWwindow* window;

static std::string gGraphicsObjectName("GraphicsObject");


cGraphicsToObject::cGraphicsToObject()
{
	cMessageManager().Register(gGraphicsObjectName, this);
}

void cGraphicsToObject::NextVisable()
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

void cGraphicsToObject::NextInvisable()
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

void cGraphicsToObject::Rotate(int plane, float value)
{
	if (!m_CurrentObject)
		return;
	std::string name = m_CurrentObject->GetName();
	cMessage_XML msg(name, gGraphicsObjectName);
	std::string text = "rotate," + cFormat::PackInt(plane) + "," + cFormat::PackFloat(value);
	msg.SetMessageString(text);
	
	bool ok = cMessageManager().SendMessage(msg);

}

void cGraphicsToObject::AdjustColour(int color, float value)
{
	if (!m_CurrentObject)
		return;
	std::string name = m_CurrentObject->GetName();
	cMessage_XML msg(name, gGraphicsObjectName);
	std::string text = "color," + cFormat::PackInt(color) + "," + cFormat::PackFloat(value);
	msg.SetMessageString(text);

	bool ok = cMessageManager().SendMessage(msg);


}
void cGraphicsToObject::Scale(float value)
{
	if (!m_CurrentObject)
		return;
	std::string name = m_CurrentObject->GetName();
	cMessage_XML msg(name, gGraphicsObjectName);
	std::string text = "scale," + cFormat::PackFloat(value);
	msg.SetMessageString(text);

	bool ok = cMessageManager().SendMessage(msg);


}

void cGraphicsToObject::Move(int plane, float value)
{
	if (!m_CurrentObject)
		return;
	std::string name = m_CurrentObject->GetName();
	cMessage_XML msg(name, gGraphicsObjectName);
	std::string text = "move," + cFormat::PackInt(plane) + "," + cFormat::PackFloat(value);
	msg.SetMessageString(text);

	bool ok = cMessageManager().SendMessage(msg);

}

void cGraphicsToObject::Light(int type, float value)
{
	if (!m_CurrentObject)
		return;
	std::string name = m_CurrentObject->GetName();
	cMessage_XML msg(name, gGraphicsObjectName);
	std::string text = "light," + cFormat::PackInt(type) + "," + cFormat::PackFloat(value);
	msg.SetMessageString(text);

	bool ok = cMessageManager().SendMessage(msg);

}

void cGraphicsToObject::SetDebug(bool value)
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
void cGraphicsToObject::SetWireFrame(bool value)
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

void cGraphicsToObject::Focus()
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

	auto camerposition = glm::vec3(targetPos.x - 15, targetPos.y, targetPos.z );
//	auto cameradirection = glm::vec3(0, 0, 10);

	world->cameraEye = camerposition;
	world->cameraTarget = targetPos;
}

const std::string& cGraphicsToObject::GetMyUID() const
{
	return gGraphicsObjectName;
}

void cGraphicsToObject::TargetModels()
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

void cGraphicsToObject::TargetLights()
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
void cGraphicsToObject::TargetGroups()
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

void cGraphicsToObject::TargetWorld()
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