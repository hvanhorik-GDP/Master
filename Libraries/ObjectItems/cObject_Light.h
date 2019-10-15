#pragma once
#include "cObject_Common.h"
#include <vector>

class cObject_Light : public cObject_Common
{
public:
	// This structure matches the file, so that our life is
	//   simpler and happier, and we all get along.

	cObject_Light() {};				// Get's filled in by physics

	cObject_Light(const std::string& type,
		const std::string& name,
		const std::string& asset_id,
		rapidxml::xml_node<>* node);
	virtual ~cObject_Light();

	virtual void IntegrationStep(float deltaTime) final {}

	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const cObject_Light& val);

private:
	friend class cObjectManager_Light;
};

