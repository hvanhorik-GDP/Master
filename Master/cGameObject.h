#ifndef _cGameObject_HG_
#define _cGameObject_HG_

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <string>

enum eShapeTypes
{
	AABB, 
	SPHERE, 
	CAPSULE,
	PLANE,
	MESH,
	UNKNOWN
};

class cGameObject
{
public:
	cGameObject()
	{
		this->scale = 0.0f;
		this->physicsShapeType = UNKNOWN;
	}
	std::string meshName;			//"Pirate"
	glm::vec3  positionXYZ;
	glm::vec3  rotationXYZ;
	glm::vec4  objectColourRGBA;	
	float scale;

	// Add some physics things
	glm::vec3 velocity;
	glm::vec3 accel;

	// If the object has an inverse mass of 0.0
	//	then it's not updated by the physics code
	float inverseMass;	// 0.0f = Doesn't move

	//bool bIsDynamic;

	eShapeTypes physicsShapeType;
};

#endif

