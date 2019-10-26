#pragma once
#include "cObject_Common.h"

#include <map>

class cObject_World : public cObject_Common			// The world is just like a group
{
public:
	typedef std::map<std::string, iObject*> mapObjectsInWorld;

	cObject_World() {};				// Get's filled in by physics

	cObject_World(const std::string& type,
		const std::string& name,
		const std::string& asset_id,
		rapidxml::xml_node<>* node);
	virtual ~cObject_World();

	virtual iObject* Clone(const std::string& newName) final;


	virtual void IntegrationStep(float deltaTime);

	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const cObject_World& val);

	// from iMessageInterface
	// Recieve a message
	virtual bool RecieveMessage(const iMessage& message);

	// Recieve a message and reply
	virtual bool RecieveAndRespond(const iMessage& in, iMessage& reply);

private:
	//TODO - HACK - PUBLIC
public:
	friend class cObjectManager_World;
	friend class cLightManager;

	glm::vec3 cameraEye;
	glm::vec3 cameraTarget;
	glm::vec3 upVector;
	bool debugRenderer;
	int windowWidth;
	int windowHeight;


	mapObjectsInWorld m_mapObjects;
};

