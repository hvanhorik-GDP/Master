#pragma once

#include "AssetItems/iItem.h"

// A way to pass items around
#include <ostream>

#pragma comment (lib, "ObjectItems.lib")

class iObject
{
public:

	// I don't think these are used
	enum eObjectType
	{
		eUnknown,
		eAudio,
		eCamera,
		eChannel,
		eChannelControl,
		eChannelGroup,
		eDSP,
		eFont,
		eGroup,
		eLight,
		eImage,
		eModel,
		eParticle,
		eParticleEmitter,
		ePhysics,
		eTexture,
		eVideo,
		eWindow,
		eWorld,
		eMax = eWorld
	};

	iObject() {};
	virtual ~iObject() {}

	// objects can clone themselves
	virtual iObject* Clone(const std::string& newName) = 0;

	virtual bool IsObjectLocked() const = 0;
	virtual const std::string& GetType() const = 0;
	virtual const std::string& GetName() const = 0;
	virtual const std::string& GetAssetID() const = 0;

	virtual void SetParentObject(iObject* in) = 0;
	virtual iObject* GetParentObject() const = 0;

	virtual bool IsVisable() const = 0;
	virtual void SetVisable(bool to) = 0;

	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const iObject& val);
};
