
#include "cObjectManager_impl.h"
#include "GameLibrary/Objects.h"
#include "GameLibrary/Object.h"
#include "cObjectManager_Audio.h"
#include "cObjectManager_Image.h"
#include "cObjectManager_Font.h"
#include "cObjectManager_Model.h"
#include "cObjectManager_Group.h"
#include "cObjectManager_Video.h"
#include "cObjectManager_Alias.h"
#include "cObjectManager_Physics.h"
#include "cObjectManager_World.h"
#include "cObjectManager_Light.h"

#include <iostream>
//#include <stdio.h> 

cObjectManager_impl::cObjectManager_impl()
{
}

cObjectManager_impl::~cObjectManager_impl()
{
	// Cleanup managers
	for (auto in : m_ObjectManagers)
	{
		delete in.second;
	}
}

void cObjectManager_impl::Init()
{
	if (m_ObjectManagers.size() > 0)
		return;
	m_ObjectManagers["alias"] = new cObjectManager_Alias();
	m_ObjectManagers["audio"] = new cObjectManager_Audio();
	m_ObjectManagers["font"] = new cObjectManager_Font();
	m_ObjectManagers["group"] = new cObjectManager_Group();
	m_ObjectManagers["image"] = new cObjectManager_Image();
	m_ObjectManagers["light"] = new cObjectManager_Light();
	m_ObjectManagers["model"] = new cObjectManager_Model();
	m_ObjectManagers["physics"] = new cObjectManager_Physics();
	m_ObjectManagers["video"] = new cObjectManager_Video();
	m_ObjectManagers["world"] = new cObjectManager_World();
}

cObjectManager_impl::iObject_map* cObjectManager_impl::GetObjects(const std::string& name)
{
	auto manager = m_ObjectManagers[name];
	assert(manager != NULL);
	return manager->GetObjects(name);
}

// Root Node of XML document which has assets
void cObjectManager_impl::LoadObjects(rapidxml::xml_node<>* parent)
{
	Init();											// Make sure we are initialized
	gamelibrary::Objects groups(parent);

	for (auto trans = parent->first_node("Object");
		trans;
		trans = trans->next_sibling())
	{
		if (std::string(trans->name()) == std::string("Object"))
		{
//			gamelibrary::Object group(trans);
//			gamelibrary::Object_name name(trans);
			gamelibrary::Object_type type(trans);
//			gamelibrary::Object_type assset_id(trans);

			auto typeName = type.GetValue();

			auto manager = m_ObjectManagers[typeName];
			assert(manager);
			manager->LoadObjects(trans);
		}
	}
}

// Write an object to the XML file
void cObjectManager_impl::SaveObject(iObject* inObject, rapidxml::xml_node<>* parent)
{
	gamelibrary::Objects groups(parent);
	std::string typeName = inObject->GetType();
	auto manager = m_ObjectManagers[typeName];
	assert(manager);
	manager->SaveObject(inObject, parent);
}


std::ostream& operator<<(std::ostream& stream, const cObjectManager_impl& val)
{
	stream << "In cObjectManager_impl" << std::endl;
	for (auto in : val.m_ObjectManagers)
	{
		auto manager = in.second;
		stream << *(manager);
	}
	return stream;
}

// returns NULL (0) if we didn't find it.
iObject* cObjectManager_impl::FindObjectByName(const std::string& objectName)
{
	for (auto manager : m_ObjectManagers)
	{
		auto objects = manager.second->GetObjects(manager.first);
		if (objects->find(objectName) != objects->end())
			return (*objects)[objectName];
	}
	return NULL;
}
