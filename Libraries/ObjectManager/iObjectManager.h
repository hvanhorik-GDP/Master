#pragma once

#include <ostream>
#include <rapidxml/rapidxml.hpp>
#include "ObjectItems/iObject.h"
#include <map>


// INFO6044 - iObjectManager reads in all of the for the object types from the xml file
// It is a "singleton", "Pimpl",  "Abstract Factory", "Builder"
// It reads all of it's information from the gamlibary XML file
// See cObjectManage, cObjectManager_imple and each of the types and each of the different types
// This will fill load in the "ObjectItems/iObject.h"
//
// objects point to assets (or not) depending on the type. for Models all of assets but lights 
// do not

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

