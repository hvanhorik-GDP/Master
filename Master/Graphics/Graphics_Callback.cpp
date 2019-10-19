#include "Graphics_Callback.h"

#include "GLCommon.h"

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "ObjectManager/cObjectManager.h"
#include "ObjectItems/cObject_Group.h"
#include "ObjectItems/cObject_World.h"
#include "Common/pFindObjectByFriendlyName.h"

#include "cGraphicsToObject.h"
#include <iostream>
#include <sstream>

static bool isShiftKeyDownByAlone(int mods);
static bool isCtrlKeyDownByAlone(int mods);

static bool gHasGraphicsObject = false;
static cGraphicsToObject* gGraphicsToObject = NULL;
static float adjustSpeed = 0.01f;

void Graphics_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Ignore key up
	if (action == 0)
		return;
	// We're getting reentrant code at startup
	if (!gHasGraphicsObject)
	{
		gHasGraphicsObject = true;
		gGraphicsToObject = new cGraphicsToObject();
	}
	if (!gGraphicsToObject)
		return;

	const float cameraSPEED = 2.0f;
	const float rgbAdjust = 0.01F;
	const float moveAdjust = 0.01F;
	const float scaleAdjust = 0.01f;
	const float rotateAdjust = 0.01f;

	int modifier = (isShiftKeyDownByAlone(mods)) ? -1 : 1;

	if (key == GLFW_KEY_F)
	{
		gGraphicsToObject->Focus();
	}
	else if (key == GLFW_KEY_W)
	{
		gGraphicsToObject->TargetWorld();
		adjustSpeed = cameraSPEED;
	}
	else if (key == GLFW_KEY_L)
	{
		gGraphicsToObject->TargetLights();
		adjustSpeed = moveAdjust;
	}
	else if (key == GLFW_KEY_M)
	{
		gGraphicsToObject->TargetModels();
		adjustSpeed = moveAdjust;
	}
	else if (key == GLFW_KEY_A)
	{
		gGraphicsToObject->TargetGroups();
		adjustSpeed = moveAdjust;
	}
	// Tab Key Shift to next visible object
	else if (key == GLFW_KEY_TAB)
	{
		if (isShiftKeyDownByAlone(mods))
			gGraphicsToObject->NextVisable();
		else
			gGraphicsToObject->NextVisable();
	}
	else if (key == GLFW_KEY_R)
	{
		gGraphicsToObject->AdjustColour(0, adjustSpeed * modifier);
	}
	else if (key == GLFW_KEY_G)
	{
		gGraphicsToObject->AdjustColour(1, adjustSpeed * modifier);
	}
	else if (key == GLFW_KEY_B)
	{
		gGraphicsToObject->AdjustColour(2, adjustSpeed * modifier);
	}

	// Position
	else if (key == GLFW_KEY_X)
	{
		gGraphicsToObject->Move(0, adjustSpeed * modifier);
	}
	else if (key == GLFW_KEY_Y)
	{
		gGraphicsToObject->Move(1, adjustSpeed * modifier);
	}
	else if (key == GLFW_KEY_Z)
	{
		gGraphicsToObject->Move(2, adjustSpeed * modifier);
	}

	// Rotate
	else if (key == GLFW_KEY_LEFT)
	{
		gGraphicsToObject->Rotate(1, adjustSpeed);
	}
	else if (key == GLFW_KEY_RIGHT)
	{
		gGraphicsToObject->Rotate(1, -adjustSpeed);
	}

	// Scale
	else if (key == GLFW_KEY_S)
	{
		gGraphicsToObject->Scale(adjustSpeed * modifier);
	}

	// Wireframe
	else if (key == GLFW_KEY_T)
	{
		gGraphicsToObject->SetWireFrame(true);
	}
	
	else if (key == GLFW_KEY_9)
	{
		gGraphicsToObject->SetDebug(false);
	}
	else if (key == GLFW_KEY_0)
	{
		gGraphicsToObject->SetDebug(true);
	}

	else if (key == GLFW_KEY_1)
	{
		gGraphicsToObject->Light(0, 0.99f);
	}
	else if (key == GLFW_KEY_2)
	{
		gGraphicsToObject->Light(0, 1.01f);
	}
	else if (key == GLFW_KEY_3)
	{
		gGraphicsToObject->Light(1, 0.99f);
	}
	else if (key == GLFW_KEY_4)
	{
		gGraphicsToObject->Light(1, 1.01f);
	}
	else if (key == GLFW_KEY_5)
	{
		gGraphicsToObject->Light(2, 0.99f);
	}
	else if (key == GLFW_KEY_6)
	{
		gGraphicsToObject->Light(2, 1.01f);
	}
	if (key == GLFW_KEY_V)
	{
//		sexyLightSpotInnerAngle -= 0.1f;
	}
	if (key == GLFW_KEY_B)
	{
//		sexyLightSpotInnerAngle += 0.1f;
	}
	if (key == GLFW_KEY_N)
	{
//		sexyLightSpotOuterAngle -= 0.1f;
	}
	if (key == GLFW_KEY_M)
	{
//		sexyLightSpotOuterAngle += 0.1f;
	}

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}




bool isShiftKeyDownByAlone(int mods)
{
	if (mods == GLFW_MOD_SHIFT)
	{
		// Shift key is down all by itself
		return true;
	}
	//// Ignore other keys and see if the shift key is down
	//if ((mods & GLFW_MOD_SHIFT) == GLFW_MOD_SHIFT)
	//{

	//}
	return false;
}

bool isCtrlKeyDownByAlone(int mods)
{
	if (mods == GLFW_MOD_CONTROL)
	{
		return true;
	}
	return false;
}



void Graphics_mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
#if 0
	// Move the sphere to where the camera is and shoot the ball from there...
	cObject_Model* pTheBall = pFindObjectByFriendlyName("Drop_Sphere");

	// What's the velocity
	// Target - eye = direction
//	glm::vec3 direction = glm::normalize(cameraTarget - cameraEye);
	//glm::vec3 position = glm::vec3(0.0f, 30.0, 0.0f);
	//glm::vec3 direction = glm::vec3(0.0f, -1.0f, 0.0f);
	{
		int min = 50;
		int max = 255;
		int r = rand() % (max - min) + min;
		int g = rand() % (max - min) + min;
		int b = rand() % (max - min) + min;
		glm::vec4 rgb = glm::vec4(float(r) / max, float(g) / max, float(b) / max, 1);
		pTheBall->objectColourRGBA = rgb;
	}
	{
		int min = -5;
		int max = 5;
		int x = rand() % (max - min) + min;
		int y = rand() % (50) + 20;
		int z = rand() % (max - min) + min;
		glm::vec3 pos = glm::vec3(float(x), float(y), float(z));
		pTheBall->positionXYZ = pos;
	}
	int scale = rand() % 5;
	pTheBall->scale = float(scale);
	pTheBall->SPHERE_radius = float(scale);
	pTheBall->velocity = glm::vec3(0.0f, 1.0f, 0.0f);
	pTheBall->accel = glm::vec3(0.0f, 0.0f, 0.0f);
#endif
	return;
}

