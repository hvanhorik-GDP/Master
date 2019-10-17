#pragma once
#include "iMessageManager.h"

#include <string>
#include <map>

class cMessageManager : public iMessageManager
{
public:

	cMessageManager();
	virtual ~cMessageManager();

	// Register an interface
	virtual bool Register(const std::string& interfaceName, iMessageInterface* interface);

	// Send a message to a reciever with no reply
	virtual bool SendMessage(const iMessage& message);

	// Send a message to a reciever and expect a response
	virtual bool SendWithResponse(const iMessage& send, iMessage& ret);

	// Broadcast a message to anyone who is interested
	virtual bool Broadcast(const iMessage& in);

};

