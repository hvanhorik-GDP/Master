
#include "cObjectManagerPart_Common.h"
#include "GameLibrary/Objects.h"
#include "GameLibrary/Object.h"
#include "ObjectItems/cObject_Common.h"
#include "AssetManager/cAssetManager.h"

#include "Utilities/cFormat.h"

#include <iostream>
#include <ostream>

cObjectManagerPart_Common::cObjectManagerPart_Common()
{
}


cObjectManagerPart_Common::~cObjectManagerPart_Common()
{
}	

// Saves all of the properties to the xml file
bool cObjectManagerPart_Common::HandleProperty(iObject* object,
	const std::string& type,
	const std::string& name,
	const std::string& value)
{
	cObject_Common* obj = dynamic_cast<cObject_Common*>(object);
	assert(obj);
	if (name == "isVisible")
		obj->m_isVisable = cFormat::LoadBool(value);
	else if (name == "isObjectLocked")
		obj->m_isObjectLocked = cFormat::LoadBool(value);
	else
		return false;
	return true;
}


// Saves all of the properties to the xml file
void cObjectManagerPart_Common::SaveProperties(iObject* object,
	rapidxml::xml_node<>* node)
{
	cObject_Common* obj = dynamic_cast<cObject_Common*>(object);
	assert(obj);
	gamelibrary::Object libObject(node);

	libObject.AddProperty("isVisible", "bool", cFormat::PackBool(obj->m_isVisable));
	libObject.AddProperty("isObjectLocked", "bool", cFormat::PackBool(obj->m_isObjectLocked));
}

iObject* cObjectManagerPart_Common::AddObjectToMap(
	iObjectManager::iObject_map& theMap,
	iObject* inObject,
	rapidxml::xml_node<>* parent)
{
	assert(inObject);
	cObject_Common* commonObject = dynamic_cast<cObject_Common*>(inObject);
	assert(commonObject);

	cObject_Common* writeObject = commonObject;

	// Insert it into the object array
	// Check to see if the node already exits
	if (theMap.find(inObject->GetName()) != theMap.end())
	{
		LogDuplicateEntry(__FILE__, commonObject->GetName(), commonObject->GetType(), commonObject->GetAssetID());

		// Overwrite what we have - This will copy the new values into the old entries
		writeObject = dynamic_cast<cObject_Common*>(theMap[commonObject->GetName()]);
		assert(writeObject);
	}
	else
		theMap[commonObject->GetName()] = commonObject;

	std::cout << "TODO - check for null parent" << std::endl;

	auto node = writeObject->GetNode();
	if (!node)
	{
		if (parent)
		{
			// If we have  parent, we want to add this to the database
			// else we will leave the node blacnk and it won't get inserted.
			// If no node then create and insert one
			gamelibrary::Objects parentObject(parent);
			node = parentObject.Insert("Object", "");
			writeObject->SetNode(node);
		}
	}

	if (node)
	{
		gamelibrary::Object libObject(node);
		gamelibrary::Object_name objName(node);
		objName.SetValue(writeObject->GetName());

		gamelibrary::Object_type objType(node);
		objType.SetValue(writeObject->GetType());

		gamelibrary::Object_asset_id objAssetID(node);
		objAssetID.SetValue(writeObject->GetAssetID());
	}

	return writeObject;
}


void cObjectManagerPart_Common::AddToMap(
	iObjectManager::iObject_map& theMap,
	iObject* object,
	const std::string& file
)
{
	// Save all of these objects
	if (theMap.find(object->GetName()) != theMap.end())
	{
		LogDuplicateEntry(file, object->GetName(), object->GetType(), object->GetAssetID());
	}
	else
		theMap[object->GetName()] = object;
}

void cObjectManagerPart_Common::LogDuplicateEntry(
	const std::string& file,
	const std::string& name,
	const std::string& type,
	const std::string& asset_id
)
{
	std::cout << "duplicate object found: "
		<< " File: " << file
		<< " Name: " << name
		<< " Type: " << type
		<< " AssetID: " << asset_id << std::endl;
}

void cObjectManagerPart_Common::LogInvalidProperty(
	const std::string& file,
	const std::string& name,
	const std::string& type,
	const std::string& value
)
{
	std::cout << "duplicate object found: "
		<< " File: " << file
		<< " Name: " << name
		<< " Type: " << type
		<< " Value: " << value << std::endl;

}

 void cObjectManagerPart_Common::LoadCommon(cObject_Common* in, rapidxml::xml_node<>* node)
{
	auto type = gamelibrary::Object_type(node).GetValue();
	auto name = gamelibrary::Object_name(node).GetValue();
	auto asset_id = gamelibrary::Object_asset_id(node).GetValue();

	in->LoadCommon(type, name, asset_id, node);


	// This needs to be moved to common
	iAssetManager::iItems_map* assets = cAssetManager().GetItems("models");
	auto asset = assets->find(asset_id);
	if (asset != assets->end())
	{
		in->m_Item = asset->second;
	}
}