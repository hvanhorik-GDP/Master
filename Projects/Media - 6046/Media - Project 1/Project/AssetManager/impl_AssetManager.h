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
	friend std::ostream& operator<<(std::ostream& stream, const impl_AssetManager& val);

	// Hack now to get at the underlying AssetManagers
	iAssetManager* GetAssetManager(const std::string& name);
protected:
	typedef std::map<std::string, iAssetManager*>  mapAssetManagers;
	mapAssetManagers m_AssetManagers;
};

