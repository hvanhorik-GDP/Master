#pragma once

#include "MessageManager/iMessageInterface.h"
#include "ObjectItems/cObject_Model.h"


// Patterns_MidTerm_2019_Tilter and example of using iMessageInterface
// This is used by the keyboard callback to handle manipluations of objects


class Patterns_MidTerm_2019_Tilter : public iMessageInterface
{
public:
	Patterns_MidTerm_2019_Tilter();
	
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
