
#include "cObjectManager.h"
#include "impl_ObjectManager.h"
#include <cassert>

cObjectManager::cObjectManager()
{
	if (!m_impl_ObjectManager)
		m_impl_ObjectManager = new impl_ObjectManager();
};

void cObjectManager::LoadObjects(rapidxml::xml_node<>* parent, cAssetManager* objectManager)
{
	assert(m_impl_ObjectManager);
	m_impl_ObjectManager->LoadObjects(parent, objectManager);
}

std::ostream& operator<<(std::ostream& stream, const cObjectManager& val)
{
	assert(val.m_impl_ObjectManager != NULL);
	stream << val.m_impl_ObjectManager;
	return stream;
}

iObjectManager* cObjectManager::GetObjectManager(const std::string& name)
{
	assert(m_impl_ObjectManager);
	return m_impl_ObjectManager->GetObjectManager(name);
}
