#pragma once

#include "ObjectItems/cObject_Model.h"

#include <map>
#include <vector>

class cObjectWatcher
{
public:
	cObjectWatcher();
	virtual ~cObjectWatcher();
	void AddObject(cObject_Model* object);
	void Watch(float deltaTime);

public:
	std::vector< cObject_Model* > m_VecObjectsWatching;
	float waitTime = 0;
};

