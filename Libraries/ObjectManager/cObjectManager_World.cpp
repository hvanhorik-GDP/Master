#include "cObjectManager_World.h"
#include "ObjectItems/cObject_World.h"
#include "GameLibrary/Object.h"
#include "GameLibrary/Objects.h"
#include "GameLibrary/Properties.h"
#include "Utilities/cFormat.h"
#include "ObjectManager/cObjectManager.h"

#include <iostream>

cObjectManager_World::cObjectManager_World()
{
}

cObjectManager_World::~cObjectManager_World()
{
}

// Root Node of XML document which has assets
void cObjectManager_World::LoadObjects(rapidxml::xml_node<>* node)
{

	gamelibrary::Object_type objectType(node);
	gamelibrary::Object_name objectName(node);
	gamelibrary::Object_asset_id objectAssetID(node);


	auto object = new cObject_World(
		objectType.GetValue(),
		objectName.GetValue(),
		objectAssetID.GetValue(),
		node);

	// Read all of the properties
	for (auto property = node->first_node("Property");
		property;
		property = property->next_sibling())
	{
		if (std::string(property->name()) == std::string("Property"))
		{
			gamelibrary::Property_type PropertyType(property);
			gamelibrary::Property_name PropertyName(property);
			gamelibrary::Property_value PropertyValue(property);
			std::string type = PropertyType.GetValue();
			std::string name = PropertyName.GetValue();
			std::string value = PropertyValue.GetValue();

			if (name == "cameraEye")
				object->cameraEye = cFormat::LoadVec3(value);
			if (name == "cameraTarget")
				object->cameraTarget = cFormat::LoadVec3(value);
			if (name == "upVector")
				object->upVector = cFormat::LoadVec3(value);
			if (name == "windowWidth")
				object->windowWidth = cFormat::LoadInt(value);
			if (name == "windowHeight")
				object->windowHeight = cFormat::LoadInt(value);

			// Some debug stuff
			else if (name == "debugRenderer")
				object->debugRenderer = cFormat::LoadBool(value);
			else if (type == "alias")
				object->m_mapObjects[name] = NULL;		// Just note the name (This gets filled in post processing)
			else
			{
				std::cout
					<< "Unkown property found: "
					<< " Name = " << name
					<< " Type = " << type
					<< " Value = " << value << std::endl;
			}
		} // if (std::string(property->name()) == std::string("Property"))
	} // for (auto property = node->first_node("Property");

	// Save all of these objects
	if (m_map_objects.find(objectName.GetValue()) != m_map_objects.end())
	{
		// Duplicate
		std::cout << "duplicate object found: "
			<< " Name : " << objectName.GetValue()
			<< " Value: " << objectType.GetValue()
			<< " AssetID: " << objectAssetID.GetValue() << std::endl;
	}
	else
		m_map_objects[objectName.GetValue()] = object;
}

void cObjectManager_World::SaveObject(iObject* inObject, rapidxml::xml_node<>* parent)
{
	assert(parent);
	assert(inObject);
	auto object = dynamic_cast<cObject_World*>(inObject);
	assert(object);

	auto writeObject = object;

	// Insert it into the object array
	// Check to see if the node already exits
	if (m_map_objects.find(object->GetName()) != m_map_objects.end())
	{
		// Duplicate
		std::cout << "duplicate object found: "
			<< " Name : " << object->GetName()
			<< " Type: " << object->GetType()
			<< " AssetID: " << object->GetAssetID() << std::endl;

		// Overwrite what we have - This will copy the new values into the old entries
		writeObject = dynamic_cast<cObject_World*>(m_map_objects[object->GetName()]);
	}
	else
		m_map_objects[object->GetName()] = object;

	auto node = writeObject->GetNode();
	if (!node)
	{
		// If no node then create and insert one
		gamelibrary::Objects parentObject(parent);
		node = parentObject.Insert("Object", "");
		writeObject->SetNode(node);
	}

	gamelibrary::Object libObject(node);
	gamelibrary::Object_name objName(node);
	objName.SetValue(writeObject->GetName());

	gamelibrary::Object_type objType(node);
	objType.SetValue(writeObject->GetType());

	gamelibrary::Object_asset_id objAssetID(node);
	objAssetID.SetValue(writeObject->GetAssetID());

	// Write all of the properties
	libObject.AddProperty("cameraEye", "vec3", cFormat::PackVec3(object->cameraEye));
	libObject.AddProperty("cameraTarget", "vec3", cFormat::PackVec3(object->cameraTarget));
	libObject.AddProperty("upVector", "vec3", cFormat::PackVec3(object->upVector));
	libObject.AddProperty("windowWidth", "float", cFormat::PackInt(object->windowWidth));
	libObject.AddProperty("windowHeight", "float", cFormat::PackInt(object->windowHeight));

	// Some debug stuff
	libObject.AddProperty("debugRenderer", "bool", cFormat::PackBool(object->debugRenderer));
	for (auto alias : object->m_mapObjects)
	{
		libObject.AddProperty(alias.first, "alias", alias.first);
	}
}

// Retrieve the item information
iObjectManager::iObject_map* cObjectManager_World::GetObjects(const std::string& name)
{
	return &m_map_objects;
}

// For debugging purposes - dumps the contents in human readable form
std::ostream& operator<<(std::ostream& stream, const cObjectManager_World& val)
{
	return stream;
}


void cObjectManager_World::ResolveAlias()
{
	cObjectManager manager;
	for (auto group : m_map_objects)
	{
		auto object = dynamic_cast<cObject_World*>(group.second);
		assert(object);

		for (auto alias : object->m_mapObjects)
		{
			iObject* theAlias = manager.FindObjectByName(alias.first);
			object->m_mapObjects[alias.first] = theAlias;
			// TODO - No backpointer to world for now.
//			theAlias->SetParentObject(object);		// Point back to the parent group
		}
	}
}
