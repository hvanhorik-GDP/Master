#pragma once
#include "cObject_ChannelControl.h"
#include <vector>

class cObject_ChannelGroup : public cObject_ChannelControl
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

	virtual void IntegrationStep(float deltaTime) final {}

	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const cObject_ChannelGroup& val);

private:
	friend class cObjectManager_ChannelGroup;
};

