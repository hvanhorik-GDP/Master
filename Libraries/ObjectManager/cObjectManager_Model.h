#pragma once
#include "iObjectManager.h"

class cObjectManager_Model :
	public iObjectManager
{
private:
	cObjectManager_Model();
	virtual ~cObjectManager_Model();

	// Root Node of XML document which has assets
	virtual void LoadObjects(rapidxml::xml_node<>* node);

	// Retrieve the item information
	virtual iObjectManager::iObject_map* GetObjects(const std::string& name);

	// Write an object to the XML file
	virtual void SaveObject(iObject* inObject, rapidxml::xml_node<>* parent);

	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const cObjectManager_Model& val);

	friend class cObjectManager_impl;
private:
	iObject_map m_map_objects;

};

