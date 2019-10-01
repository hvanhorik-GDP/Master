#include "AssetGroups.h"
#include "GameLibraryElements.h"
#include <iostream>

namespace gamelibrary
{
	const std::string AssetGroups::gName = "AssetGroup";

	void Properties::AddProperty(const std::string& newtype, const std::string& newvalue)
	{
		Insert();
		Properties_type type(GetNode());
		type.SetValue(newtype);
		Properties_value value(GetNode());
		value.SetValue(newvalue);
	}

	std::ostream& operator << (std::ostream& out, const AssetGroups& node)
	{
		using namespace std;

		for (size_t i = 0; i < node.GetSize(); ++i)
		{
			AssetGroups temp(node.GetParent(), i);
			if (temp.isValid())
			{
				out << xmlindent::indent(2) << "<" << temp.GetNodeName() << " ";
				GameAsset_open open(temp.GetNode());
				GameAsset_type type(temp.GetNode());
				out << type << open << ">" << endl;
				out << xmlindent::indent(2) << temp.GetAssetRoot() << endl;
				out << xmlindent::indent(2) <<temp.GetAsset() << endl;
				out << xmlindent::indent(2) << "</" << temp.GetNodeName() << ">" << endl;
			}
		}
		return out;
	}

	std::ostream& operator << (std::ostream& out, const Assets& node)
	{
		using namespace std;

		for (size_t i = 0; i < node.GetSize(); ++i)
		{
			Assets temp(node.GetParent(), i);
			if (temp.isValid())
			{
				out << xmlindent::indent(3) << "<" << temp.GetNodeName() << " ";
				Assets_name name(temp.GetNode());
				out << name << ">" << endl;
				out << xmlindent::indent(3) << temp.GetAssetFile() << endl;
				out << xmlindent::indent(3) << temp.GetProperties();
				out << xmlindent::indent(3) << " </" << temp.GetNodeName() << ">" << endl;
			}
		}
		return out;
	}

	std::ostream& operator << (std::ostream& out, const Properties& node)
	{
		using namespace std;

		for (size_t i = 0; i < node.GetSize(); ++i)
		{
			Properties temp(node.GetParent(), i);
			if (temp.isValid())
			{
				out << xmlindent::indent(4) << "<" << temp.GetNodeName() << " ";
				Properties_type type(temp.GetNode());
				Properties_value value(temp.GetNode());
				out << type << value << ">" << endl;
			}
		}
		return out;
	}

	const std::string AssetFile::gName = "AssetFile";
	const std::string AssetRoot::gName = "AssetRoot";
	const std::string GameAsset_type::gName = "type";
	const std::string GameAsset_open::gName = "open";
	const std::string GameAsset_subdir::gName = "subdir";
	const std::string GameAsset_subtype::gName = "subtype";
	const std::string Assets_name::gName = "name";
	const std::string Assets_type::gName = "type";
	const std::string Assets::gName = "Asset";
	const std::string AssetParts::gName = "AssetPart";
	const std::string Properties_type::gName = "type";
	const std::string Properties_value::gName = "value";
	const std::string Properties::gName = "Property";
}
