#include "cGraphicsTilter.h"
#include "MessageManager/cMessageManager.h"
#include "MessageManager/cMessage_XML.h"
#include "Utilities/cFormat.h"
#include "ObjectManager/cObjectManager.h"
#include "ObjectItems/cObject_Group.h"


static std::string gTilterName("tilter");

cGraphicsTilter::cGraphicsTilter()
{
	cMessageManager().Register(gTilterName, this);
}

const std::string& cGraphicsTilter::GetMyUID() const
{
	return gTilterName;
}

void cGraphicsTilter::tiltPlane(int plane, float value)
{
	const float maxplaneTilt = .5f;

	// TODO - This is still a hack to check if we tilt too far
	// This would be a Get message to the plane to retrieve the current rotation
	cObjectManager objectManager;
	auto object = objectManager.FindObjectByName("ground_plane");
	assert(object);
	cObject_Group* group = dynamic_cast<cObject_Group*>(object);
	assert(group);
	auto howFar = group->rotationXYZ[plane];

	if (howFar < maxplaneTilt)
	{
		cMessage_XML msg("ground_plane", gTilterName);
		std::string text = "rotate," + cFormat::PackInt(plane) + "," + cFormat::PackFloat(value);
		msg.SetMessageString(text);

		bool ok = cMessageManager().SendMessage(msg);

		//		group->rotationXYZ[plane] += value;
	}
}
