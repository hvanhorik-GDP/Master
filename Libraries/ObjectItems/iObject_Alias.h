#pragma once


#include <map>
#include <string>

class iObject;

class iObject_Alias
{
public:
	typedef std::map<std::string, iObject*> mapObjectsInAlias;

	iObject_Alias() {};				// Get's filled in by physics
	virtual ~iObject_Alias() {};

	// objects can clone themselves (We don't do it)
	virtual void Copy_iObject_Alias(const iObject_Alias& from) = 0;

	// Add a new child to the group
	virtual void AddChildObject(iObject* child) = 0;

	// Retrieve the list of children
	virtual iObject_Alias::mapObjectsInAlias& GetObjectsInAlias() = 0;

	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const iObject_Alias& val);
};

