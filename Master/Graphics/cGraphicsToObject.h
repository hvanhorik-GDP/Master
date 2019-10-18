#pragma once

#include "MessageManager/iMessageInterface.h"
#include "ObjectItems/cObject_Model.h"

class cGraphicsToObject : public iMessageInterface
{
public:
	cGraphicsToObject();
	
	virtual const std::string& GetMyUID() const;

	// We only send messages
	virtual bool RecieveMessage(const iMessage& message) { return false; }

	// Recieve a message and reply
	virtual bool RecieveAndRespond(const iMessage& in, iMessage& reply) { return false; }

	void NextVisable();
	void NextInvisable();

	void Rotate(int plane, float value);
	void AdjustColour(int color, float value);
	void Move(int plane, float value);
	void Scale(float value);

	std::vector<cObject_Model*> m_Objects;
	cObject_Model* m_CurrentObject;
	int m_CurrentOffset = 0;
	bool m_lastWasVisable = true;
};
