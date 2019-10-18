#include "cGraphicsToObject.h"
#include "MessageManager/cMessageManager.h"
#include "MessageManager/cMessage_XML.h"
#include "Utilities/cFormat.h"
#include "ObjectManager/cObjectManager.h"
#include "ObjectItems/cObject_Group.h"
#include "ObjectItems/cObject_Model.h"

#include "GLCommon.h"
#include "Common/globalStuff.h"
#include <sstream>
#include <iomanip>


static std::string gGraphicsObjectName("GraphicsObject");


cGraphicsToObject::cGraphicsToObject()
{
	cMessageManager().Register(gGraphicsObjectName, this);
	cObjectManager objectManager;
	auto objects = objectManager.GetObjects("model");
	
	// Make a nice linked list
	for (auto object : (*objects))
	{
		auto oModel = dynamic_cast<cObject_Model*>(object.second);
		assert(oModel);
		m_Objects.push_back(oModel);
	}
	m_CurrentObject = NULL;
}

void cGraphicsToObject::NextVisable()
{
	for (int i = m_CurrentOffset+1; i < m_Objects.size(); ++i)
	{
		auto object = m_Objects[i];
		if (object->isVisible)
		{
			m_CurrentObject = object;
			m_CurrentOffset = i;
			m_lastWasVisable = true;
			std::stringstream ssTitle;
			ssTitle << "Object: "
				<< "Object: " << m_CurrentObject->GetName();

			glfwSetWindowTitle(window, ssTitle.str().c_str());

			return;
		}
	}
	for (int i = 0; i < m_CurrentOffset; ++i)
	{
		auto object = m_Objects[i];
		if (object->isVisible)
		{
			m_CurrentObject = object;
			m_CurrentOffset = i;
			m_lastWasVisable = true;
			std::stringstream ssTitle;
			ssTitle << "Object: "
				<< "Object: " << m_CurrentObject->GetName();

			glfwSetWindowTitle(window, ssTitle.str().c_str());

			return;
		}
	}
}

void cGraphicsToObject::NextInvisable()
{
	if (m_CurrentObject)
		m_CurrentObject->isVisible = m_lastWasVisable;

	++m_CurrentOffset;
	if (m_CurrentOffset >= m_Objects.size())
		m_CurrentOffset = 0;

	auto object = m_Objects[m_CurrentOffset];
	m_CurrentObject = object;
	m_lastWasVisable = object->isVisible;
	object->isVisible = true;
	std::stringstream ssTitle;
	ssTitle << "Object: "
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

	auto rotate = m_CurrentObject->rotationXYZ;
	std::stringstream ssTitle;

	ssTitle << std::fixed << std::setprecision(4)
		<< "Rotation: "
		<< "Object: " << m_CurrentObject->GetName().substr(0, 8)
		<< " x: " << rotate.x 
		<< " y: " << rotate.y 
		<< " z: " << rotate.z;

	glfwSetWindowTitle(window, ssTitle.str().c_str());

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
	auto colour = m_CurrentObject->objectColourRGBA;
	std::stringstream ssTitle;
	ssTitle << std::fixed << std::setprecision(4)
		<< "Colour: "
		<< "Object: " << m_CurrentObject->GetName().substr(0, 8)
		<< " r : " << colour.r 
		<< " g : " << colour.g 
		<< " b : " << colour.b;

	glfwSetWindowTitle(window, ssTitle.str().c_str());

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
	auto scale = m_CurrentObject->scale;
	std::stringstream ssTitle;
	ssTitle << std::fixed << std::setprecision(4)
		<< "Rotation: "
		<< "Object: " << m_CurrentObject->GetName().substr(0, 8)
		<< "Scale: " << scale;

	glfwSetWindowTitle(window, ssTitle.str().c_str());

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

	auto position = m_CurrentObject->positionXYZ;
	std::stringstream ssTitle;
	ssTitle << std::fixed <<std::setprecision(4)
		<< "Position: "
		<< "Object: " << m_CurrentObject->GetName().substr(0,8)
		<< " x: " << position.x
		<< " y: " << position.y
		<< " z: " << position.z;

	glfwSetWindowTitle(window, ssTitle.str().c_str());

}

const std::string& cGraphicsToObject::GetMyUID() const
{
	return gGraphicsObjectName;
}
