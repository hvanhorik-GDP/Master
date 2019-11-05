#pragma once

#include "iCacheManager.h"
#include "cCacheManager_impl.h"

#pragma comment (lib, "CacheManager.lib")


class cCacheManager: public iCacheManager
{
public:
	cCacheManager();
	virtual ~cCacheManager();
private:
	void CleanUp();
};

