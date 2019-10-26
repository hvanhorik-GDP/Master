#pragma once

#include "iObjectManagerPart.h"
#include "iObjectManager.h"

class cObjectManagerPart_Common : public iObjectManagerPart
{
public:

	cObjectManagerPart_Common();
	virtual ~cObjectManagerPart_Common();

	virtual bool HandleProperty(iObject* object,
		const std::string& type,
		const std::string& name,
		const std::string& value) final;

	// Saves all of the properties to the xml file
	virtual void SaveProperties(iObject* object,
		rapidxml::xml_node<>* node) final;

	// For debugging purposes - dumps the contents in human readable form


	// Some helper methods
	static void LogInvalidProperty(
		const std::string& file,
		const std::string& name,
		const std::string& type,
		const std::string& value
	);

	static void LogDuplicateEntry(
		const std::string& file,
		const std::string& name,
		const std::string& type,
		const std::string& asset_id
	);

	static void AddToMap(
		iObjectManager::iObject_map& theMap,
		iObject* object,
		const std::string& file,
		const std::string& name,
		const std::string& type,
		const std::string& asset_id
	);

	static iObject* AddObjectToMap(
		iObjectManager::iObject_map& theMap,
		iObject* inObject, 
		rapidxml::xml_node<>* parent);
};

