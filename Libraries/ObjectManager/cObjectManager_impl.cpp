
#include "cObjectManager_impl.h"
#include "GameLibrary/Objects.h"
#include "GameLibrary/Object.h"
#include "cObjectManager_Audio.h"
#include "cObjectManager_Image.h"
#include "cObjectManager_Font.h"
#include "cObjectManager_Model.h"
#include "cObjectManager_Group.h"
#include "cObjectManager_Video.h"
#include "cObjectManager_Physics.h"
#include "cObjectManager_World.h"
#include "cObjectManager_Light.h"
#include "cObjectManager_ParticleEmitter.h"
#include "cObjectManager_Camera.h"
#include "cObjectManager_Texture.h"
#include "cObjectManager_Window.h"
#include "cObjectManager_Channel.h"
#include "cObjectManager_ChannelGroup.h"
#include "cObjectManager_DSP.h"
#include "cObjectManager_Sound.h"


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
	m_ObjectManagers["audio"] = new cObjectManager_Audio();
	m_ObjectManagers["camera"] = new cObjectManager_Camera();
	m_ObjectManagers["font"] = new cObjectManager_Font();
	m_ObjectManagers["channel"] = new cObjectManager_Channel();
	m_ObjectManagers["channelgroup"] = new cObjectManager_ChannelGroup();
	m_ObjectManagers["DSP"] = new cObjectManager_DSP();
	m_ObjectManagers["group"] = new cObjectManager_Group();
	m_ObjectManagers["image"] = new cObjectManager_Image();
	m_ObjectManagers["light"] = new cObjectManager_Light();
	m_ObjectManagers["model"] = new cObjectManager_Model();
	m_ObjectManagers["particleemitter"] = new cObjectManager_ParticleEmitter();
	m_ObjectManagers["physics"] = new cObjectManager_Physics();
	m_ObjectManagers["sound"] = new cObjectManager_Sound();
	m_ObjectManagers["texture"] = new cObjectManager_Texture();
	m_ObjectManagers["video"] = new cObjectManager_Video();
	m_ObjectManagers["window"] = new cObjectManager_Window();
	m_ObjectManagers["world"] = new cObjectManager_World();

	enum eObjectType
	{
		eUnknown,
		eAudio,
		eCamera,
		eChannel,
		eChannelControl,
		eChannelGroup,
		eDSP,
		eFont,
		eGroup,
		eLight,
		eImage,
		eModel,
		eParticle,
		eParticleEmitter,
		ePhysics,
		eTexture,
		eVideo,
		eWindow,
		eWorld,
		eMax = eWorld
	};
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
			gamelibrary::Object_type type(trans);

			auto typeName = type.GetValue();

			auto manager = m_ObjectManagers[typeName];
			assert(manager);
			manager->LoadObjects(trans);
		}
	}
	ResolveAlias();
	//// After loaded we need to resolve all aliases
	//auto temp = m_ObjectManagers["group"];
	//assert(temp);
	//cObjectManager_Group* groupManager = dynamic_cast<cObjectManager_Group*>(temp);
	//assert(groupManager);
	//groupManager->ResolveAlias();

	//// After loaded we need to resolve all aliases
	//temp = m_ObjectManagers["world"];
	//assert(temp);
	//cObjectManager_World* worldManager = dynamic_cast<cObjectManager_World*>(temp);
	//assert(worldManager);
	//worldManager->ResolveAlias();
}

void cObjectManager_impl::ResolveAlias()
{
	for (auto manager : m_ObjectManagers)
	{
		manager.second->ResolveAlias();
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
