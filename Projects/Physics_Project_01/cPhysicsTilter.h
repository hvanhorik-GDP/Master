#pragma once

#include "MessageManager/iMessageInterface.h"
#include "../../Libraries/ObjectItems/cObject_Model.h"


// cPhysicsTilter and example of using iMessageInterface
// This is used by the keyboard callback to handle manipluations of objects


class cPhysicsTilter : public iMessageInterface
{
public:
	cPhysicsTilter();
	
	virtual const std::string& GetMyUID() const;

	// We only send messages
	virtual bool RecieveMessage(const iMessage& message) { return false; }

	// Recieve a message and reply
	virtual bool RecieveAndRespond(const iMessage& in, iMessage& reply) { return false; }
	void tiltPlane(int plane, float value);
	void track();
private:
	cObject_Model* m_trackObject;
};
