#pragma once

#include "GLCommon.h"
#include "ObjectItems/cObject_Model.h"


// These are defined in theMain.cpp
extern glm::vec3 old_cameraEye;
extern glm::vec3 old_cameraTarget;
extern glm::vec3 old_upVector;

extern glm::vec3 sexyLightPosition;
extern float sexyLightConstAtten;
extern float sexyLightLinearAtten;  
extern float sexyLightQuadraticAtten;

extern float sexyLightSpotInnerAngle;
extern float sexyLightSpotOuterAngle;

// This is a "normalized" direction
// (i.e. the length is 1.0f)
extern glm::vec3 sexyLightSpotDirection;

extern bool bLightDebugSheresOn;

extern GLFWwindow* window;
