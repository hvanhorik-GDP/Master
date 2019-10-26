#include "cObjectManager_Audio.h"
#include "ObjectItems/cObject_Audio.h"
#include "GameLibrary/Object.h"
#include "GameLibrary/Properties.h"

cObjectManager_Audio::cObjectManager_Audio()
{
}

cObjectManager_Audio::~cObjectManager_Audio()
{
}

// Root Node of XML document which has assets
void cObjectManager_Audio::LoadObjects(rapidxml::xml_node<>* node)
{

	gamelibrary::Object_type type(node);
	gamelibrary::Object_name name(node);
	gamelibrary::Object_asset_id asset_id(node);


	auto object = new cObject_Audio(type.GetValue(), name.GetValue(), asset_id.GetValue(), node);
}

// Retrieve the item information
iObjectManager::iObject_map* cObjectManager_Audio::GetObjects(const std::string& name)
{
	return &m_map_objects;
}

// For debugging purposes - dumps the contents in human readable form
std::ostream& operator<<(std::ostream& stream, const cObjectManager_Audio& val)
{
	return stream;
}

void cObjectManager_Audio::ResolveAlias()
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
