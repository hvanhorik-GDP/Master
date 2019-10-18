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

	void TargetModels();
	void TargetLights();
	void TargetGroups();
	void TargetWorld();

	void NextVisable();
	void NextInvisable();

	void Rotate(int plane, float value);
	void AdjustColour(int color, float value);
	void Move(int plane, float value);
	void Scale(float value);
	void Light(int type, float value);
	void SetDebug(bool value);

	std::vector<iObject *> m_Objects;
	iObject* m_CurrentObject;
	int m_NextOffset = 0;
	bool m_lastWasVisable = true;
	bool m_debug = false;
};
