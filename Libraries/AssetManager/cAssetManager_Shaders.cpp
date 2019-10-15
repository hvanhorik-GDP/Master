#include "cAssetManager_Shaders.h"
#include "GAmeLibrary/AssetGroups.h"
#include "../Shaders/cShaderLoader.h"
#include "Utilities/cFormat.h"

#include <iostream>
#include <sstream>

cAssetManager_Shaders::cAssetManager_Shaders()
{
}
cAssetManager_Shaders::~cAssetManager_Shaders()
{
}

void cAssetManager_Shaders::LoadAssets(rapidxml::xml_node<>* parent)
{
	using namespace gamelibrary;

	AssetGroups groups(parent);
	for (size_t i = 0; i < groups.GetSize(); ++i)
	{
		AssetGroups group(groups.GetParent(), i);
		if (group.isValid())
		{
			GameAsset_open open(group.GetNode());
			GameAsset_type type(group.GetNode());
			if (type.GetValue() == "shaders")
			{
				GameAsset_subtype subtype(group.GetNode());
				AssetRoot  root = group.GetAssetRoot();
				std::string rootPath = root.GetValue();		// Root Path
				Assets assets = group.GetAsset();

				for (size_t i = 0; i < assets.GetSize(); ++i)
				{
					Assets file(assets.GetParent(), i);
					if (file.isValid())
					{
						Assets_name assetName(file.GetNode());
						AssetFile fileName = file.GetAssetFile();
						Assets_type assetType(file.GetNode());
						std::string fullPath = rootPath + fileName.GetValue();

						std::string id = assetName.GetValue();
						auto parent = file.GetParent();
						cItem_Shader* item = new cItem_Shader(id, fullPath, parent, i);
						auto val = assetType.GetValue();
						if (val == "fragment")
							item->m_shaderType = cItem_Shader::type::fragment;
						else if (val == "vertex")
							item->m_shaderType = cItem_Shader::type::vertex;
						m_map_items[item->GetAssetID()] = item;

						cShaderLoader loader;
						bool ok = loader.Load(*item);
						if (!ok)
						{
							item->m_error = loader.GetLastError();
							item->m_valid = false;
							continue;
						}
						item->m_valid = true;
						// Write the properties to the xml file
						file.AddProperty("isValid", "bool", cFormat::PackBool(item->m_valid));
					}
				}
			}
		}
	}
}

iAssetManager::iItems_map* cAssetManager_Shaders::GetItems(const std::string& name)
{
	return &m_map_items;
}

std::ostream& operator<<(std::ostream& stream, const cAssetManager_Shaders& val)
{
	// TODO
	stream << "std::ostream& operator<<(std::ostream& stream, const cAssetManager_Videos& val)" << " Not implemented" << std::endl;
	return stream;
}
