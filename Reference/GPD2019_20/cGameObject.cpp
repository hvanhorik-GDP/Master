#include "cGameObject.h"
#include <glm/gtx/quaternion.hpp>

cGameObject::cGameObject()
{
	this->scale = 0.0f;
	this->isVisible = true;

	this->isWireframe = false;
	this->debugColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	this->velocity = glm::vec3(0.0f,0.0f,0.0f);
	this->accel = glm::vec3(0.0f,0.0f,0.0f);
	this->inverseMass = 0.0f;	// Infinite mass
	this->physicsShapeType = UNKNOWN;

	// Set the unique ID
	// Take the value of the static int, 
	//  set this to the instance variable
	this->m_uniqueID = cGameObject::next_uniqueID;
	// Then increment the static variable
	cGameObject::next_uniqueID++;

	this->disableDepthBufferTest = false;
	this->disableDepthBufferWrite = false;

	this->m_pDebugRenderer = NULL;

	this->positionXYZ = glm::vec3(0.0f,0.0f,0.0f);

	// Rotation of 0 degrees.
	this->m_qRotation = glm::quat(glm::vec3(0.0f,0.0f,0.0f));

	return;
}


unsigned int cGameObject::getUniqueID(void)
{
	return this->m_uniqueID;
}

void cGameObject::setDebugRenderer(iDebugRenderer* pDebugRenderer)
{
	this->m_pDebugRenderer = pDebugRenderer;
	return;
}


// this variable is static, so common to all objects.
// When the object is created, the unique ID is set, and 
//	the next unique ID is incremented
//static 
unsigned int cGameObject::next_uniqueID = 1000;	// Starting at 1000, just because





//glm::quat m_qRotation;		// Orientation as a quaternion
glm::quat cGameObject::getQOrientation(void)
{
	return this->m_qRotation;
}

// Overwrite the orientation
void cGameObject::setOrientation(glm::vec3 EulerAngleDegreesXYZ)
{
	// c'tor of the glm quaternion converts Euler 
	//	to quaternion representation. 
	glm::vec3 EulerAngleRadians;
	EulerAngleRadians.x = glm::radians(EulerAngleDegreesXYZ.x);
	EulerAngleRadians.y = glm::radians(EulerAngleDegreesXYZ.y);
	EulerAngleRadians.z = glm::radians(EulerAngleDegreesXYZ.z);

	this->m_qRotation = glm::quat(EulerAngleRadians);
}

void cGameObject::setOrientation(glm::quat qAngle)
{
	this->m_qRotation = qAngle;
}

// Updates the existing angle
void cGameObject::updateOrientation(glm::vec3 EulerAngleDegreesXYZ)
{
	// Create a quaternion of this angle...
	glm::vec3 EulerAngleRadians;
	EulerAngleRadians.x = glm::radians(EulerAngleDegreesXYZ.x);
	EulerAngleRadians.y = glm::radians(EulerAngleDegreesXYZ.y);
	EulerAngleRadians.z = glm::radians(EulerAngleDegreesXYZ.z);

	glm::quat angleChange = glm::quat(EulerAngleRadians);

	// ...apply it to the exiting rotation
	this->m_qRotation *= angleChange;
}

void cGameObject::updateOrientation(glm::quat qAngleChange)
{
	this->m_qRotation *= qAngleChange;
}

glm::vec3 cGameObject::getEulerAngle(void)
{
	// In glm::gtx (a bunch of helpful things there)
	glm::vec3 EulerAngle = glm::eulerAngles(this->m_qRotation);

	return EulerAngle;
}