#include "cObjectManager_Channel.h"
#include "ObjectItems/cObject_Channel.h"
#include "GameLibrary/Object.h"
#include "GameLibrary/Properties.h"
#include "Utilities/cFormat.h"

// We handle all of these properties
#include "cObjectManagerPart_Common.h"
#include "cObjectManagerPart_Physics.h"
#include "cObjectManagerPart_ChannelControl.h"
#include "cObjectManagerPart_3d.h"

#include <iostream>

cObjectManager_Channel::cObjectManager_Channel()
{
}

cObjectManager_Channel::~cObjectManager_Channel()
{
}

// Root Node of XML document which has assets
void cObjectManager_Channel::LoadObjects(rapidxml::xml_node<>* node)
{

	auto object = new cObject_Channel();
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
			else if (cObjectManagerPart_ChannelControl().HandleProperty(object, type, name, value))
				continue;
			else
			{
				cObjectManagerPart_Common::LogInvalidProperty(__FILE__, name, type, value);
			}
		} // if (std::string(property->name()) == std::string("Property"))
	} // for (auto property = node->first_node("Property");

	cObjectManagerPart_Common::AddToMap(m_map_objects, object, __FILE__);
}

void cObjectManager_Channel::SaveObject(iObject* inObject, rapidxml::xml_node<>* parent)
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
	}
}


// Retrieve the item information
iObjectManager::iObject_map* cObjectManager_Channel::GetObjects(const std::string& name)
{
	return &m_map_objects;
}

// For debugging purposes - dumps the contents in human readable form
std::ostream& operator<<(std::ostream& stream, const cObjectManager_Channel& val)
{
	return stream;
}


void cObjectManager_Channel::ResolveAlias()
{
	return;					// No Alias
}
