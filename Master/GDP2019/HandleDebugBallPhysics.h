#pragma once
#include "GLCommon.h"

#include "Physics/cPhysics_Henky.h"
#include "VAOManager/cVAOManager.h"
#include "DebugRenderer/cDebugRenderer.h"

#include <string>
#include <vector>

void HandleDebugBallPhysics(GLuint shaderProgID,
	cPhysics_Henky* pPhsyics,
	cVAOManager* pTheVAOManager,
	cDebugRenderer* pDebugRenderer,
	std::map<std::string, cItem_Model*>* mapLoaded);
