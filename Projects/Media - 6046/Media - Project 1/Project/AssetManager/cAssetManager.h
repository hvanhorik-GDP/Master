#pragma once
#include "iAssetManager.h"

class impl_AssetManager;

class cAssetManager : public iAssetManager
{
public:
	cAssetManager();
	virtual ~cAssetManager() {}

	// Root Node of XML document which has assets
	virtual void LoadAssets(rapidxml::xml_node<>* parent);
	iAssetManager* GetAssetManager(const std::string& name);
	friend std::ostream& operator<<(std::ostream& stream, const cAssetManager& val);

protected:
	impl_AssetManager* m_impl_AssetManager;
};