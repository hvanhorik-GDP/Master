#include "cObjectManagerPart_Alias.h"
#include "ObjectItems/cObject_Alias.h"
#include "ObjectItems/cObject_Common.h"
#include "GameLibrary/Object.h"
#include "cObjectManager.h"

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



void cObjectManagerPart_Alias::ResolveAlias(iObjectManager::iObject_map& objects, bool pointToParent)
{
	cObjectManager manager;
	for (auto group : objects)
	{
		auto object = dynamic_cast<cObject_Alias*>(group.second);
		assert(object);

		for (auto alias : object->m_mapObjects)
		{
			iObject* theAlias = manager.FindObjectByName(alias.first);
			assert(theAlias);
			object->m_mapObjects[alias.first] = theAlias;
			if (pointToParent)
				theAlias->SetParentObject(group.second);		// Point back to the parent group
		}
	}
}
