#pragma once
#include "cObject_Group.h"
#include <vector>

class cObject_World : public cObject_Group			// The world is just like a group
{
public:
	// This structure matches the file, so that our life is
	//   simpler and happier, and we all get along.

	cObject_World() {};				// Get's filled in by physics

	cObject_World(const std::string& type,
		const std::string& name,
		const std::string& asset_id,
		rapidxml::xml_node<>* node);
	virtual ~cObject_World();

	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const cObject_World& val);

private:
	friend class cObjectManager_World;
};

