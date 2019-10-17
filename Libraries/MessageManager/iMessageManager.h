#pragma once

#include "iMessage.h"
#include "iMessageInterface.h"
#include <string>

class iMessageManager
{
public:
	iMessageManager() {}
	virtual ~iMessageManager() {}

	// Register thyself
	virtual bool Register(const std::string& interfaceName, iMessageInterface* interface) = 0;

	// Just send a message to the reciever
	virtual bool SendMessage(const iMessage& message) = 0;
	
	// Send a message and expect a response
	virtual bool SendWithResponse(const iMessage& send, iMessage& ret) = 0;

	// Broadcast a message to anyone who is interested
	virtual bool Broadcast(const iMessage& in) = 0;
};

