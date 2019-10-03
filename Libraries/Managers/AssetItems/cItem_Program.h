#pragma once

#include "cItem_Common.h"
#include <vector>

class cItem_Program : public cItem_Common
{
public:


	struct sUniform
	{
		unsigned int m_ID;
		int m_index;
		unsigned int m_type;
		int m_size;
		std::string m_name;
	};

	typedef sUniform sAttribute;
	typedef std::vector<sUniform> vecUniforms;
	typedef std::vector<sAttribute> vecAttributes;

	typedef std::vector<iItem*> vecShaders;

	cItem_Program(std::string id,
		std::string path,
		rapidxml::xml_node<>* parent,
		std::size_t index);
	virtual ~cItem_Program();

	unsigned int GetID() const;
	vecShaders* GetShaders();
	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const cItem_Program& val);

private:
	cItem_Program();				// Bad Consructor so hide

	unsigned int m_ID = 0;
	bool m_valid;
	std::string m_error;

	vecShaders m_vecShaders;
	vecUniforms m_vecUniforms;
	vecAttributes m_vecAttributes;

	friend class cAssetManager_Programs;
	friend class cProgramLoader;
};

