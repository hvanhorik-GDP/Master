#include "HandleDebugPirate.h"

#include "../Common/pFindObjectByFriendlyName.h"
// ********************************************************
// Move the pirate in the direction it's pointing in...

// Vec4 = mat4x4 * vec4				vertFinal = matModel * vertStart;

void HandleDebugPirate(cDebugRenderer* pDebugRenderer)
{
	//cObject_Model* pPirate = pFindObjectByFriendlyName("PirateShip");

	//glm::mat4 matRotY = glm::rotate(glm::mat4(1.0f),
	//	pPirate->HACK_AngleAroundYAxis,	//(float)glfwGetTime(),					// Angle 
	//	glm::vec3(0.0f, 1.0f, 0.0f));

	//// Assume the ship is at 0,0,0
	//glm::vec4 frontOfShip = glm::vec4(0.0f, 0.0f, -1.0f, 1.0f);	// pointing to the "front" of the ship

	//// Vec4 = mat4x4 * vec4				vertFinal = matModel * vertStart;
	//glm::vec4 frontOfShipInWorld = matRotY * frontOfShip;

	//// this value would be the velocity, ifyou wanted the phsyics update do to it
	//glm::vec3 newSpeedOfShipIN_THE_DIRECTION_WE_WANT_TO_GO
	//	= frontOfShipInWorld * pPirate->HACK_speed;

	//// Draw a line showing where we are going...
	//pDebugRenderer->addLine(pPirate->positionXYZ,
	//	pPirate->positionXYZ + (glm::vec3(frontOfShipInWorld) * pPirate->HACK_speed * 5.0f),
	//	glm::vec3(1.0f, 0.0f, 0.0f), 0.5f);

	//// Draw a line showing how fast we are going...

	//// Update the pirate ship
	//pPirate->positionXYZ += newSpeedOfShipIN_THE_DIRECTION_WE_WANT_TO_GO;

}
