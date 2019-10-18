#include "Graphics_Callback.h"

#include "GLCommon.h"

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "Common/globalStuff.h"	
#include "ObjectManager/cObjectManager.h"
#include "ObjectItems/cObject_Group.h"
#include "Common/pFindObjectByFriendlyName.h"

#include "cGraphicsToObject.h"
#include <iostream>
#include <sstream>

static bool isShiftKeyDownByAlone(int mods);
static bool isCtrlKeyDownByAlone(int mods);

static bool gHasGraphicsObject = false;
static cGraphicsToObject* gGraphicsToObject = NULL;


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

	if (!isShiftKeyDownByAlone(mods) && !isCtrlKeyDownByAlone(mods))
	{
		// Tab Key Shift to next visible object
		if (key == GLFW_KEY_TAB)
		{
			gGraphicsToObject->NextVisable();
		}
		if (key == GLFW_KEY_R)
		{
			gGraphicsToObject->AdjustColour(0, +rgbAdjust);
		}
		if (key == GLFW_KEY_G)
		{
			gGraphicsToObject->AdjustColour(1, +rgbAdjust);
		}
		if (key == GLFW_KEY_B)
		{
			gGraphicsToObject->AdjustColour(2, +rgbAdjust);
		}

		// Position
		if (key == GLFW_KEY_X)
		{
			gGraphicsToObject->Move(0, +moveAdjust);
		}
		if (key == GLFW_KEY_Y)
		{
			gGraphicsToObject->Move(1, +moveAdjust);
		}
		if (key == GLFW_KEY_Z)
		{
			gGraphicsToObject->Move(2, +moveAdjust);
		}

		// Rotate
		if (key == GLFW_KEY_LEFT)
		{
			gGraphicsToObject->Rotate(1, +rotateAdjust);
		}
		if (key == GLFW_KEY_RIGHT)
		{
			gGraphicsToObject->Rotate(1, -rotateAdjust);
		}

		// Scale
		if (key == GLFW_KEY_S)
		{
			gGraphicsToObject->Scale(+scaleAdjust);
		}
	}
	if (isShiftKeyDownByAlone(mods))
	{
		if (key == GLFW_KEY_TAB)
		{
			gGraphicsToObject->NextInvisable();
		}

		if (key == GLFW_KEY_R)
		{
			gGraphicsToObject->AdjustColour(0, -rgbAdjust);
		}
		if (key == GLFW_KEY_G)
		{
			gGraphicsToObject->AdjustColour(1, -rgbAdjust);
		}
		if (key == GLFW_KEY_B)
		{
			gGraphicsToObject->AdjustColour(2, -rgbAdjust);
		}


		// Position
		if (key == GLFW_KEY_X)
		{
			gGraphicsToObject->Move(0, -moveAdjust);
		}
		if (key == GLFW_KEY_Y)
		{
			gGraphicsToObject->Move(1, -moveAdjust);
		}
		if (key == GLFW_KEY_Z)
		{
			gGraphicsToObject->Move(2, -moveAdjust);
		}

		// Scale
		if (key == GLFW_KEY_S)
		{
			gGraphicsToObject->Scale( -scaleAdjust);
		}

#if 0
		// move the light
		if (key == GLFW_KEY_A)
		{
			sexyLightPosition.x -= cameraSPEED;		// Move the camera -0.01f units
		}
		if (key == GLFW_KEY_D)
		{
			sexyLightPosition.x += cameraSPEED;		// Move the camera +0.01f units
		}

		// Move the camera (Q & E for up and down, along the y axis)
		if (key == GLFW_KEY_Q)
		{
			sexyLightPosition.y -= cameraSPEED;		// Move the camera -0.01f units
		}
		if (key == GLFW_KEY_E)
		{
			sexyLightPosition.y += cameraSPEED;		// Move the camera +0.01f units
		}

		// Move the camera (W & S for towards and away, along the z axis)
		if (key == GLFW_KEY_W)
		{
			sexyLightPosition.z -= cameraSPEED;		// Move the camera -0.01f units
		}
		if (key == GLFW_KEY_S)
		{
			sexyLightPosition.z += cameraSPEED;		// Move the camera +0.01f units
		}

		if (key == GLFW_KEY_1)
		{
			sexyLightConstAtten *= 0.99f;			// 99% of what it was
		}
		if (key == GLFW_KEY_2)
		{
			sexyLightConstAtten *= 1.01f;			// 1% more of what it was
		}
		if (key == GLFW_KEY_3)
		{
			sexyLightLinearAtten *= 0.99f;			// 99% of what it was
		}
		if (key == GLFW_KEY_4)
		{
			sexyLightLinearAtten *= 1.01f;			// 1% more of what it was
		}
		if (key == GLFW_KEY_5)
		{
			sexyLightQuadraticAtten *= 0.99f;			// 99% of what it was
		}
		if (key == GLFW_KEY_6)
		{
			sexyLightQuadraticAtten *= 1.01f;			// 1% more of what it was
		}
		if (key == GLFW_KEY_V)
		{
			sexyLightSpotInnerAngle -= 0.1f;
		}
		if (key == GLFW_KEY_B)
		{
			sexyLightSpotInnerAngle += 0.1f;
		}
		if (key == GLFW_KEY_N)
		{
			sexyLightSpotOuterAngle -= 0.1f;
		}
		if (key == GLFW_KEY_M)
		{
			sexyLightSpotOuterAngle += 0.1f;
		}


		if (key == GLFW_KEY_9)
		{
			bLightDebugSheresOn = false;
		}
		if (key == GLFW_KEY_0)
		{
			bLightDebugSheresOn = true;
		}
#endif
		
	}//if (isShiftKeyDownByAlone(mods))


	// Camera moved to ctrl key
	if (isCtrlKeyDownByAlone(mods))
	{
		// Move the camera (A & D for left and right, along the x axis)
		if (key == GLFW_KEY_A)
		{
			cameraEye.x -= cameraSPEED;		// Move the camera -0.01f units
		}
		if (key == GLFW_KEY_D)
		{
			cameraEye.x += cameraSPEED;		// Move the camera +0.01f units
		}

		// Move the camera (Q & E for up and down, along the y axis)
		if (key == GLFW_KEY_Q)
		{
			cameraEye.y -= cameraSPEED;		// Move the camera -0.01f units
		}
		if (key == GLFW_KEY_E)
		{
			cameraEye.y += cameraSPEED;		// Move the camera +0.01f units
		}

		// Move the camera (W & S for towards and away, along the z axis)
		if (key == GLFW_KEY_W)
		{
			cameraEye.z -= cameraSPEED;		// Move the camera -0.01f units
		}
		if (key == GLFW_KEY_S)
		{
			cameraEye.z += cameraSPEED;		// Move the camera +0.01f units
		}

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

