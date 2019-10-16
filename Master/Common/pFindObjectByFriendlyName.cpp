#include "pFindObjectByFriendlyName.h"
#include "ObjectManager/cObjectManager.h"


// returns NULL (0) if we didn't find it.
cObject_Model* pFindObjectByFriendlyName(std::string name)
{
	cObjectManager objectManager;
	auto object = objectManager.FindObjectByName(name);
	if (object)
		return dynamic_cast<cObject_Model*>(object);
	return NULL;
}

