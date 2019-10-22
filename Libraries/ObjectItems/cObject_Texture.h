#pragma once
#include "cObject_Common.h"
#include <vector>

class cObject_Texture : public cObject_Common
{
public:
	// This structure matches the file, so that our life is
	//   simpler and happier, and we all get along.

	cObject_Texture() {};				// Get's filled in by physics

	cObject_Texture(const std::string& type,
		const std::string& name,
		const std::string& asset_id,
		rapidxml::xml_node<>* node);
	virtual ~cObject_Texture();

	virtual void IntegrationStep(float deltaTime) final {}

	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const cObject_Texture& val);

private:
	friend class cObjectManager_Texture;
};

