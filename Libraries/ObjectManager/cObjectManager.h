#pragma once
#include "iObjectManager.h"

class cObjectManager_impl;
class cObjectManager;

class cObjectManager : public iObjectManager
{
public:
	cObjectManager();
	virtual ~cObjectManager() {}

	// Root Node of XML document which has assets
	virtual void LoadObjects(rapidxml::xml_node<>* parent);

	// Retrieve the item information
	virtual iObjectManager::iObject_map* GetObjects(const std::string& name);

	// Write an object to the XML file
	virtual void SaveObject(iObject* inObject, rapidxml::xml_node<>* parent);

	iObject* FindObjectByName(const std::string& objectName);

	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const cObjectManager& val);
private:
	virtual void ResolveAlias();			// Don't expose this

};
