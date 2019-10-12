#pragma once
#include "iObjectManager.h"

class cObjectManager_Image :
	public iObjectManager
{
private:
	cObjectManager_Image();
	virtual ~cObjectManager_Image();

	// Root Node of XML document which has assets
	virtual void LoadObjects(rapidxml::xml_node<>* parent);

	// Retrieve the item information
	virtual iObjectManager::iObject_map* GetObjects(const std::string& node);

	// Write an object to the XML file
	virtual void SaveObject(iObject* inObject, rapidxml::xml_node<>* parent) { assert(false); };

	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const cObjectManager_Image& val);

	friend class cObjectManager_impl;
private:
	iObject_map m_map_objects;

};

