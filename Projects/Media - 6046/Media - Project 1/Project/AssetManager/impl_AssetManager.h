#pragma once
#include "iAssetManager.h"
#include <map>
#include <string>

class impl_AssetManager : public iAssetManager
{
public:
	impl_AssetManager();
	virtual ~impl_AssetManager() final;

	// Root Node of XML document which has assets
	virtual void LoadAssets(rapidxml::xml_node<>* parent);
	iAssetManager* GetAssetManager(const std::string& name);
	friend std::ostream& operator<<(std::ostream& stream, const impl_AssetManager& val);
protected:
	typedef std::map<std::string, iAssetManager*>  mapManagers;
	mapManagers m_Managers;
};

