#pragma once
#include "cItem_Common.h"
#include <fmod/fmod.hpp>

class cItem_Shader : public cItem_Common
{
public:

	cItem_Shader(std::string id,
		std::string path,
		rapidxml::xml_node<>* parent,
		std::size_t index);
	virtual ~cItem_Shader();
	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const cItem_Shader& val);

private:
	cItem_Shader();				// Bad Consructor

	friend class cAssetManager_Audios;

};

