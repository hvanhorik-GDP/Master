#pragma once
#include "cObject_Common.h"
#include <vector>

class cObject_Font : public cObject_Common
{
public:
	// This structure matches the file, so that our life is
	//   simpler and happier, and we all get along.

	cObject_Font() {};				// Get's filled in by physics

	cObject_Font(const std::string& type,
		const std::string& name,
		const std::string& asset_id,
		rapidxml::xml_node<>* node);
	virtual ~cObject_Font();

	virtual iObject* Clone(const std::string& newName) final;

	virtual void IntegrationStep(float deltaTime) final {}

	// Recieve a message
	virtual bool RecieveMessage(const iMessage& message) final;

	// Recieve a message and reply
	virtual bool RecieveAndRespond(const iMessage& in, iMessage& reply) final;

	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const cObject_Font& val);

private:
	friend class cObjectManager_Font;
};

