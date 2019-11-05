
#include "GLFW_Callbacks.h"
#include "gl/GLCommon.h"

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "../Common/globalStuff.h"			// for find object
#include "../Common/pFindObjectByFriendlyName.h"

#include <stdio.h>		// for fprintf()

static bool isShiftKeyDownByAlone(int mods);
static bool isCtrlKeyDownByAlone(int mods);


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	const float cameraSPEED = 2.0f;

	if (!isShiftKeyDownByAlone(mods) && !isCtrlKeyDownByAlone(mods))
	{

		// Move the camera (A & D for left and right, along the x axis)
		if (key == GLFW_KEY_A)
		{
			old_cameraEye.x -= cameraSPEED;		// Move the camera -0.01f units
		}
		if (key == GLFW_KEY_D)
		{
			old_cameraEye.x += cameraSPEED;		// Move the camera +0.01f units
		}

		// Move the camera (Q & E for up and down, along the y axis)
		if (key == GLFW_KEY_Q)
		{
			old_cameraEye.y -= cameraSPEED;		// Move the camera -0.01f units
		}
		if (key == GLFW_KEY_E)
		{
			old_cameraEye.y += cameraSPEED;		// Move the camera +0.01f units
		}

		// Move the camera (W & S for towards and away, along the z axis)
		if (key == GLFW_KEY_W)
		{
			old_cameraEye.z -= cameraSPEED;		// Move the camera -0.01f units
		}
		if (key == GLFW_KEY_S)
		{
			old_cameraEye.z += cameraSPEED;		// Move the camera +0.01f units
		}

		if (key == GLFW_KEY_B)
		{
			// Shoot a bullet from the pirate ship
			// Find the pirate ship...
			// returns NULL (0) if we didn't find it.
			cObject_Model* pShip = pFindObjectByFriendlyName("PirateShip");
			// Maybe check to see if it returned something... 

			// Find the sphere#2
			cObject_Model* pBall = pFindObjectByFriendlyName("Sphere#2");

			// Set the location velocity for sphere#2
			pBall->positionXYZ = pShip->positionXYZ;
			pBall->inverseMass = 1.0f;		// So it's updated
			// 20.0 units "to the right"
			// 30.0 units "up"
			pBall->velocity = glm::vec3(15.0f, 20.0f, 0.0f);
			pBall->acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
			pBall->diffuseColour = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
		}//if ( key == GLFW_KEY_B )

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
		const float SHIP_SPEED_CHANGE = 0.01f;
		const float SHIP_ANGLE_CHANGE = 0.01f;

		cObject_Model* pShip = pFindObjectByFriendlyName("PirateShip");
		// Turn the ship around
		//if (key == GLFW_KEY_A)
		//{	// Left
		//	pShip->HACK_AngleAroundYAxis -= SHIP_ANGLE_CHANGE;
		//	pShip->rotationXYZ.y = pShip->HACK_AngleAroundYAxis;
		//}
		//if (key == GLFW_KEY_D)
		//{	// Right
		//	pShip->HACK_AngleAroundYAxis += SHIP_ANGLE_CHANGE;
		//	pShip->rotationXYZ.y = pShip->HACK_AngleAroundYAxis;
		//}
		//if (key == GLFW_KEY_W)
		//{	// Faster
		//	pShip->HACK_speed += SHIP_SPEED_CHANGE;
		//}
		//if (key == GLFW_KEY_S)
		//{	// Slower
		//	pShip->HACK_speed -= SHIP_SPEED_CHANGE;
		//}
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



void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	// Move the sphere to where the camera is and shoot the ball from there...

	cObject_Model* pTheBall = pFindObjectByFriendlyName("Sphere#1");

	// What's the velocity
	// Target - eye = direction
	glm::vec3 direction = glm::normalize(old_cameraTarget - old_cameraEye);

	float speed = 5.0f;

	pTheBall->velocity = direction * speed;
	pTheBall->positionXYZ = old_cameraEye;

	return;
}
