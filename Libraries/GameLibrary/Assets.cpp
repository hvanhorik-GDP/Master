#include "AssetGroups.h"
#include "XML/XMLIndent.h"
#include <iostream>

namespace gamelibrary
{
	std::ostream& operator << (std::ostream& out, const Assets& node)
	{
		using namespace std;

		for (size_t i = 0; i < node.GetSize(); ++i)
		{
			Assets temp(node.GetParent(), i);
			if (temp.isValid())
			{
				out << XMLIndent(3) << "<" << temp.GetNodeName() << " ";
				Assets_name name(temp.GetNode());
				out << name << ">" << endl;
				out << XMLIndent(3) << temp.GetAssetFile() << endl;
				out << XMLIndent(3) << temp.GetProperties();
				out << XMLIndent(3) << " </" << temp.GetNodeName() << ">" << endl;
			}
		}
		return out;
	}

	void Assets::AddProperty(
		const std::string& newname,
		const std::string& newtype,
		const std::string& newvalue)
	{
		rapidxml::xml_node<>* node = NULL;

		// See if we already have one
		for (auto property = GetNode()->first_node("Property");
			property;
			property = property->next_sibling())
		{
			if (std::string(property->name()) == std::string("Property"))
			{
				gamelibrary::Property_name PropertyName(property);
				if (PropertyName.GetValue() == newname)
				{
					node = property;
					break;
				}
			}
		}
		if (!node)
		{
			// Not here so insert a new one
			gamelibrary::Properties properties(GetNode());
			properties.Insert();
			node = properties.GetNode();
		}

		Property_name name(node);
		name.SetValue(newname);
		Property_type type(node);
		type.SetValue(newtype);
		Property_value value(node);
		value.SetValue(newvalue);
	}

	const std::string Assets::gName = "Asset";
}
