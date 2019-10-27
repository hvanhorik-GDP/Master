#include "cObjectManager_ChannelGroup.h"
#include "ObjectItems/cObject_ChannelGroup.h"
#include "GameLibrary/Object.h"
#include "GameLibrary/Properties.h"
#include "Utilities/cFormat.h"

// We handle all of these properties
#include "cObjectManagerPart_Common.h"
#include "cObjectManagerPart_Physics.h"
#include "cObjectManagerPart_ChannelControl.h"
#include "cObjectManagerPart_3d.h"
#include "cObjectManagerPart_Alias.h"

#include <iostream>

cObjectManager_ChannelGroup::cObjectManager_ChannelGroup()
{
}

cObjectManager_ChannelGroup::~cObjectManager_ChannelGroup()
{
}

// Root Node of XML document which has assets
void cObjectManager_ChannelGroup::LoadObjects(rapidxml::xml_node<>* node)
{
	auto type = gamelibrary::Object_type(node).GetValue();
	auto name = gamelibrary::Object_name(node).GetValue();
	auto asset_id = gamelibrary::Object_asset_id(node).GetValue();

	auto object = new cObject_ChannelGroup();
	object->LoadCommon(type, name, asset_id, node);

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
			else if (cObjectManagerPart_ChannelControl().HandleProperty(object, type, name, value))
				continue;
			else if (cObjectManagerPart_Alias().HandleProperty(object, type, name, value))
				continue;
			else
			{
				cObjectManagerPart_Common::LogInvalidProperty(__FILE__, name, type, value);
			}
		} // if (std::string(property->name()) == std::string("Property"))
	} // for (auto property = node->first_node("Property");

	cObjectManagerPart_Common::AddToMap(m_map_objects, object, __FILE__, name, type, asset_id);
}

void cObjectManager_ChannelGroup::SaveObject(iObject* inObject, rapidxml::xml_node<>* parent)
{
	auto object = cObjectManagerPart_Common::AddObjectToMap(m_map_objects, inObject, parent);
	assert(object);

	iObject_Common* writeObject = dynamic_cast<iObject_Common*>(object);
	assert(writeObject);

	auto node = writeObject->GetNode();
	if (node)
	{
		gamelibrary::Object libObject(node);

		cObjectManagerPart_Common().SaveProperties(writeObject, node);
		cObjectManagerPart_3d().SaveProperties(writeObject, node);
		cObjectManagerPart_ChannelControl().SaveProperties(writeObject, node);
		cObjectManagerPart_Physics().SaveProperties(writeObject, node);
		cObjectManagerPart_Alias().SaveProperties(writeObject, node);
	}
}


// Retrieve the item information
iObjectManager::iObject_map* cObjectManager_ChannelGroup::GetObjects(const std::string& name)
{
	return &m_map_objects;
}

// For debugging purposes - dumps the contents in human readable form
std::ostream& operator<<(std::ostream& stream, const cObjectManager_ChannelGroup& val)
{
	return stream;
}


void cObjectManager_ChannelGroup::ResolveAlias()
{
	return;					// No Alias
}
