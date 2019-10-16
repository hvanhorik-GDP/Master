#include "cObject_Group.h"

cObject_Group::cObject_Group(const std::string& type,
	const std::string& name,
	const std::string& asset_id,
	rapidxml::xml_node<>* node)
	: cObject_Common(type, name, asset_id, node)
{

}
cObject_Group::~cObject_Group()
{
}

void cObject_Group::IntegrationStep(float deltaTime)
{
}

void cObject_Group::AddChildObject(iObject* child)
{
	m_mapObjects[child->GetName()] = child;
}

cObject_Group::mapObjectsInGroup& cObject_Group::GetObjectsInGroup()
{
	return m_mapObjects;
}

// For debugging purposes - dumps the contents in human readable form
std::ostream& operator<<(std::ostream& stream, const cObject_Group& val)
{
	stream << "std::ostream& operator<<(std::ostream& stream, const cObject_Group& val)" << "Not Implemented" << std::endl;
	return stream;
}
