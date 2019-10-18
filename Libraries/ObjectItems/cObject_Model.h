#pragma once
#include "cObject_Common.h"

#include <glm/glm.hpp>

#include <string>
#include <map>

class cObject_Model : public cObject_Common 
{
public:

	enum eShapeTypes
	{
		UNKNOWN,				// Default is unknown
		AABB,					// min and max corners 
		SPHERE,					// Radius
		CAPSULE,
		PLANE,
		MESH,					// Triangle test
	};

	cObject_Model() {};

	cObject_Model(const std::string& type,
		const std::string& name,
		const std::string& asset_id,
		rapidxml::xml_node<>* node);
	virtual ~cObject_Model();

	virtual void IntegrationStep(float deltaTime) final;

	virtual iObject* Clone(const std::string& newName);

	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const cObject_Model& val);

	static std::string ShapeTypeToString(cObject_Model::eShapeTypes in);
	static cObject_Model::eShapeTypes StringToShapeType(std::string& in);

	// from iMessageInterface
	// Recieve a message
	virtual bool RecieveMessage(const iMessage& message);

	// Recieve a message and reply
	virtual bool RecieveAndRespond(const iMessage& in, iMessage& reply);

public:			// TODO - Hack - We need this public for old code since it replaces cGameObject.h

	friend class cObjectManager_Model;
	// Used to draw this mesh

	// Values that we can assign and then look for them
	unsigned int friendlyIDNumber;
	std::string friendlyName;

	glm::vec3  positionXYZ;
	glm::vec3  rotationXYZ;
	float scale;

	glm::mat4 matWorld;			// Calculated - Not loaded from XML

	glm::vec4  objectColourRGBA;

	// Likely want this now:
	glm::vec4 diffuseColour;		// Colour of the object
	glm::vec4 specularColour;		// Colour of the HIGHLIGHT + Shininess
									// RGB - colour
									// 4th value (a or w) is the "power"
									// 1.0 to 10,000.0f 


	// Add some physics things
	glm::vec3 velocity;
	glm::vec3 accel;

	// For driving the ship around
	float HACK_speed;
	float HACK_AngleAroundYAxis;		// Angle, around the y axis


	// If the object has an inverse mass of 0.0
	//	then it's not updated by the physics code
	float bounce = 1.0;			// bounce percentage
	float inverseMass;	// 0.0f = Doesn't move

	//bool bIsDynamic;

	// We could contain another class or struct with the phsyics stuff
	// or we could use this type to determine what we need to check.
	eShapeTypes physicsShapeType;
	// 
	glm::vec3 AABB_min, AABB_max;
	float SPHERE_radius;

	// Won't be lit, and is wireframe
	bool isWireframe;
	glm::vec4 debugColour;

	bool disableDepthBufferTest;
	bool disableDepthBufferWrite;
};
