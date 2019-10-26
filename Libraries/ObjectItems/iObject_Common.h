#pragma once

#include "iObject.h"
#include <rapidxml/rapidxml.hpp>
#include <glm/glm.hpp>

#include <string>
#include <vector>

class iItem;

class iObject_Common : public iObject
{
public:
	iObject_Common() {};
	virtual ~iObject_Common() {};

	// These are the four attributes that are part of every object
	virtual const std::string& GetType() const = 0;
	virtual const std::string& GetName() const = 0;
	virtual const std::string& GetAssetID() const = 0;

	// A visablity flags across all objects translates to playable for audio
	virtual bool IsVisable() const = 0;
	virtual bool IsObjectLocked() const = 0;

	// returns a pointer to any Asset Item that is associated with this object
	virtual iItem* GetItem() const = 0;

	// The objects parent group (if any)
	virtual iObject* GetParentObject() const = 0;

	// Raw XML - Get the root node and check for validity
	virtual bool IsXMLValid() const = 0;
	virtual rapidxml::xml_node<>* GetNode() const = 0;

	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const iObject_Common& val);
};
