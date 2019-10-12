#pragma once

#include <ostream>
#include <rapidxml/rapidxml.hpp>
#include "ObjectItems/iObject.h"
#include <map>

#pragma comment (lib, "ObjectManager.lib")

class cObjectManager;

class iObjectManager
{
public:
	// Items are stored in a map so they can be looked up by string name
	typedef std::map<std::string, iObject*> iObject_map;

	iObjectManager() {}
	virtual ~iObjectManager() {}

	// Root Node of XML document which has assets
	virtual void LoadObjects(rapidxml::xml_node<>* parent) = 0;

	// Retrieve the item information
	virtual iObjectManager::iObject_map* GetObjects(const std::string& name) = 0;

	// Write an object to the XML file
	virtual void SaveObject(iObject* inObject, rapidxml::xml_node<>* parent = NULL) = 0;

	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const iObjectManager& val);
};

