#pragma once
#include "cObject_Common.h"
#include <vector>

class cObject_Sound : public cObject_Common
{
public:
	// This structure matches the file, so that our life is
	//   simpler and happier, and we all get along.

	cObject_Sound() {};				// Get's filled in by physics

	cObject_Sound(const std::string& type,
		const std::string& name,
		const std::string& asset_id,
		rapidxml::xml_node<>* node);
	virtual ~cObject_Sound();

	virtual void IntegrationStep(float deltaTime) final {}

	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const cObject_Sound& val);

private:
	friend class cObjectManager_Sound;
};
