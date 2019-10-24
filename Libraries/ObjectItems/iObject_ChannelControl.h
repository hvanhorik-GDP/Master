#pragma once
#include "cObject_Common.h"
#include <vector>

class iObject_ChannelControl
{
public:
	// This structure matches the file, so that our life is
	//   simpler and happier, and we all get along.

	iObject_ChannelControl() {};				// Get's filled in by physics

	virtual ~iObject_ChannelControl() {}

	virtual void IntegrationStep(float deltaTime) = 0;

	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const iObject_ChannelControl& val);

private:
	friend class cObjectManager_Channel;
};

