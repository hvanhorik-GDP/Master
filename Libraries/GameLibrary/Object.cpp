#include "Object.h"
#include "Properties.h"


namespace gamelibrary
{
	//<Object type = "light" name = "spotlight" id = "foo2">

	const std::string Object::gName = "Object";
	const std::string Object_type::gName = "type";
	const std::string Object_name::gName = "name";
	const std::string Object_asset_id::gName = "asset_id";

	void Object::AddProperty(
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
	std::ostream& operator << (std::ostream& out, const Object& node)
	{
		out << "Unimlemented  Objects - << " << std::endl;
		return out;
	}
}
