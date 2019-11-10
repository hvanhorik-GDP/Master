#pragma once

#include "iObjectManagerPart.h"
#include "iObjectManager.h"

class cObjectManagerPart_Alias: public iObjectManagerPart
{
public:
	cObjectManagerPart_Alias();
	virtual ~cObjectManagerPart_Alias();

	virtual bool HandleProperty(	iObject* object, 
									const std::string& type, 
									const std::string& name, 
									const std::string& value);

	// Saves all of the properties to the xml file
	virtual void SaveProperties(	iObject* object, 
									rapidxml::xml_node<>* node);

	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const cObjectManagerPart_Alias& val);

	static void ResolveAlias(iObjectManager::iObject_map& objects, bool pointToParent);
};

