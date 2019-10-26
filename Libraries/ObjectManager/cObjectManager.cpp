
#include "cObjectManager.h"
#include "cObjectManager_impl.h"
#include <cassert>

cObjectManager_impl* m_cObjectManager_impl = NULL;		// The one and only

cObjectManager::cObjectManager()
{
	if (!m_cObjectManager_impl)
		m_cObjectManager_impl = new cObjectManager_impl();
};

void cObjectManager::LoadObjects(rapidxml::xml_node<>* parent)
{
	assert(m_cObjectManager_impl);
	m_cObjectManager_impl->LoadObjects(parent);
}

// Write an object to the XML file
void cObjectManager::SaveObject(iObject* inObject, rapidxml::xml_node<>* parent)
{
	assert(m_cObjectManager_impl);
	m_cObjectManager_impl->SaveObject(inObject, parent);

}

std::ostream& operator<<(std::ostream& stream, const cObjectManager& val)
{
	stream << *m_cObjectManager_impl;
	return stream;
}

// Retrieve the item information
iObjectManager::iObject_map* cObjectManager::GetObjects(const std::string& name)
{
	assert(m_cObjectManager_impl);
	return m_cObjectManager_impl->GetObjects(name);
}

iObject* cObjectManager::FindObjectByName(const std::string& objectName)
{
	assert(m_cObjectManager_impl);
	return m_cObjectManager_impl->FindObjectByName(objectName);
}

void cObjectManager::ResolveAlias()
{
	assert(m_cObjectManager_impl);
	m_cObjectManager_impl->ResolveAlias();
}