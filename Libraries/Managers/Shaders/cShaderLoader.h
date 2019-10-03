#pragma once
#include "../AssetItems/cItem_Shader.h"

class cShaderLoader
{
public:
	cShaderLoader();
	~cShaderLoader();
	bool Load(cItem_Shader& shader);
	
	std::string GetLastError();
private:
	bool LoadSourceFromFile(cItem_Shader& shader);
	bool CompileShaderFromSource(cItem_Shader& shader, std::string& error);
	bool WasThereACompileError(unsigned int shaderID, std::string& errorText);

	std::string m_lastError;

};

