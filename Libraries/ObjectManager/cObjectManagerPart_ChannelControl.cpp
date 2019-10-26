#include "cObjectManagerPart_ChannelControl.h"
#include "ObjectItems/cObject_ChannelControl.h"
#include "GameLibrary/Object.h"

cObjectManagerPart_ChannelControl::cObjectManagerPart_ChannelControl()
{

}

cObjectManagerPart_ChannelControl::~cObjectManagerPart_ChannelControl()
{

}

bool cObjectManagerPart_ChannelControl::HandleProperty(iObject* object,
	const std::string& type,
	const std::string& name,
	const std::string& value)
{
	cObject_ChannelControl* group = dynamic_cast<cObject_ChannelControl*>(object);
	assert(group);
	//if (type == "alias")
	//	group->m_mapObjects[name] = NULL;		// Just note the name (This gets filled in post processing)
	return false;
}

// Saves all of the properties to the xml file
void cObjectManagerPart_ChannelControl::SaveProperties(iObject* object,
	rapidxml::xml_node<>* node)
{
	cObject_ChannelControl* group = dynamic_cast<cObject_ChannelControl*>(object);
	assert(group);
	gamelibrary::Object libObject(node);

	//for (auto alias : group->m_mapObjects)
	//{
	//	libObject.AddProperty(alias.first, "alias", alias.first);
	//}
}

// We need this dummy operator in case classes don't override this method.
std::ostream& operator<<(std::ostream& stream, const cObjectManagerPart_ChannelControl& val)
{
	stream << "Got to cObjectManagerPart_ChannelControl by accident" << std::endl;
	return stream;
}
