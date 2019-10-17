#include "cMessageManager.h"
#include "cMessageManager_impl.h"
#include <cassert>

static cMessageManager_impl* gMessageManager_impl = NULL;

cMessageManager::cMessageManager()
{
	if (!gMessageManager_impl)
		gMessageManager_impl = new cMessageManager_impl();
}

cMessageManager::~cMessageManager()
{
	// Global singleton so don't delete impl
}

bool cMessageManager::SendMessage(const iMessage& message)
{
	assert(gMessageManager_impl);
	return gMessageManager_impl->SendMessage(message);
}

bool cMessageManager::Register(const std::string& interfaceName, iMessageInterface* interface)
{
	assert(gMessageManager_impl);
	return gMessageManager_impl->Register(interfaceName, interface);
}

bool cMessageManager::SendWithResponse(const iMessage& send, iMessage& ret)
{
	assert(gMessageManager_impl);
	return gMessageManager_impl->SendWithResponse(send, ret);
}

bool cMessageManager::Broadcast(const iMessage& in)
{
	assert(gMessageManager_impl);
	return gMessageManager_impl->Broadcast(in);
}
