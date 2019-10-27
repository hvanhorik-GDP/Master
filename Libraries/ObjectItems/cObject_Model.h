#pragma once

#include "cObject_Common.h"
#include "cObject_3d.h"
#include "cObject_Physics.h"

#include <glm/glm.hpp>

#include <string>
#include <map>

class cObject_Model 
	: public cObject_Common							// Need common items
	, public cObject_3d								// This is a 3d Object
	, public cObject_Physics						// and physics applies to it
{
public:

	cObject_Model();

	virtual ~cObject_Model();

	virtual iObject* Clone(const std::string& newName) final;

	virtual void IntegrationStep(float deltaTime) final;

	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const cObject_Model& val);

	//static std::string ShapeTypeToString(cObject_Model::eShapeTypes in);
	//static cObject_Model::eShapeTypes StringToShapeType(std::string& in);

	// Recieve a message
	virtual bool RecieveMessage(const iMessage& message) final;
	// Recieve a message and reply
	virtual bool RecieveAndRespond(const iMessage& in, iMessage& reply) final; 

public:			// TODO - Hack - We need this public for old code since it replaces cGameObject.h

	friend class cObjectManager_Model;
	// Used to draw this mesh

	glm::vec4  objectColourRGBA;	// Probably obsolete with textures
	glm::vec4 diffuseColour;		// Colour of the object
	glm::vec4 specularColour;		// Colour of the HIGHLIGHT + Shininess
									// RGB - colour
									// 4th value (a or w) is the "power"
									// 1.0 to 10,000.0f 


	// Won't be lit, and is wireframe
	bool isWireframe;
	glm::vec4 debugColour;

	bool disableDepthBufferTest;
	bool disableDepthBufferWrite;
	// We are being tracked by the camera
	// TODO - HACK - This needs to be moved into a Camera Object
	// TODO - I don't have time now to do it
	bool debugHackTrackingMe = false;
};
