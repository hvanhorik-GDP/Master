#pragma once
#include "iMessageManager.h"

#include <map>

class cMessageManager_impl : public iMessageManager
{
private:
	typedef std::map<std::string, iMessageInterface*> mapMessageInterfaces;

	cMessageManager_impl();
	virtual ~cMessageManager_impl();

	virtual bool Register(const std::string&interfaceName, iMessageInterface* interface);

	// Send a message to a reciever with no reply
	virtual bool SendMessage(const iMessage& message);

	// Send a message to a reiever and expect a reply
	virtual bool SendWithResponse(const iMessage& send, iMessage& ret);

	// Broadcast a message to anyone who is interested
	virtual bool Broadcast(const iMessage& in);


private:
	friend class cMessageManager;
	mapMessageInterfaces m_mapMessageInterfaces;
};

