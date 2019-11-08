#include "Test_Callback.h"

#include "gl/GLCommon.h"

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "ObjectManager/cObjectManager.h"
#include "ObjectItems/cObject_Group.h"
#include "ObjectItems/cObject_World.h"

#include <iostream>
#include <sstream>
#include <time.h>

static bool isShiftKeyDownByAlone(int mods);
static bool isCtrlKeyDownByAlone(int mods);

static bool gHasGraphicsObject = false;
static float adjustSpeed = 0.01f;
extern bool gFlyCamera;

void Test_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Ignore key up
	if (action == 0)
		return;

	
	const float cameraSPEED = 1.5f;
	const float rgbAdjust = 0.01F;
	const float moveAdjust = 0.01F;
	const float scaleAdjust = 0.01f;
	const float rotateAdjust = 0.01f;
	static float speed = 1;

	int modifier = (isShiftKeyDownByAlone(mods)) ? -speed : speed;


	
	if (key == GLFW_KEY_EQUAL)
	{
		speed *= 1.10f;
		if (speed < 1)
			speed = 1;
	}
	if (key == GLFW_KEY_MINUS)
	{
		speed *= 0.90f;
		if (speed < 1)
			speed = 1;
	}


	//// Position
	//if (key == GLFW_KEY_X)
	//{
	//	gGraphicsToObject->Move(0, cameraSPEED * modifier);
	//}
	//else if (key == GLFW_KEY_Y)
	//{
	//	gGraphicsToObject->Move(1, cameraSPEED * modifier);
	//}
	//else if (key == GLFW_KEY_Z)
	//{
	//	gGraphicsToObject->Move(2, cameraSPEED* modifier);
	//}

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



void Test_mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
}

