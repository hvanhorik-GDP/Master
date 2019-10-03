#pragma once
#include "../AssetItems/cItem_Program.h"

class cProgramLoader
{
public:
	cProgramLoader();
	~cProgramLoader();
	bool Load(cItem_Program& info);

	std::string GetLastError();
private:
	bool WasThereALinkError(unsigned int programID, std::string& errorText);

	void GetAttributes(cItem_Program& info);
	void GetUniforms(cItem_Program& info);

	std::string m_lastError;
};

