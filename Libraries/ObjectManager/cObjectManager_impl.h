#pragma once

#include "iObjectManager.h"
#include <map>
#include <string>

class cAssetManager;

class cObjectManager_impl : public iObjectManager
{
private:
	cObjectManager_impl();
	virtual ~cObjectManager_impl();

	// Root Node of XML document which has assets
	virtual void LoadObjects(rapidxml::xml_node<>* node) final;

	// Retrieve the item information
	virtual iObjectManager::iObject_map* GetObjects(const std::string& name) final;

	// Write an object to the XML file
	virtual void SaveObject(iObject* inObject, rapidxml::xml_node<>* parent) final;

	virtual void ResolveAlias() final;

	iObject* FindObjectByName(const std::string& objectName);

	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const cObjectManager_impl& val);

	typedef std::map<std::string, iObjectManager*>  mapObjectManagers;
	mapObjectManagers m_ObjectManagers;

	friend class cObjectManager;

private:
	void Init();
};

