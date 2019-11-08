#include "cAssetManager_Models.h"
#include "AssetItems/cItem_Model.h"
#include "GameLibrary/AssetGroups.h"
#include "Models/cPlyLoader.h"
#include "Utilities/cFormat.h"
#include <iostream>
#include <sstream>

cAssetManager_Models::cAssetManager_Models()
{
}
cAssetManager_Models::~cAssetManager_Models()
{
}

void cAssetManager_Models::LoadAssets(rapidxml::xml_node<>* parent)
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
			if (type.GetValue() == "models")
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
						std::string fullPath = rootPath + fileName.GetValue();

						std::string id = assetName.GetValue();
						auto parent = file.GetParent();
						cItem_Model* item = new cItem_Model(id, fullPath, parent, i);
						auto val = subtype.GetValue();
						m_map_items[item->GetAssetID()] = item;
						cPlyLoader loader;
						// Just load the header for speed
						bool ok = loader.LoadPlyModelInfo(fullPath, *item);
						file.AddProperty("exists", "bool", cFormat::PackBool(item->m_fileExists));
						file.AddProperty("valid", "bool", cFormat::PackBool(item->m_isValid));
						if (ok)
						{
							// Write the properties to the xml file
							file.AddProperty("type", "enum", item->m_type);
							file.AddProperty("format", "string", item->m_format);
							file.AddProperty("vertex", "int", cFormat::PackInt(item->m_vertices));
							for (auto in : item->m_vecProperties)
							{
								file.AddProperty(in.name, in.type, "" );
							}
							file.AddProperty("face", "int", cFormat::PackInt(item->m_faces));
							file.AddProperty("normals", "bool", cFormat::PackBool(item->m_hasNormals));
							file.AddProperty("colours", "bool", cFormat::PackBool(item->m_hasColor));
							file.AddProperty("textureCoordinates", "bool", cFormat::PackBool(item->m_hasTextureCoordinates));
						}
					}
				}
			}
		}
	}
}

iAssetManager::iItems_map* cAssetManager_Models::GetItems(const std::string& name)
{
	return &m_map_items;
}

std::ostream& operator<<(std::ostream& stream, const cAssetManager_Models& val)
{
	// TODO
	stream << "std::ostream& operator<<(std::ostream& stream, const cAssetManager_Videos& val)" << " Not implemented" << std::endl;
	return stream;
}
