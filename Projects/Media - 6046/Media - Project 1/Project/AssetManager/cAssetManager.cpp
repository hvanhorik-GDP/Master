#include "cAssetManager.h"
#include "impl_AssetManager.h"
#include <cassert>

cAssetManager::cAssetManager()
{
	if (!m_impl_AssetManager)
		m_impl_AssetManager = new impl_AssetManager();
};

void cAssetManager::LoadAssets(rapidxml::xml_node<>* parent)
{
	assert(m_impl_AssetManager);
	m_impl_AssetManager->LoadAssets(parent);
}

std::ostream& operator<<(std::ostream& stream, const cAssetManager& val)
{
	assert(val.m_impl_AssetManager != NULL);
	stream << val.m_impl_AssetManager;
	return stream;
}

iAssetManager* cAssetManager::GetAssetManager(const std::string& name)
{
	assert(m_impl_AssetManager);
	return m_impl_AssetManager->GetAssetManager(name);
}
