#pragma once

#include "iMessage.h"
#include "iMessageInterface.h"
#include <string>

// INFO6044 - iMessageManager is a mediator/singleton. It may become an abstract factory depending on
// future needs.
// It is desgined to send messages between any object that inherit from the class
// It will be using an XML version in the future, but due to time constraints I only implemented a 
// string version.
// You can 
//   Send messages 
//   Send with response
//   Broadcast - (future)
//   Register to recieve "Broadcast"
//    Each users of the class must have a unique ID

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

