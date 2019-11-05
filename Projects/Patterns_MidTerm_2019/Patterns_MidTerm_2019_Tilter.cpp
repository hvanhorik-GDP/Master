#include "Patterns_MidTerm_2019_Tilter.h"
#include "MessageManager/cMessageManager.h"
#include "MessageManager/cMessage_XML.h"
#include "Utilities/cFormat.h"
#include "ObjectManager/cObjectManager.h"
#include "ObjectItems/cObject_Group.h"



static std::string gTilterName("tilter");

Patterns_MidTerm_2019_Tilter::Patterns_MidTerm_2019_Tilter()
	: m_trackObject(NULL)
{
	cMessageManager().Register(gTilterName, this);
}

const std::string& Patterns_MidTerm_2019_Tilter::GetMyUID() const
{
	return gTilterName;
}

void Patterns_MidTerm_2019_Tilter::track()
{
	bool wastracking = (m_trackObject != NULL);
	cObjectManager objectManager;
	auto object = objectManager.FindObjectByName("Drop_Sphere");
	assert(object);
	m_trackObject = dynamic_cast<cObject_Model*>(object);
	assert(m_trackObject);

	cMessage_XML msg(m_trackObject->GetName(), gTilterName);
	std::string text = "track,";
	msg.SetMessageString(text);

	bool ok = cMessageManager().SendMessage(msg);
	if (wastracking)
		m_trackObject = NULL;
}

void Patterns_MidTerm_2019_Tilter::tiltPlane(int plane, float value)
{
	if (m_trackObject)
	{
		// Usurp the keys to poke the tracked object
		// We want to hit the ball with the applied force


		// PhysicsTilter and example of using iMessageInterface
		// This sends a message to an object saying I have "hit" it.

		cMessage_XML msg(m_trackObject->GetName(), gTilterName);
		std::string text = "hit," + cFormat::PackInt(plane) + "," + cFormat::PackFloat(value);
		msg.SetMessageString(text);
		bool ok = cMessageManager().SendMessage(msg);
	}
	else
	{
		const float maxplaneTilt = .5f;

		// TODO - BUG - This is still a hack to check if we tilt too far
		// This would be a Get message to the plane to retrieve the current rotation
		cObjectManager objectManager;
		auto object = objectManager.FindObjectByName("ground_plane");
		assert(object);
		cObject_Group* group = dynamic_cast<cObject_Group*>(object);
		assert(group);
		auto howFar = group->rotationXYZ[plane];

		if (howFar < maxplaneTilt)
		{

			// Patterns_MidTerm_2019_Tilter and example of using iMessageInterface
			// This sends a message to the ground plane telling it to tilt.

			cMessage_XML msg("ground_plane", gTilterName);
			std::string text = "rotate," + cFormat::PackInt(plane) + "," + cFormat::PackFloat(value);
			msg.SetMessageString(text);

			bool ok = cMessageManager().SendMessage(msg);
		}
	}
}
