#include "cObjectManagerPart_Alias.h"
#include "ObjectItems/cObject_Alias.h"
#include "GameLibrary/Object.h"

cObjectManagerPart_Alias::cObjectManagerPart_Alias()
{
}

cObjectManagerPart_Alias::~cObjectManagerPart_Alias()
{
}

bool cObjectManagerPart_Alias::HandleProperty(iObject* object,
	const std::string& type,
	const std::string& name,
	const std::string& value)
{
	cObject_Alias* group = dynamic_cast<cObject_Alias*>(object);
	assert(group);
	if (type == "alias")
		group->m_mapObjects[name] = NULL;		// Just note the name (This gets filled in post processing)
	else
		return false;
	return true;
}

// Saves all of the properties to the xml file
void cObjectManagerPart_Alias::SaveProperties(iObject* object,
	rapidxml::xml_node<>* node)
{
	cObject_Alias* group = dynamic_cast<cObject_Alias*>(object);
	assert(group);
	gamelibrary::Object libObject(node);

	for (auto alias : group->m_mapObjects)
	{
		libObject.AddProperty(alias.first, "alias", alias.first);
	}
}

// We need this dummy operator in case classes don't override this method.
std::ostream& operator<<(std::ostream& stream, const cObjectManagerPart_Alias& val)
{
	stream << "Got to cObjectManagerPart_Alias by accident" << std::endl;
	return stream;
}
