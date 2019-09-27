#include "impl_AssetManager.h"
#include "XML/AssetGroups.h"
#include "cAudioAssetManager.h"
#include <iostream>
#include <stdio.h> 

impl_AssetManager::impl_AssetManager()
{
}

impl_AssetManager::~impl_AssetManager()
{
	// Cleanup managers
	for (auto in : m_Managers)
	{
		delete in.second;
	}
}
iAssetManager* impl_AssetManager::GetAssetManager(const std::string& name)
{
	auto manager = m_Managers[name];
	assert(manager != NULL);
	return manager;
}

// Root Node of XML document which has assets
void impl_AssetManager::LoadAssets(rapidxml::xml_node<>* parent)
{
	// This loop is non sensical. Each valid manager should just do the same loop
	// to check for assets and read any that are relevent for them
	//cAudioAssetManager* audio = new cAudioAssetManager();
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
				if (m_Managers.find("audios") == m_Managers.end())
				{
					cAudioAssetManager* audio = new cAudioAssetManager();
					m_Managers["audios"] = audio;
					audio->LoadAssets(parent);
				}
			}
			else
			{
				// Handle	"videos"
				//			"images"
				//			"shaders"
				//			"models"
				//			"fonts"
				std::cout << "Unimplemented AssetManager: (Ignored): " << type.GetValue() << std::endl;
			}
		}
	}

}

std::ostream& operator<<(std::ostream& stream, const impl_AssetManager& val)
{
	stream << "In impl_AssetManager" << std::endl;
	for (auto in : val.m_Managers)
	{
		auto manager = in.second;
		stream << *(manager);
	}
	return stream;
}
