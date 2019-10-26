#include "cObjectManager_ParticleEmitter.h"
#include "ObjectItems/cObject_ParticleEmitter.h"
#include "GameLibrary/Object.h"
#include "GameLibrary/Objects.h"
#include "GameLibrary/Properties.h"
#include "Utilities/cFormat.h"
#include "ObjectManager/cObjectManager.h"

#include <iostream>

cObjectManager_ParticleEmitter::cObjectManager_ParticleEmitter()
{
}

cObjectManager_ParticleEmitter::~cObjectManager_ParticleEmitter()
{
}

// Root Node of XML document which has assets
void cObjectManager_ParticleEmitter::LoadObjects(rapidxml::xml_node<>* node)
{

	gamelibrary::Object_type objectType(node);
	gamelibrary::Object_name objectName(node);
	gamelibrary::Object_asset_id objectAssetID(node);


	auto object = new cObject_ParticleEmitter(
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

			//if (name == "cameraEye")
			//	object->cameraEye = cFormat::LoadVec3(value);
			//else if (name == "cameraTarget")
			//	object->cameraTarget = cFormat::LoadVec3(value);
			//else if (name == "upVector")
			//	object->upVector = cFormat::LoadVec3(value);
			//else if (name == "windowWidth")
			//	object->windowWidth = cFormat::LoadInt(value);
			//else if (name == "windowHeight")
			//	object->windowHeight = cFormat::LoadInt(value);

			//// Some debug stuff
			//else if (name == "debugRenderer")
			//	object->debugRenderer = cFormat::LoadBool(value);
			//glm::vec3 m_acceleration;
			//glm::vec3 m_location;

			//vec_Particles m_vec_pParticles;

			//// Saved for when we call Step()
			//// These are set when we call Initialize();
			//glm::vec3 m_minVelocity;
			//glm::vec3 m_maxVelocity;
			//glm::vec3 m_minDeltaPosition;
			//glm::vec3 m_maxDeltaPosition;
			//float m_minLifeSeconds;
			//float m_maxLifeSeconds;
			//int m_minParticlesPerFrame;
			//int m_maxParticlesPerFrame;
			//bool m_initialized;
//			else
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
		m_map_objects[objectName.GetValue()] = object;
}

void cObjectManager_ParticleEmitter::SaveObject(iObject* inObject, rapidxml::xml_node<>* parent)
{
	assert(parent);
	assert(inObject);
	auto object = dynamic_cast<cObject_ParticleEmitter*>(inObject);
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
		writeObject = dynamic_cast<cObject_ParticleEmitter*>(m_map_objects[object->GetName()]);
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

	//glm::vec3 m_acceleration;
	//glm::vec3 m_location;

	//vec_Particles m_vec_pParticles;

	//// Saved for when we call Step()
	//// These are set when we call Initialize();
	//glm::vec3 m_minVelocity;
	//glm::vec3 m_maxVelocity;
	//glm::vec3 m_minDeltaPosition;
	//glm::vec3 m_maxDeltaPosition;
	//float m_minLifeSeconds;
	//float m_maxLifeSeconds;
	//int m_minParticlesPerFrame;
	//int m_maxParticlesPerFrame;
	//bool m_initialized;
// Write all of the properties
	//libObject.AddProperty("cameraEye", "vec3", cFormat::PackVec3(object->cameraEye));
	//libObject.AddProperty("cameraTarget", "vec3", cFormat::PackVec3(object->cameraTarget));
	//libObject.AddProperty("upVector", "vec3", cFormat::PackVec3(object->upVector));
	//libObject.AddProperty("windowWidth", "float", cFormat::PackInt(object->windowWidth));
	//libObject.AddProperty("windowHeight", "float", cFormat::PackInt(object->windowHeight));

}

// Retrieve the item information
iObjectManager::iObject_map* cObjectManager_ParticleEmitter::GetObjects(const std::string& name)
{
	return &m_map_objects;
}

// For debugging purposes - dumps the contents in human readable form
std::ostream& operator<<(std::ostream& stream, const cObjectManager_ParticleEmitter& val)
{
	return stream;
}


void cObjectManager_ParticleEmitter::ResolveAlias()
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
