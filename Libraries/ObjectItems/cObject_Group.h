#pragma once
#include "cObject_Common.h"
#include <map>

class cObject_Group : public cObject_Common
{
public:
	typedef std::map<std::string, iObject*> mapObjectsInGroup;
	// This structure matches the file, so that our life is
	//   simpler and happier, and we all get along.

	cObject_Group() {};				// Get's filled in by physics

	cObject_Group(const std::string& type,
		const std::string& name,
		const std::string& asset_id,
		rapidxml::xml_node<>* node);
	virtual ~cObject_Group();

	virtual void IntegrationStep(float deltaTime) final;

	virtual void AddChildObject(iObject* child);

	cObject_Group::mapObjectsInGroup& GetObjectsInGroup();
	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const cObject_Group& val);

private:
public:			// TODO - hack
	friend class cObjectManager_Group;

	glm::vec3  positionXYZ;
	glm::vec3  rotationXYZ;
	float scale;
	// Add some physics things
	glm::vec3 velocity;
	glm::vec3 accel;
	bool isVisible;

	mapObjectsInGroup m_mapObjects;
};

