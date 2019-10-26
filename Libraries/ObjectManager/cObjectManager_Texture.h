#pragma once
#include "iObjectManager.h"

class cObjectManager_Texture :
	public iObjectManager
{
private:
	cObjectManager_Texture();
	virtual ~cObjectManager_Texture();

	// Root Node of XML document which has assets
	virtual void LoadObjects(rapidxml::xml_node<>* node) final;

	// Retrieve the item information
	virtual iObjectManager::iObject_map* GetObjects(const std::string& name) final;

	// Write an object to the XML file
	virtual void SaveObject(iObject* inObject, rapidxml::xml_node<>* parent) final;

	// Resolve any aliases
	virtual void ResolveAlias() final;

	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const cObjectManager_Texture& val);

private:
	friend class cObjectManager_impl;

	iObject_map m_map_objects;

};

