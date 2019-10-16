#include "cVAOManager.h"
#include "cVAOManager_impl.h"
#include <cassert>

static cVAOManager_impl* gVAOManager = NULL;

cVAOManager::cVAOManager(GLint shaderProgramID)
{
	assert(gVAOManager == NULL);	// can only be called once
	gVAOManager = new cVAOManager_impl(shaderProgramID);
}

cVAOManager::cVAOManager()
{
	assert(gVAOManager != NULL);	// Someone has to init the thing by calling above constructor
}

cVAOManager::~cVAOManager()
{
}

// Takes a cMesh object and copies it into the GPU (as a VOA)

bool cVAOManager::LoadModelIntoVAO(cItem_Model& theMesh, sModelDrawInfo& drawInfo)
{
	assert(gVAOManager);
	return gVAOManager->LoadModelIntoVAO(theMesh, drawInfo);
}

void cVAOManager::DrawObject(glm::mat4 m, cObject_Model* pCurrentObject)
{
	assert(gVAOManager);
	gVAOManager->DrawObject(m, pCurrentObject);
}
