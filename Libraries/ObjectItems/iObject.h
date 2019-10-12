#pragma once

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
	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const iObject& val);
};
