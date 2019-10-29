#pragma once
#include <ostream>
#include <map>
#include <string>
#include <rapidxml/rapidxml.hpp>

// including Audio/Models/Shaders etc.
// It is a "singleton", "Pimpl",  "Abstract Factory", "Builder"
// It reads all of it's information from the gamlibary XML file
// See cAssetManager, cAssetManager_impl, and each of the different types
// This will fill load in the "AssetItems/iItems.h"

class iItem;


class iAssetManager
{
public:

	// Items are stored in a map so they can be looked up by string name
	typedef std::map<std::string, iItem*> iItems_map;

	iAssetManager() {};
	virtual ~iAssetManager() {}

	// Load assets from XML document
	virtual void LoadAssets(rapidxml::xml_node<>* parent) = 0;

	// Retrieve the item information
	virtual iAssetManager::iItems_map* GetItems(const std::string& name) = 0;

	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const iAssetManager& val);
};