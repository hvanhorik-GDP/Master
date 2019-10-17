#pragma once


#include "MessageManager/iMessageInterface.h"

class cGraphicsTilter : public iMessageInterface
{
public:
	cGraphicsTilter();
	
	virtual const std::string& GetMyUID() const;

	// We only send messages
	virtual bool RecieveMessage(const iMessage& message) { return false; }

	// Recieve a message and reply
	virtual bool RecieveAndRespond(const iMessage& in, iMessage& reply) { return false; }
	void tiltPlane(int plane, float value);
};
