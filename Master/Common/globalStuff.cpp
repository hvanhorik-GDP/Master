#include "globalStuff.h"

GLFWwindow* window;

glm::vec3 old_cameraEye = glm::vec3(0.0, 80.0, -80.0);
glm::vec3 old_cameraTarget = glm::vec3(0.0f, 10.0, 0.0f);
glm::vec3 old_upVector = glm::vec3(0.0f, 1.0f, 0.0f);

glm::vec3 sexyLightPosition = glm::vec3(-25.0f, 200.0f, 0.0f);
float sexyLightConstAtten = 0.0000001f;			// not really used (can turn off and on the light)
float sexyLightLinearAtten = 0.002f;
float sexyLightQuadraticAtten = 0.0000001f;

float sexyLightSpotInnerAngle = 5.0f;
float sexyLightSpotOuterAngle = 7.5f;
// This is a "normalized" direction
// (i.e. the length is 1.0f)
glm::vec3 sexyLightSpotDirection = glm::vec3(0.0f, -1.0f, 0.0f);

bool bLightDebugSheresOn = false;
