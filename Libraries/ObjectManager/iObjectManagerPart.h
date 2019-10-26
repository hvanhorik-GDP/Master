#pragma once

#include <rapidxml/rapidxml.hpp>
#include "ObjectItems/iObject.h"
#include <map>
#include <ostream>

class iObjectManagerPart
{
public:
	iObjectManagerPart() {}
	virtual ~iObjectManagerPart() {}

	virtual bool HandleProperty(	iObject* object, 
									const std::string& type, 
									const std::string& name, 
									const std::string& value) = 0;

	// Saves all of the properties to the xml file
	virtual void SaveProperties(	iObject* object, 
									rapidxml::xml_node<>* node) = 0;

	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const iObjectManagerPart& val);
};

