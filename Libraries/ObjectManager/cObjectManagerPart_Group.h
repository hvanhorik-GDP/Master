#pragma once

#include "iObjectManagerPart.h"

class cObjectManagerPart_Group: public iObjectManagerPart
{
public:
	cObjectManagerPart_Group();
	virtual ~cObjectManagerPart_Group();

	virtual bool HandleProperty(	iObject* object, 
									const std::string& type, 
									const std::string& name, 
									const std::string& value);

	// Saves all of the properties to the xml file
	virtual void SaveProperties(	iObject* object, 
									rapidxml::xml_node<>* node);

	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const iObjectManagerPart& val);
};

