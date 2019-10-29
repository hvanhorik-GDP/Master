#pragma once

#include <string>

class iMessage;

// iMessageInterface is a part of the iMessageManager
// This is what anyone using the interface inherit from

class iMessageInterface
{
public:
	iMessageInterface() {}
	virtual ~iMessageInterface() {};

	// Everyone has a universal ID
	virtual const std::string& GetMyUID() const = 0;

	// Recieve a message
	virtual bool RecieveMessage(const iMessage& message) = 0;

	// Recieve a message and reply
	virtual bool RecieveAndRespond(const iMessage& in, iMessage& reply) = 0;

};

