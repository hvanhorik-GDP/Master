#include "Physics_Callback.h"

#include "GLCommon.h"

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "Common/globalStuff.h"	
#include "ObjectManager/cObjectManager.h"
#include "ObjectItems/cObject_Group.h"
#include "ObjectItems/cObject_World.h"
#include "Common/pFindObjectByFriendlyName.h"

#include "cPhysicsTilter.h"
#include <iostream>

static bool isShiftKeyDownByAlone(int mods);
static bool isCtrlKeyDownByAlone(int mods);



static cPhysicsTilter* gTilter = NULL;


void Physics_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (!gTilter)
		gTilter = new cPhysicsTilter();

	const float cameraSPEED = 2.0f;

	if (!isShiftKeyDownByAlone(mods) && !isCtrlKeyDownByAlone(mods))
	{
		cObjectManager manager;
		//TODO - for now only a single world
		auto object = manager.FindObjectByName("world");
		assert(object);
		cObject_World* world = dynamic_cast<cObject_World*>(object);

		// Move the camera (A & D for left and right, along the x axis)
		if (key == GLFW_KEY_A)
		{
			world->cameraEye.x -= cameraSPEED;		// Move the camera -0.01f units
		}
		if (key == GLFW_KEY_D)
		{
			world->cameraEye.x += cameraSPEED;		// Move the camera +0.01f units
		}

		// Move the camera (Q & E for up and down, along the y axis)
		if (key == GLFW_KEY_Q)
		{
			world->cameraEye.y -= cameraSPEED;		// Move the camera -0.01f units
		}
		if (key == GLFW_KEY_E)
		{
			world->cameraEye.y += cameraSPEED;		// Move the camera +0.01f units
		}

		// Move the camera (W & S for towards and away, along the z axis)
		if (key == GLFW_KEY_W)
		{
			world->cameraEye.z -= cameraSPEED;		// Move the camera -0.01f units
		}
		if (key == GLFW_KEY_S)
		{
			world->cameraEye.z += cameraSPEED;		// Move the camera +0.01f units
		}

		const float planeTilt = 0.0005f;
		const int x = 0;
		const int y = 1;
		const int z = 2;

		if (key == GLFW_KEY_RIGHT)
		{
			gTilter->tiltPlane(z, planeTilt);
		}
		if (key == GLFW_KEY_LEFT)
		{
			gTilter->tiltPlane(z, -planeTilt);
		}
		if (key == GLFW_KEY_UP)
		{
			gTilter->tiltPlane(x, planeTilt);
		}
		if (key == GLFW_KEY_DOWN)
		{
			gTilter->tiltPlane(x, -planeTilt);
		}
	}

	if (isShiftKeyDownByAlone(mods))
	{
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

	}//if (isShiftKeyDownByAlone(mods))


	// Moving the pirate ship in a certain direction
	if (isCtrlKeyDownByAlone(mods))
	{

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



void Physics_mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
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
	pTheBall->inverseMass = 1.0f;
	return;
}

