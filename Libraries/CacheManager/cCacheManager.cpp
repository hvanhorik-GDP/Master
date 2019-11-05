#include "cCacheManager.h"
#include "cCacheManager_impl.h"

#include <iostream>
#include <cassert>

static cCacheManager_impl* impl;

cCacheManager::cCacheManager()
{
	if (!impl)
		impl = new cCacheManager_impl();
}

void cCacheManager::CleanUp()
{
	if (impl)
		delete impl;
	impl = NULL;
}

cCacheManager::~cCacheManager()
{
}
