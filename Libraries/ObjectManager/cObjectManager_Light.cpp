#include "cObjectManager_Light.h"
#include "ObjectItems/cObject_Light.h"
#include "GameLibrary/Object.h"
#include "GameLibrary/Objects.h"
#include "GameLibrary/Properties.h"
#include "AssetManager/cAssetManager.h"
#include "Utilities/cFormat.h"

#include <iostream>

cObjectManager_Light::cObjectManager_Light()
{
}

cObjectManager_Light::~cObjectManager_Light()
{
}

// Root Node of XML document which has assets
void cObjectManager_Light::LoadObjects(rapidxml::xml_node<>* node)
{
	gamelibrary::Object_type objectType(node);
	gamelibrary::Object_name objectName(node);
	gamelibrary::Object_asset_id objectAssetID(node);

	auto object = new cObject_Light(
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
			if (name == "shaderEntry")
				object->shaderEntry = value;

			else if (name == "lightType")
				object->lightType = cObject_Light::StringToLightType(value);
			else if (name == "positionXYZ")
				object->positionXYZ = cFormat::LoadVec3(value);
			else if (name == "diffuseColour")
				object->diffuseColour = cFormat::LoadVec4(value);
			else if (name == "specularColour")
				object->specularColour = cFormat::LoadVec4(value);
			else if (name == "constantAttenuation")
				object->constantAttenuation = cFormat::LoadFloat(value);
			else if (name == "linearAttenuation")
				object->linearAttenuation = cFormat::LoadFloat(value);
			else if (name == "quadradicAttenuation")
				object->quadradicAttenuation = cFormat::LoadFloat(value);
			else if (name == "distanceCutOff")
				object->distanceCutOff = cFormat::LoadFloat(value);

			// Spotlight stuff
			else if (name == "spotInnerangle")
				object->spotInnerangle = cFormat::LoadFloat(value);
			else if (name == "spotOuterangle")
				object->spotOuterangle = cFormat::LoadFloat(value);
			else if (name == "direction")
				object->direction = cFormat::LoadVec3(value);

		
			// Some debug stuff
			else if (name == "DebugSpheres")
				object->DebugSpheres = cFormat::LoadBool(value);
			else if (name == "isVisible")
				object->m_isVisable = cFormat::LoadBool(value);
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
		m_map_objects[objectName.GetValue()] = object;;
}

// Write an object to the XML file
void cObjectManager_Light::SaveObject(iObject* inObject, rapidxml::xml_node<>* parent)
{
	assert(parent);
	assert(inObject);
	auto object = dynamic_cast<cObject_Light*>(inObject);
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
		writeObject = dynamic_cast<cObject_Light*>(m_map_objects[object->GetName()]);
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
	libObject.AddProperty("shaderEntry", "string", object->shaderEntry);
	libObject.AddProperty("lightType", "enum", cObject_Light::LightTypeToString(object->lightType));
	libObject.AddProperty("diffuseColour", "vec4", cFormat::PackVec4(object->diffuseColour));
	libObject.AddProperty("specularColour", "vec4", cFormat::PackVec4(object->specularColour));
	libObject.AddProperty("constantAttenuation", "float", cFormat::PackFloat(object->constantAttenuation));
	libObject.AddProperty("linearAttenuation", "float", cFormat::PackFloat(object->linearAttenuation));
	libObject.AddProperty("quadradicAttenuation", "float", cFormat::PackFloat(object->quadradicAttenuation));
	libObject.AddProperty("distanceCutOff", "float", cFormat::PackFloat(object->distanceCutOff));

	// Spot Light only
	libObject.AddProperty("spotInnerangle", "float", cFormat::PackFloat(object->spotInnerangle));
	libObject.AddProperty("spotOuterangle", "float", cFormat::PackFloat(object->spotOuterangle));
	libObject.AddProperty("direction", "vec3", cFormat::PackVec3(object->direction));

	// Debug
	libObject.AddProperty("isVisible", "float", cFormat::PackBool(object->m_isVisable));
	libObject.AddProperty("DebugSpheres", "float", cFormat::PackBool(object->DebugSpheres));

}

// Retrieve the item information
iObjectManager::iObject_map* cObjectManager_Light::GetObjects(const std::string& name)
{
	return &m_map_objects;
}

// For debugging purposes - dumps the contents in human readable form
std::ostream& operator<<(std::ostream& stream, const cObjectManager_Light& val)
{
	return stream;
}

void cObjectManager_Light::ResolveAlias()
{
	//	cObjectManager manager;
	//	for (auto group : m_map_objects)
	//	{
	//		auto object = dynamic_cast<cObject_World*>(group.second);
	//		assert(object);
	//
	//		for (auto alias : object->m_mapObjects)
	//		{
	//			iObject* theAlias = manager.FindObjectByName(alias.first);
	//			object->m_mapObjects[alias.first] = theAlias;
	//			// TODO - No backpointer to world for now.
	////			theAlias->SetParentObject(object);		// Point back to the parent group
	//		}
	//	}
}
