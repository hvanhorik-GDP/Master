#include "cPhysicsTilter.h"
#include "MessageManager/cMessageManager.h"
#include "MessageManager/cMessage_XML.h"
#include "Utilities/cFormat.h"
#include "ObjectManager/cObjectManager.h"
#include "ObjectItems/cObject_Group.h"
#include "Common/pFindObjectByFriendlyName.h"



static std::string gTilterName("tilter");

cPhysicsTilter::cPhysicsTilter()
	: m_trackObject(NULL)
{
	cMessageManager().Register(gTilterName, this);
}

const std::string& cPhysicsTilter::GetMyUID() const
{
	return gTilterName;
}

void cPhysicsTilter::track()
{
	bool wastracking = (m_trackObject != NULL);
	m_trackObject = pFindObjectByFriendlyName("Drop_Sphere");
	assert(m_trackObject);

	cMessage_XML msg(m_trackObject->GetName(), gTilterName);
	std::string text = "track,";
	msg.SetMessageString(text);

	bool ok = cMessageManager().SendMessage(msg);
	if (wastracking)
		m_trackObject = NULL;
}

void cPhysicsTilter::tiltPlane(int plane, float value)
{
	if (m_trackObject)
	{
		// Usurp the keys to poke the tracked object
		// We want to hit the ball with the applied force


		// INFO6044 - cPhysicsTilter and example of using iMessageInterface
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

			// INFO6044 - cPhysicsTilter and example of using iMessageInterface
			// This sends a message to the ground plane telling it to tilt.

			cMessage_XML msg("ground_plane", gTilterName);
			std::string text = "rotate," + cFormat::PackInt(plane) + "," + cFormat::PackFloat(value);
			msg.SetMessageString(text);

			bool ok = cMessageManager().SendMessage(msg);
		}
	}
}
