#pragma once
#include "cObject_Common.h"
#include <vector>

class cObject_ChannelControl : public cObject_Common
{
public:
	// This structure matches the file, so that our life is
	//   simpler and happier, and we all get along.

	cObject_ChannelControl() {};				// Get's filled in by physics

	cObject_ChannelControl(const std::string& type,
		const std::string& name,
		const std::string& asset_id,
		rapidxml::xml_node<>* node);
	virtual ~cObject_ChannelControl();

	virtual void IntegrationStep(float deltaTime) = 0;

	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const cObject_ChannelControl& val);

private:
	friend class cObjectManager_Channel;
};

