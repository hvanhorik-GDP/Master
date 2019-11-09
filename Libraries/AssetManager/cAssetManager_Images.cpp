#include "cAssetManager_Images.h"

#include "GAmeLibrary/AssetGroups.h"
#include "AssetItems/cItem_Image.h"
#include "TextureManager/cBasicTextureManager.h"
#include "Utilities/cFormat.h"

#include <iostream>
#include <sstream>

cAssetManager_Images::cAssetManager_Images()
{
}
cAssetManager_Images::~cAssetManager_Images()
{
}

void cAssetManager_Images::LoadAssets(rapidxml::xml_node<>* parent)
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
			if (type.GetValue() == "images")
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
						cItem_Image* item = new cItem_Image(id, fullPath, parent, i);
						auto val = subtype.GetValue();
						m_map_items[item->GetAssetID()] = item;

						cBasicTextureManager textureManager;
						textureManager.SetBasePath(rootPath);
						
						CTextureFromBMP* bmp =  textureManager.Create2DTextureFromBMPFile(fileName.GetValue(), true);
						if (!bmp)
							std::cout << "Didn't load texture" << fullPath << std::endl;

						item->m_fileExists = (bmp != NULL);
						item->m_isValid = (bmp != NULL);
						// Just load the header for speed
						file.AddProperty("exists", "bool", cFormat::PackBool(item->m_fileExists));
						file.AddProperty("valid", "bool", cFormat::PackBool(item->m_isValid));
						if (bmp)
						{
							// Write the properties to the xml file
							file.AddProperty("fileSize", "int", cFormat::PackInt(bmp->GetFileSize()));
							file.AddProperty("bitsPerPixel", "int", cFormat::PackInt(bmp->GetBitsPerPixel()));
							file.AddProperty("height", "int", cFormat::PackInt(bmp->GetHeightInRows()));
							file.AddProperty("width", "int", cFormat::PackInt(bmp->GetWidthInColumns()));
							file.AddProperty("compressionMode", "int", cFormat::PackInt(bmp->GetCompressionMode()));
						}
					}
				}
			}
		}
	}
}


iAssetManager::iItems_map* cAssetManager_Images::GetItems(const std::string& name)
{
	return &m_map_items;
}

std::ostream& operator<<(std::ostream& stream, const cAssetManager_Images& val)
{
	// TODO
	stream << "std::ostream& operator<<(std::ostream& stream, const cAssetManager_Videos& val)" << " Not implemented" << std::endl;
	return stream;
}
