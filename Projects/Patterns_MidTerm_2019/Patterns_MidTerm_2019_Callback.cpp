#include "Patterns_MidTerm_2019_Callback.h"

#include "gl/GLCommon.h"

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

//#include "Common/globalStuff.h"	
#include "ObjectManager/cObjectManager.h"
#include "ObjectItems/cObject_Group.h"
#include "ObjectItems/cObject_World.h"

#include "Patterns_MidTerm_2019_Tilter.h"
#include <iostream>

static bool isShiftKeyDownByAlone(int mods);
static bool isCtrlKeyDownByAlone(int mods);

Patterns_MidTerm_2019_Tilter* gTilter = NULL;


void Patterns_MidTerm_2019_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Ignore key up (double hit)
	if (action == 0)
		return;

	const float cameraSPEED = 2.0f;

	cObjectManager manager;
	//TODO - for now only a single world
	auto object = manager.FindObjectByName("world");
	assert(object);
	cObject_World* world = dynamic_cast<cObject_World*>(object);
	assert(world);
	auto parentNode = world->GetNode()->parent();
	assert(parentNode);

	if (!isShiftKeyDownByAlone(mods) && !isCtrlKeyDownByAlone(mods))
	{
		// Move the camera (A & D for left and right, along the x axis)
		if (key == GLFW_KEY_X)
		{
			world->cameraEye.x += cameraSPEED;				// Move the camera +0.01f units
			manager.SaveObject(world, parentNode);
		}

		if (key == GLFW_KEY_Y)
		{
			world->cameraEye.y += cameraSPEED;		// Move the camera +0.01f units
			manager.SaveObject(world, parentNode);
		}

		if (key == GLFW_KEY_Z)
		{
			world->cameraEye.z += cameraSPEED;		// Move the camera +0.01f units
			manager.SaveObject(world, parentNode);
		}

		const float planeTilt = 0.0005f;
		const int x = 0;
		const int y = 1;
		const int z = 2;
	}

	if (isShiftKeyDownByAlone(mods))
	{
		if (key == GLFW_KEY_X)
		{
			world->cameraEye.x -= cameraSPEED;		// Move the camera -0.01f units
		}
		// Move the camera (Q & E for up and down, along the y axis)
		if (key == GLFW_KEY_Y)
		{
			world->cameraEye.y -= cameraSPEED;		// Move the camera -0.01f units
		}
		// Move the camera (W & S for towards and away, along the z axis)
		if (key == GLFW_KEY_Z)
		{
			world->cameraEye.z -= cameraSPEED;		// Move the camera -0.01f units
		}

	}//if (isShiftKeyDownByAlone(mods))


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


void Patterns_MidTerm_2019_mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	// Move the sphere to where the camera is and shoot the ball from there...
	auto temp = cObjectManager().FindObjectByName("Drop_Sphere");
	cObject_Model* pTheBall = dynamic_cast<cObject_Model*>(temp);
	assert(pTheBall);

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
	// HACK - TODO - turn off scale
//	int scale = rand() % 5;
//	pTheBall->scale = float(scale);
//	pTheBall->SPHERE_radius = float(scale);
	pTheBall->velocity = glm::vec3(0.0f, 1.0f, 0.0f);
	pTheBall->acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
	pTheBall->inverseMass = 1.0f;
	return;
}
