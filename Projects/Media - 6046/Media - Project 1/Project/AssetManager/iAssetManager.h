#pragma once
#include <ostream>
#include <rapidxml/rapidxml.hpp>

class iAssetManager
{
public:
	iAssetManager() {};
	virtual ~iAssetManager() {}

	// Root Node of XML document which has assets
	virtual void LoadAssets(rapidxml::xml_node<>* parent) = 0;
	friend std::ostream& operator<<(std::ostream& stream, const iAssetManager& val);
};