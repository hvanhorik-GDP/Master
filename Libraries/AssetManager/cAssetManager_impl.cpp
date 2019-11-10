#include "cAssetManager_impl.h"
#include "GAmeLibrary/AssetGroups.h"
#include "cAssetManager_Audios.h"
#include "cAssetManager_Videos.h"
#include "cAssetManager_Shaders.h"
#include "cAssetManager_Programs.h"
#include "cAssetManager_Images.h"
#include "cAssetManager_Fonts.h"
#include "cAssetManager_Models.h"

#include <iostream>
#include <stdio.h> 

cAssetManager_impl::cAssetManager_impl()
{
}

cAssetManager_impl::~cAssetManager_impl()
{
	// Cleanup managers
	for (auto in : m_AssetManagers)
	{
		delete in.second;
	}
}

iAssetManager* cAssetManager_impl::GetAssetManager(const std::string& name)
{
	auto manager = m_AssetManagers[name];
	assert(manager != NULL);
	return manager;
}

cAssetManager_impl::iItems_map* cAssetManager_impl::GetItems(const std::string& name)
{
	auto manager = m_AssetManagers[name];
	assert(manager != NULL);
	return manager->GetItems(name);
}

// Root Node of XML document which has assets
void cAssetManager_impl::LoadAssets(rapidxml::xml_node<>* parent)
{
	m_AssetManagers["audios"] = new cAssetManager_Audios();
	m_AssetManagers["audios"]->LoadAssets(parent);

	m_AssetManagers["videos"] = new cAssetManager_Videos();
	m_AssetManagers["videos"]->LoadAssets(parent);

	m_AssetManagers["images"] = new cAssetManager_Images();
	m_AssetManagers["images"]->LoadAssets(parent);

	m_AssetManagers["shaders"] = new cAssetManager_Shaders();
	m_AssetManagers["shaders"]->LoadAssets(parent);

	m_AssetManagers["programs"] = new cAssetManager_Programs();
	m_AssetManagers["programs"]->LoadAssets(parent);

	m_AssetManagers["models"] = new cAssetManager_Models();
	m_AssetManagers["models"]->LoadAssets(parent);

	m_AssetManagers["fonts"]  = new cAssetManager_Fonts();
	m_AssetManagers["fonts"]->LoadAssets(parent);

#if 0
	gamelibrary::AssetGroups groups(parent);
	for (size_t i = 0; i < groups.GetSize(); ++i)
	{
		//TODO - this will screw up and find the objects
		// the array loops through all elements of every name
		gamelibrary::AssetGroups temp(groups.GetParent(), i);
		if (temp.isValid())
		{
			gamelibrary::GameAsset_open open(temp.GetNode());
			gamelibrary::GameAsset_type type(temp.GetNode());
			if (type.GetValue() == "audios")
			{
				// The Manager should handle duplicates properly
				if (m_AssetManagers.find("audios") == m_AssetManagers.end())
				{
					auto manager = new cAssetManager_Audios();
					m_AssetManagers["audios"] = manager;
					manager->LoadAssets(parent);
				}
			}
			else if (type.GetValue() == "videos")
			{
				// The Manager should handle duplicates properly
				if (m_AssetManagers.find("videos") == m_AssetManagers.end())
				{
					auto manager = new cAssetManager_Videos();
					m_AssetManagers["videos"] = manager;
					manager->LoadAssets(parent);
				}
			}
			else if (type.GetValue() == "images")
			{
				// The Manager should handle duplicates properly
				if (m_AssetManagers.find("images") == m_AssetManagers.end())
				{
					auto manager = new cAssetManager_Images();
					m_AssetManagers["images"] = manager;
					manager->LoadAssets(parent);
				}
			}
			else if (type.GetValue() == "shaders" || type.GetValue() == "programs")
			{
				// The Manager should handle duplicates properly
				if (m_AssetManagers.find("shaders") == m_AssetManagers.end())
				{
					auto manager = new cAssetManager_Shaders();
					m_AssetManagers["shaders"] = manager;
					manager->LoadAssets(parent);
				}
				// (shaders and groups go together so need proper ordering
				if (m_AssetManagers.find("programs") == m_AssetManagers.end())
				{
					auto manager = new cAssetManager_Programs();
					m_AssetManagers["programs"] = manager;
					manager->LoadAssets(parent);
				}
			}
			else if (type.GetValue() == "models")
			{
				// The Manager should handle duplicates properly
				if (m_AssetManagers.find("models") == m_AssetManagers.end())
				{
					auto manager = new cAssetManager_Models();
					m_AssetManagers["models"] = manager;
					manager->LoadAssets(parent);
				}
			}
			else if (type.GetValue() == "fonts")
			{
				// The Manager should handle duplicates properly
				if (m_AssetManagers.find("fonts") == m_AssetManagers.end())
				{
					auto manager = new cAssetManager_Fonts();
					m_AssetManagers["fonts"] = manager;
					manager->LoadAssets(parent);
				}
			} 
			else
			{
				// TODO - see COMMENT ABOVE
//				std::cout << "Unimplemented AssetManager: (Ignored): " << type.GetValue() << std::endl;
			}
		}
	}
#endif

}

std::ostream& operator<<(std::ostream& stream, const cAssetManager_impl& val)
{
	stream << "In cAssetManager_impl" << std::endl;
	for (auto in : val.m_AssetManagers)
	{
		auto manager = in.second;
		stream << *(manager);
	}
	return stream;
}
