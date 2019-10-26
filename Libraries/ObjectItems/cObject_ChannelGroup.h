#pragma once

#include "cObject_Common.h"
#include "cObject_ChannelControl.h"
#include "cObject_3d.h"
#include "cObject_Physics.h"
#include "cObject_Alias.h"

#include <vector>

class cObject_ChannelGroup
	: public cObject_Common							// Need common items
	, public cObject_ChannelControl					// Full channel control
	, public cObject_3d								// This is a 3d Object
	, public cObject_Physics						// and physics applies to it
	, public cObject_Alias							// This is a grouping
{
public:
	// This structure matches the file, so that our life is
	//   simpler and happier, and we all get along.

	cObject_ChannelGroup() {};				// Get's filled in by physics

	cObject_ChannelGroup(const std::string& type,
		const std::string& name,
		const std::string& asset_id,
		rapidxml::xml_node<>* node);
	virtual ~cObject_ChannelGroup();

	virtual iObject* Clone(const std::string& newName) final;

	// Recieve a message
	virtual bool RecieveMessage(const iMessage& message) final;

	// Recieve a message and reply
	virtual bool RecieveAndRespond(const iMessage& in, iMessage& reply) final;

	virtual void IntegrationStep(float deltaTime) final;

	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const cObject_ChannelGroup& val);


private:
	friend class cObjectManager_ChannelGroup;
};

