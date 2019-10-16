#pragma once
#include "iVAOManager.h"

class cVAOManager : public iVAOManager
{
public:
	cVAOManager(GLint shaderProgramID);
	cVAOManager();
	virtual ~cVAOManager();

	// Takes a cMesh object and copies it into the GPU (as a VOA)

	virtual bool LoadModelIntoVAO(cItem_Model& theMesh, sModelDrawInfo& drawInfo);

	virtual void DrawObject(glm::mat4 m, cObject_Model* pCurrentObject);

};

