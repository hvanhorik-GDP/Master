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

	mapObjectsInAlias m_mapObjects;
	size_t m_originalSize;
};

