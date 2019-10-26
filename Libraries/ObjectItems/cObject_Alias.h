#pragma once
#include "iObject_Alias.h"
#include <map>

class cObject_Alias : public iObject_Alias
{
public:

	cObject_Alias();
	virtual ~cObject_Alias();

	// objects can clone themselves (We don't do it)
	virtual void Copy_iObject_Alias(const iObject_Alias& from) final ;

	// Add a child to the group
	virtual void AddChildObject(iObject* child) final;

	virtual iObject_Alias::mapObjectsInAlias& GetObjectsInAlias() final;

	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const cObject_Alias& val);

public:	
	friend class cObjectManager_Alias;

	//glm::vec3  positionXYZ;
	//glm::vec3  rotationXYZ;
	//float scale;
	//// Add some physics things
	//glm::vec3 velocity;
	//glm::vec3 accel;
	//bool isVisible;

	mapObjectsInAlias m_mapObjects;
};

