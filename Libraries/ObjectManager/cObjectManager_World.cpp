#include "cObjectManager_World.h"
#include "ObjectItems/cObject_World.h"
#include "GameLibrary/Object.h"
#include "GameLibrary/Objects.h"
#include "GameLibrary/Properties.h"
#include "Utilities/cFormat.h"
#include "ObjectManager/cObjectManager.h"
#include "cObjectManagerPart_Common.h"
#include "cObjectManagerPart_Alias.h"

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

	auto object = new cObject_World();
	cObjectManagerPart_Common::LoadCommon(object, node);

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

			if (cObjectManagerPart_Common().HandleProperty(object, type, name, value))
				continue;
			else if (cObjectManagerPart_Alias().HandleProperty(object, type, name, value))
				continue;

			if (name == "cameraEye")
				object->cameraEye = cFormat::LoadVec3(value);
			else if (name == "cameraTarget")
				object->cameraTarget = cFormat::LoadVec3(value);
			else if (name == "upVector")
				object->upVector = cFormat::LoadVec3(value);
			else if (name == "windowWidth")
				object->windowWidth = cFormat::LoadInt(value);
			else if (name == "windowHeight")
				object->windowHeight = cFormat::LoadInt(value);
			else if (name == "cameraNearClipping")
				object->cameraNearClipping = cFormat::LoadFloat(value);
			else if (name == "cameraFarClipping")
				object->cameraFarClipping = cFormat::LoadFloat(value);

			// Some debug stuff
			else if (name == "physicsStepOn")
				object->physicsStepOn = cFormat::LoadBool(value);
			else if (name == "physicsCollisionOn")
				object->physicsCollisionOn = cFormat::LoadBool(value);
			else if (name == "debugRenderer")
				object->debugRenderer = cFormat::LoadBool(value);
			else if (type == "alias")
				object->m_mapObjects[name] = NULL;		// Just note the name (This gets filled in post processing)
			else
			{
				std::cout
					<< __FILE__
					<< "Unkown property found: "
					<< " Name = " << name
					<< " Type = " << type
					<< " Value = " << value << std::endl;
			}
		} // if (std::string(property->name()) == std::string("Property"))
	} // for (auto property = node->first_node("Property");

	cObjectManagerPart_Common::AddToMap(m_map_objects, object, __FILE__);
}

void cObjectManager_World::SaveObject(iObject* inObject, rapidxml::xml_node<>* parent)
{
	auto object = cObjectManagerPart_Common::AddObjectToMap(m_map_objects, inObject, parent);
	assert(object);

	cObject_World* writeObject = dynamic_cast<cObject_World*>(object);
	assert(writeObject);

	auto node = writeObject->GetNode();
	if (node)
	{
		cObjectManagerPart_Common().SaveProperties(writeObject, node);
		cObjectManagerPart_Alias().SaveProperties(writeObject, node);

		gamelibrary::Object libObject(node);

		// Write all of the properties
		libObject.AddProperty("cameraEye", "vec3", cFormat::PackVec3(writeObject->cameraEye));
		libObject.AddProperty("cameraTarget", "vec3", cFormat::PackVec3(writeObject->cameraTarget));
		libObject.AddProperty("upVector", "vec3", cFormat::PackVec3(writeObject->upVector));
		libObject.AddProperty("windowWidth", "float", cFormat::PackInt(writeObject->windowWidth));
		libObject.AddProperty("windowHeight", "float", cFormat::PackInt(writeObject->windowHeight));
		libObject.AddProperty("cameraNearClipping", "float", cFormat::PackFloat(writeObject->cameraNearClipping));
		libObject.AddProperty("cameraFarClipping", "float", cFormat::PackFloat(writeObject->cameraFarClipping));
		libObject.AddProperty("physicsStepOn", "bool", cFormat::PackBool(writeObject->physicsStepOn));
		libObject.AddProperty("physicsCollisionOn", "bool", cFormat::PackBool(writeObject->physicsCollisionOn));

		// Some debug stuff
		libObject.AddProperty("debugRenderer", "bool", cFormat::PackBool(writeObject->debugRenderer));
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
