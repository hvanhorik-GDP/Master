#include "impl_ObjectManager.h"

#include "impl_ObjectManager.h"
#include "XML/AssetGroups.h"
#include "cAudioObjectManager.h"
#include <iostream>
#include <stdio.h> 

impl_ObjectManager::impl_ObjectManager()
{
}

impl_ObjectManager::~impl_ObjectManager()
{
	// Cleanup managers
	for (auto in : m_ObjectManagers)
	{
		delete in.second;
	}
}
iObjectManager* impl_ObjectManager::GetObjectManager(const std::string& name)
{
	auto manager = m_ObjectManagers[name];
	assert(manager != NULL);
	return manager;
}

// Root Node of XML document which has assets
void impl_ObjectManager::LoadObjects(rapidxml::xml_node<>* parent, cAssetManager* assetManager)
{
	// This loop is non sensical. Each valid manager should just do the same loop
	// to check for assets and read any that are relevent for them
	//cAudioObjectManager* audio = new cAudioObjectManager();
	//m_Managers["audios"] = audio;
	//audio->LoadAssets(parent);

	gamelibrary::AssetGroups groups(parent);
	for (size_t i = 0; i < groups.GetSize(); ++i)
	{
		gamelibrary::AssetGroups temp(groups.GetParent(), i);
		if (temp.isValid())
		{
			gamelibrary::GameAsset_open open(temp.GetNode());
			gamelibrary::GameAsset_type type(temp.GetNode());
			if (type.GetValue() == "audios")
			{
				// The Manager should handle duplicates properly
				if (m_ObjectManagers.find("audios") == m_ObjectManagers.end())
				{
					cAudioObjectManager* audio = new cAudioObjectManager();
					m_ObjectManagers["audios"] = audio;
					audio->LoadObjects(parent, assetManager);
				}
			}
			else
			{
				// Handle	"videos"
				//			"images"
				//			"shaders"
				//			"models"
				//			"fonts"
				std::cout << "Unimplemented ObjectManager: (Ignored): " << type.GetValue() << std::endl;
			}
		}
	}

}

std::ostream& operator<<(std::ostream& stream, const impl_ObjectManager& val)
{
	stream << "In impl_ObjectManager" << std::endl;
	for (auto in : val.m_ObjectManagers)
	{
		auto manager = in.second;
		stream << *(manager);
	}
	return stream;
}
