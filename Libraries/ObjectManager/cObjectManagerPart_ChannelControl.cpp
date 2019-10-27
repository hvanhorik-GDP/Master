#include "cObjectManagerPart_ChannelControl.h"
#include "ObjectItems/cObject_ChannelControl.h"
#include "GameLibrary/Object.h"
#include "Utilities/cFormat.h"

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

	cObject_ChannelControl* channel = dynamic_cast<cObject_ChannelControl*>(object);
	assert(channel);
	if (name == "paused")
		channel->m_Paused = cFormat::LoadBool(value);

	else if (name == "volume")
		channel->m_Volume = cFormat::LoadFloat(value);

	else if (name == "volunmeRamp")
		channel->m_VolunmeRamp = cFormat::LoadBool(value);

	else if (name == "audibility")
		channel->m_Audibility = cFormat::LoadFloat(value);

	else if (name == "pitch")
		channel->m_Pitch = cFormat::LoadFloat(value);

	else if (name == "mute")
		channel->m_Mute = cFormat::LoadBool(value);

	else if (name == "playing")
		channel->m_Playing = cFormat::LoadBool(value);
	else
		return false;

	return true;
}

// Saves all of the properties to the xml file
void cObjectManagerPart_ChannelControl::SaveProperties(iObject* object,
	rapidxml::xml_node<>* node)
{
	cObject_ChannelControl* group = dynamic_cast<cObject_ChannelControl*>(object);
	assert(group);
	gamelibrary::Object libObject(node);


	libObject.AddProperty("paused", "bool", cFormat::PackBool(group->m_Paused));
	libObject.AddProperty("volume", "float", cFormat::PackFloat(group->m_Volume));
	libObject.AddProperty("volunmeRamp", "bool", cFormat::PackBool(group->m_VolunmeRamp));
	libObject.AddProperty("audibility", "float", cFormat::PackFloat(group->m_Audibility));
	libObject.AddProperty("pitch", "float", cFormat::PackFloat(group->m_Pitch));
	libObject.AddProperty("mute", "bool", cFormat::PackBool(group->m_Mute));
	libObject.AddProperty("playing", "bool", cFormat::PackBool(group->m_Playing));
}

// We need this dummy operator in case classes don't override this method.
std::ostream& operator<<(std::ostream& stream, const cObjectManagerPart_ChannelControl& val)
{
	stream << "Got to cObjectManagerPart_ChannelControl by accident" << std::endl;
	return stream;
}
