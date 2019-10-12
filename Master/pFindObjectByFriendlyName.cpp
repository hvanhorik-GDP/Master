#include "pFindObjectByFriendlyName.h"
#include "ObjectManager/cObjectManager.h"


// returns NULL (0) if we didn't find it.
cObject_Model* pFindObjectByFriendlyName(std::string name)
{
	cObjectManager objectManager;
	auto objects = *objectManager.GetObjects("model");

	cObject_Model* ret = NULL;
	auto object = objects[name];
	if (object)
		ret = dynamic_cast<cObject_Model*>(object);
	return ret;
}

