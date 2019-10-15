#pragma once
#include "cObject_Common.h"
#include <vector>

class cObject_Physics : public cObject_Common
{
public:
	// This structure matches the file, so that our life is
	//   simpler and happier, and we all get along.

	cObject_Physics() {};				// Get's filled in by physics

	cObject_Physics(const std::string& type,
		const std::string& name,
		const std::string& asset_id,
		rapidxml::xml_node<>* node);
	virtual ~cObject_Physics();

	virtual void IntegrationStep(float deltaTime) final {}

	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const cObject_Physics& val);

private:
	friend class cObjectManager_Physics;
};

