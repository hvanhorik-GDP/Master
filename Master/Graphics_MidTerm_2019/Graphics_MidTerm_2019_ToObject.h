#pragma once

#include "MessageManager/iMessageInterface.h"
#include "ObjectItems/cObject_Model.h"

class Graphics_MidTerm_2019_ToObject : public iMessageInterface
{
public:
	Graphics_MidTerm_2019_ToObject();
	
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
	void SetWireFrame(bool value);
	void Focus();

	void Duplicate();
	void SetCamera(glm::vec3 target, glm::vec3 eye);


	std::vector<iObject *> m_Objects;
	iObject* m_CurrentObject;
	int m_NextOffset = 0;
	bool m_lastWasVisable = true;
	bool m_debug = false;
};

void Graphics_MidTerm_2019_CalculateBounds(rapidxml::xml_node<>* parent);
void Graphics_MidTerm_2019_ShiftAllObjects(rapidxml::xml_node<>* parent);

void Graphics_MidTerm_2019_Flicker();
void Graphics_MidTerm_2019_FlyCamera();