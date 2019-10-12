#include "cObjectManager_Model.h"
#include "ObjectItems/cObject_Model.h"
#include "GameLibrary/Object.h"
#include "GameLibrary/Properties.h"
#include "GameLibrary/Objects.h"
#include "Utilities/cFormat.h"

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

	gamelibrary::Object_type objectType(node);
	gamelibrary::Object_name objectName(node);
	gamelibrary::Object_asset_id objectAssetID(node);

	auto object = new cObject_Model(objectType.GetValue(), objectName.GetValue(), objectAssetID.GetValue(), node);
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
			if (name == "meshName")
				object->meshName = value;
			else if (name == "positionXYZ")
				object->positionXYZ = cFormat::LoadVec3(value);
			else if (name == "rotationXYZ")
				object->rotationXYZ = cFormat::LoadVec3(value);
			else if (name == "scale")
				object->scale = std::stof(value);
			else if (name == "objectColourRGBA")
				object->objectColourRGBA = cFormat::LoadVec4(value);
			else if (name == "diffuseColour")
				object->diffuseColour = cFormat::LoadVec4(value);
			else if (name == "specularColour")
				object->specularColour = cFormat::LoadVec4(value);
			// Should be in physics
			else if (name == "inverseMass")
				object->inverseMass = cFormat::LoadFloat(value);
			else if (name == "physicsShapeType")
				object->physicsShapeType = cObject_Model::StringToShapeType(value);
			else if (name == "velocity")
				object->velocity = cFormat::LoadVec3(value);
			else if (name == "accel")
				object->accel = cFormat::LoadVec3(value);
			else if (name == "AABB_min")
				object->AABB_min = cFormat::LoadVec3(value);
			else if (name == "AABB_max")
				object->AABB_max = cFormat::LoadVec3(value);
			else if (name == "SPHERE_radius")
				object->SPHERE_radius = cFormat::LoadFloat(value);

			// Some debug stuff
			else if (name == "isWireframe")
				object->isWireframe = cFormat::LoadBool(value);
			else if (name == "debugColour")
				object->debugColour = cFormat::LoadVec4(value);
			else if (name == "isVisible")
				object->isVisible = cFormat::LoadBool(value);
			else if (name == "disableDepthBufferTest")
				object->disableDepthBufferTest = cFormat::LoadBool(value);
			else if (name == "disableDepthBufferWrite")
				object->disableDepthBufferWrite = cFormat::LoadBool(value);
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

void cObjectManager_Model::SaveObject( iObject* inObject, rapidxml::xml_node<>* parent )
{
	assert(parent);
	assert(inObject);
	auto object = dynamic_cast<cObject_Model*>(inObject);
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
		writeObject = dynamic_cast<cObject_Model*>(m_map_objects[object->GetName()]);
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
//	gamelibrary::Properties properties(node);

	libObject.AddProperty("meshName", "string", object->meshName);
	libObject.AddProperty("positionXYZ", "vec3", cFormat::PackVec3(object->positionXYZ));
	libObject.AddProperty("rotationXYZ", "vec3", cFormat::PackVec3(object->rotationXYZ));
	libObject.AddProperty("scale", "float", cFormat::PackFloat(object->scale));

	libObject.AddProperty("objectColourRGBA", "vec4", cFormat::PackVec4(object->objectColourRGBA));
	libObject.AddProperty("diffuseColour", "vec4", cFormat::PackVec4(object->diffuseColour));
	libObject.AddProperty("specularColour", "vec4", cFormat::PackVec4(object->specularColour));

	libObject.AddProperty("inverseMass", "float", cFormat::PackFloat(object->inverseMass));
	libObject.AddProperty("physicsShapeType", "vec3", cObject_Model::ShapeTypeToString(object->physicsShapeType));
	libObject.AddProperty("velocity", "vec3", cFormat::PackVec3(object->velocity));
	libObject.AddProperty("accel", "vec3", cFormat::PackVec3(object->accel));
	libObject.AddProperty("AABB_min", "vec3", cFormat::PackVec3(object->AABB_min));
	libObject.AddProperty("AABB_max", "vec3", cFormat::PackVec3(object->AABB_max));
	libObject.AddProperty("SPHERE_radius", "float", cFormat::PackFloat(object->SPHERE_radius));

	// Some debug stuff
	libObject.AddProperty("isWireframe", "bool", cFormat::PackBool(object->isWireframe));
	libObject.AddProperty("debugColour", "vec4", cFormat::PackVec4(object->debugColour));
	libObject.AddProperty("isVisible", "bool", cFormat::PackBool(object->isVisible));
	libObject.AddProperty("disableDepthBufferTest", "bool", cFormat::PackBool(object->disableDepthBufferTest));
	libObject.AddProperty("disableDepthBufferWrite", "bool", cFormat::PackBool(object->disableDepthBufferWrite));
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

/*
  <Property name = "position" type ="vec3" value="1,2,3"/>
  <Property name = "rotation" type ="vec3" value="1,2,3"/>
  <Property name = "scale" type ="float" value="1.0"/>
  <Property name = "objectColourRGBA" type ="vec4" value="1,2,3,4"/>
  <Property name = "diffuseColour" type ="vec4" value="1,2,3,4"/>
  <Property name = "specularColour" type ="vec4" value="1,2,3,4"/>

  <!-- Physics - should be moved -->
  <Property name = "velocity" type ="vec3" value="1,2,3"/>
  <Property name = "accel" type ="vec3" value="1,2,3"/>
  <Property name = "physicsShapeType" type ="enum" value="UNKNOWN"/>
  <Property name = "AABB_min" type ="vec3" value="1,2,3"/>
  <Property name = "AABB_max" type ="vec3" value="1,2,3"/>
  <Property name = "SPHERE_radius" type ="float" value="1.0"/>

  <!-- Debug -->
  <Property name = "isWireframe" type ="bool" value="false"/>
  <Property name = "debugColour" type ="vec4" value="1,2,3,4"/>
  <Property name = "isWireframe" type ="bool" value="false"/>
  <Property name = "debugColour" type ="vec4" value="1,2,3,4"/>
  <Property name = "isVisible" type ="bool" value="false"/>
  <Property name = "disableDepthBufferTest" type ="bool" value="false"/>
  <Property name = "disableDepthBufferTest" type ="bool" value="false"/>
*/