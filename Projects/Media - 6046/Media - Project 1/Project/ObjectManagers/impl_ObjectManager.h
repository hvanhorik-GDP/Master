#pragma once

#include "iObjectManager.h"
#include <map>
#include <string>

class cAssetManager;

class impl_ObjectManager : public iObjectManager
{
public:
	impl_ObjectManager();
	virtual ~impl_ObjectManager() final;

	// Root Node of XML document which has assets
	virtual void LoadObjects(rapidxml::xml_node<>* parent, cAssetManager* assetManager);
	iObjectManager* GetObjectManager(const std::string& name);
	friend std::ostream& operator<<(std::ostream& stream, const impl_ObjectManager& val);
protected:
	typedef std::map<std::string, iObjectManager*>  mapObjectManagers;
	mapObjectManagers m_ObjectManagers;
};

