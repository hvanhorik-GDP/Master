#include "cObjectManagerPart_Group.h"
#include "ObjectItems/cObject_Group.h"
#include "GameLibrary/Object.h"

cObjectManagerPart_Group::cObjectManagerPart_Group()
{
}

cObjectManagerPart_Group::~cObjectManagerPart_Group()
{
}

bool cObjectManagerPart_Group::HandleProperty(iObject* object,
	const std::string& type,
	const std::string& name,
	const std::string& value)
{
	cObject_Group* group = dynamic_cast<cObject_Group*>(object);
	assert(group);
	if (type == "alias")
		group->m_mapObjects[name] = NULL;		// Just note the name (This gets filled in post processing)
	else
		return false;
	return true;
}

// Saves all of the properties to the xml file
void cObjectManagerPart_Group::SaveProperties(iObject* object,
	rapidxml::xml_node<>* node)
{
	cObject_Group* group = dynamic_cast<cObject_Group*>(object);
	assert(group);
	gamelibrary::Object libObject(node);

	for (auto alias : group->m_mapObjects)
	{
		libObject.AddProperty(alias.first, "alias", alias.first);
	}
}

// We need this dummy operator in case classes don't override this method.
std::ostream& operator<<(std::ostream& stream, const cObjectManagerPart_Group& val)
{
	stream << "Got to cObjectManagerPart_Group by accident" << std::endl;
	return stream;
}
