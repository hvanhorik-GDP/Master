#include "cObjectManager_Model.h"
#include "ObjectItems/cObject_Model.h"
#include "GameLibrary/Object.h"
#include "GameLibrary/Properties.h"
#include "GameLibrary/Objects.h"
#include "Utilities/cFormat.h"

// We handle all of these properties
#include "cObjectManagerPart_Common.h"
#include "cObjectManagerPart_Physics.h"
#include "cObjectManagerPart_3d.h"
#include "cObjectManagerPart_Alias.h"


#include "AssetManager/cAssetManager.h"
#include <rapidxml/rapidxml_ext.hpp>

#include <glm/glm.hpp>
#include <iostream>

cObjectManager_Model::cObjectManager_Model()
{
}

cObjectManager_Model::~cObjectManager_Model()
{
}

// Root Node of XML document which has assets
void cObjectManager_Model::LoadObjects(rapidxml::xml_node<>* node)
{
	auto object = new cObject_Model();
	cObjectManagerPart_Common::LoadCommon(object, node);

	// Read all of the properties
	for (auto property = node->first_node("Property");
		property;
		property = property->next_sibling())
	{
		if (std::string(property->name()) == std::string("Property"))
		{
			auto type = gamelibrary::Property_type(property).GetValue();
			auto name = gamelibrary::Property_name(property).GetValue();
			auto value = gamelibrary::Property_value(property).GetValue();

			if (cObjectManagerPart_Common().HandleProperty(object, type, name, value))
				continue;
			if (cObjectManagerPart_3d().HandleProperty(object, type, name, value))
				continue;
			else if (cObjectManagerPart_Physics().HandleProperty(object, type, name, value))
				continue;
			else if (cObjectManagerPart_Alias().HandleProperty(object, type, name, value))
				continue;

			else if (name == "objectColourRGBA")
				object->objectColourRGBA = cFormat::LoadVec4(value);
			else if (name == "diffuseColour")
				object->diffuseColour = cFormat::LoadVec4(value);
			else if (name == "specularColour")
				object->specularColour = cFormat::LoadVec4(value);

			// Some debug stuff
			else if (name == "isWireframe")
				object->isWireframe = cFormat::LoadBool(value);
			else if (name == "debugColour")
				object->debugColour = cFormat::LoadVec4(value);
			else if (name == "disableDepthBufferTest")
				object->disableDepthBufferTest = cFormat::LoadBool(value);
			else if (name == "disableDepthBufferWrite")
				object->disableDepthBufferWrite = cFormat::LoadBool(value);
			else
			{
				cObjectManagerPart_Common::LogInvalidProperty(__FILE__, name, type, value);
			}
		} // if (std::string(property->name()) == std::string("Property"))
	} // for (auto property = node->first_node("Property");

	cObjectManagerPart_Common::AddToMap(m_map_objects, object, __FILE__);
}

void cObjectManager_Model::SaveObject( iObject* inObject, rapidxml::xml_node<>* parent )
{
	auto object = cObjectManagerPart_Common::AddObjectToMap(m_map_objects, inObject, parent);
	assert(object);

	cObject_Model* writeObject = dynamic_cast<cObject_Model*>(object);
	assert(writeObject);

	auto node = writeObject->GetNode();
	if (node)
	{
		cObjectManagerPart_Common().SaveProperties(writeObject, node);
		cObjectManagerPart_3d().SaveProperties(writeObject, node);
		cObjectManagerPart_Physics().SaveProperties(writeObject, node);
		cObjectManagerPart_Alias().SaveProperties(writeObject, node);

		gamelibrary::Object libObject(node);

		// Write all of the properties

		libObject.AddProperty("objectColourRGBA", "vec4", cFormat::PackVec4(writeObject->objectColourRGBA));
		libObject.AddProperty("diffuseColour", "vec4", cFormat::PackVec4(writeObject->diffuseColour));
		libObject.AddProperty("specularColour", "vec4", cFormat::PackVec4(writeObject->specularColour));

		// Some debug stuff
		libObject.AddProperty("isWireframe", "bool", cFormat::PackBool(writeObject->isWireframe));
		libObject.AddProperty("debugColour", "vec4", cFormat::PackVec4(writeObject->debugColour));
		libObject.AddProperty("isVisible", "bool", cFormat::PackBool(writeObject->m_isVisable));
		libObject.AddProperty("disableDepthBufferTest", "bool", cFormat::PackBool(writeObject->disableDepthBufferTest));
		libObject.AddProperty("disableDepthBufferWrite", "bool", cFormat::PackBool(writeObject->disableDepthBufferWrite));
	}
}

// Retrieve the item information
iObjectManager::iObject_map* cObjectManager_Model::GetObjects(const std::string& name)
{
	return &m_map_objects;
}

// For debugging purposes - dumps the contents in human readable form
std::ostream& operator<<(std::ostream& stream, const cObjectManager_Model& val)
{
	return stream;
}

void cObjectManager_Model::ResolveAlias()
{
	cObjectManagerPart_Alias::ResolveAlias(m_map_objects, false);
}
