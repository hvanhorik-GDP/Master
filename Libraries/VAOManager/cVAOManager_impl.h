#pragma once
#include "iVAOManager.h"

#include <map>

class cVAOManager_impl : public iVAOManager
{
private:
	cVAOManager_impl(GLint shaderProgramID);
	// Takes a cMesh object and copies it into the GPU (as a VOA)
	bool LoadModelIntoVAO(cItem_Model &theMesh,	sModelDrawInfo &drawInfo);

	friend class cVAOManager;
	void DrawObject(glm::mat4 m, cObject_Model* pCurrentObject);

	std::string getLastError(bool bAndClear = true);

private:
	cVAOManager_impl();
	// We don't want to return an int, likely
	bool FindDrawInfoByModelName(std::string filename,
		sModelDrawInfo& drawInfo);

	std::map< std::string, sModelDrawInfo > m_map_ModelName_to_VAOID;
	GLint m_shaderProgID;
};
