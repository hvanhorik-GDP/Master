#pragma once


#include "GLCommon.h"
#include <glm/glm.hpp>

#include "AssetItems/cItem_Model.h"
#include "ObjectItems/cObject_Model.h"
#include "sModelDrawInfo.h"


#pragma comment(lib, "VAOManager.lib")


class iVAOManager
{
public:
	iVAOManager() {};
	virtual ~iVAOManager() {}

	// Takes a cMesh object and copies it into the GPU (as a VOA)

	virtual bool LoadModelIntoVAO(cItem_Model& theMesh, sModelDrawInfo& drawInfo) = 0;

	virtual void DrawObject(glm::mat4 m, cObject_Model* pCurrentObject) = 0;
};

