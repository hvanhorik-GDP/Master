#pragma once
#include "GLCommon.h"

#include "Physics/cPhysics.h"
#include "VAOManager/cVAOManager.h"
#include "DebugRenderer/cDebugRenderer.h"

#include <string>
#include <vector>

void HandleDebugBallPhysics(GLuint shaderProgID,
	cPhysics* pPhsyics,
	cVAOManager* pTheVAOManager,
	cDebugRenderer* pDebugRenderer,
	std::map<std::string, cItem_Model*>* mapLoaded);
