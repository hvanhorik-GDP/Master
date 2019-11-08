#pragma once

#include "MessageManager/iMessageInterface.h"
#include "../../Libraries/ObjectItems/cObject_Model.h"


// cPhysics_Project_01_Tilter and example of using iMessageInterface
// This is used by the keyboard callback to handle manipluations of objects


class cPhysics_Project_01_Tilter : public iMessageInterface
{
public:
	cPhysics_Project_01_Tilter();
	
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
