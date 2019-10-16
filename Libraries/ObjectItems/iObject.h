#pragma once

#include "AssetItems/iItem.h"

// A way to pass items around
#include <ostream>

#pragma comment (lib, "ObjectItems.lib")

class iObject
{
public:
	enum eObjectType
	{
		eUnknown,
		eGroup,
		eAudio,
		eModel,
		ePhysics,
		eImage,
		eLight,
		eFont, 
		eAlias,
		eWorld,
		eMax = eWorld
	};

	iObject() {};
	virtual ~iObject() {}

	virtual const std::string& GetType() const = 0;

	// Information about the object
	virtual const std::string& GetName() const = 0;
	virtual const std::string& GetAssetID() const = 0;
	virtual iItem* GetItem() const = 0;

	virtual iObject* Clone(const std::string& newName) = 0;
	virtual iObject* GetParentObject() const = 0;
	virtual void SetParentObject(iObject* in) = 0;

	virtual void IntegrationStep(float deltaTime) = 0;
	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const iObject& val);
};
