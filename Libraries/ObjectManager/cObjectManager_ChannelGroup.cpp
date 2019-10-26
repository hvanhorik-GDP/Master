#include "cObjectManager_ChannelGroup.h"
#include "ObjectItems/cObject_Channel.h"
#include "GameLibrary/Object.h"
#include "GameLibrary/Properties.h"
#include "cObjectManagerPart_Physics.h"
#include "cObjectManagerPart_Group.h"
#include "cObjectManagerPart_ChannelControl.h"
#include "cObjectManagerPart_3d.h"

cObjectManager_ChannelGroup::cObjectManager_ChannelGroup()
{
}

cObjectManager_ChannelGroup::~cObjectManager_ChannelGroup()
{
}

// Root Node of XML document which has assets
void cObjectManager_ChannelGroup::LoadObjects(rapidxml::xml_node<>* node)
{

	gamelibrary::Object_type type(node);
	gamelibrary::Object_name name(node);
	gamelibrary::Object_asset_id asset_id(node);


	auto object = new cObject_Channel(type.GetValue(), name.GetValue(), asset_id.GetValue(), node);
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
