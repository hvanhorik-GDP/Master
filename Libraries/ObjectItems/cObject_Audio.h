#pragma once
#include "cObject_Common.h"
#include <vector>

class cObject_Audio : public cObject_Common
{
public:
	// This structure matches the file, so that our life is
	//   simpler and happier, and we all get along.

	cObject_Audio() {};				// Get's filled in by physics

	cObject_Audio(const std::string& type,
		const std::string& name,
		const std::string& asset_id,
		rapidxml::xml_node<>* node);
	virtual ~cObject_Audio();

	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const cObject_Audio& val);

private:
	friend class cObjectManager_Audio;
};

