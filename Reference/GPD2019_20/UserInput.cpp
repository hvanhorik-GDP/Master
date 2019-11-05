#include "GLCommon.h"
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "GFLW_callbacks.h"
#include "globalStuff.h"			// for find object

#include <stdio.h>		// for fprintf()
#include <iostream>

#include "FlyCamera/cFlyCamera.h"

bool isOnlyShiftKeyDown(int mods);
bool isOnlyCtrlKeyDown(int mods);
bool isOnlyAltKeyDown(int mods);
bool isShiftDown(GLFWwindow* window);
bool isCtrlDown(GLFWwindow* window);
bool isAltDown(GLFWwindow* window);
bool areAllModifiersUp(GLFWwindow* window);

bool g_MouseIsInsideWindow = false;
bool g_MouseLeftButtonIsDown = false;

// Declared in theMain
extern cFlyCamera* g_pFlyCamera;

void cursor_enter_callback(GLFWwindow* window, int entered)
{
	if (entered)
	{
		::g_MouseIsInsideWindow = true;
		std::cout << "Mouse moved inside window" << std::endl;
	}
	else
	{
		::g_MouseIsInsideWindow = false;
		std::cout << "Mouse moved outside window" << std::endl;
	}
	return;
}//cursor_enter_callback(...

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	const float CAMERASPEED = 2.0f;

	if ( !isShiftDown(window) && !isCtrlDown(window) )
	{

//		// Move the camera (A & D for left and right, along the x axis)
//		if (key == GLFW_KEY_A)
//		{
//			cameraEye.x -= CAMERASPEED;		// Move the camera -0.01f units
//		}
//		if (key == GLFW_KEY_D)
//		{
//			cameraEye.x += CAMERASPEED;		// Move the camera +0.01f units
//		}
//	
//		// Move the camera (Q & E for up and down, along the y axis)
//		if (key == GLFW_KEY_Q)
//		{
//			cameraEye.y -= CAMERASPEED;		// Move the camera -0.01f units
//		}
//		if (key == GLFW_KEY_E)
//		{
//			cameraEye.y += CAMERASPEED;		// Move the camera +0.01f units
//		}
//	
//		// Move the camera (W & S for towards and away, along the z axis)
//		if (key == GLFW_KEY_W)
//		{
//			cameraEye.z -= CAMERASPEED;		// Move the camera -0.01f units
//		}
//		if (key == GLFW_KEY_S)
//		{
//			cameraEye.z += CAMERASPEED;		// Move the camera +0.01f units
//		}

		if ( key == GLFW_KEY_B )
		{ 
			// Shoot a bullet from the pirate ship
			// Find the pirate ship...
			// returns NULL (0) if we didn't find it.
//			cGameObject* pShip = pFindObjectByFriendlyName("PirateShip");
			cGameObject* pShip = pFindObjectByFriendlyNameMap("PirateShip");
			// Maybe check to see if it returned something... 

			// Find the sphere#2
//			cGameObject* pBall = pFindObjectByFriendlyName("Sphere#2");
			cGameObject* pBall = pFindObjectByFriendlyNameMap("Sphere#2");

			// Set the location velocity for sphere#2
			pBall->positionXYZ = pShip->positionXYZ;
			pBall->inverseMass = 1.0f;		// So it's updated
			// 20.0 units "to the right"
			// 30.0 units "up"
			pBall->velocity = glm::vec3( 15.0f, 20.0f, 0.0f );
			pBall->accel = glm::vec3(0.0f,0.0f,0.0f);
			pBall->diffuseColour = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
		}//if ( key == GLFW_KEY_B )

	}

	if (isOnlyShiftKeyDown(mods))
	{
		// move the light
		if (key == GLFW_KEY_A)
		{
			sexyLightPosition.x -= CAMERASPEED;		// Move the camera -0.01f units
		}
		if (key == GLFW_KEY_D)
		{
			sexyLightPosition.x += CAMERASPEED;		// Move the camera +0.01f units
		}

		// Move the camera (Q & E for up and down, along the y axis)
		if (key == GLFW_KEY_Q)
		{
			sexyLightPosition.y -= CAMERASPEED;		// Move the camera -0.01f units
		}
		if (key == GLFW_KEY_E)
		{
			sexyLightPosition.y += CAMERASPEED;		// Move the camera +0.01f units
		}

		// Move the camera (W & S for towards and away, along the z axis)
		if (key == GLFW_KEY_W)
		{
			sexyLightPosition.z -= CAMERASPEED;		// Move the camera -0.01f units
		}
		if (key == GLFW_KEY_S)
		{
			sexyLightPosition.z += CAMERASPEED;		// Move the camera +0.01f units
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
	if (isOnlyCtrlKeyDown(mods))
	{
		const float SHIP_SPEED_CHANGE = 0.01f;
		const float SHIP_ANGLE_CHANGE = 0.01f;

		cGameObject* pShip = pFindObjectByFriendlyName("PirateShip");
		// Turn the ship around
		if (key == GLFW_KEY_A)
		{	// Left
			pShip->HACK_AngleAroundYAxis -= SHIP_ANGLE_CHANGE;
			pShip->rotationXYZ.y = pShip->HACK_AngleAroundYAxis;
		}
		if (key == GLFW_KEY_D)
		{	// Right
			pShip->HACK_AngleAroundYAxis += SHIP_ANGLE_CHANGE;
			pShip->rotationXYZ.y = pShip->HACK_AngleAroundYAxis;
		}
		if (key == GLFW_KEY_W)
		{	// Faster
			pShip->HACK_speed += SHIP_SPEED_CHANGE;
		}
		if (key == GLFW_KEY_S)
		{	// Slower
			pShip->HACK_speed -= SHIP_SPEED_CHANGE;
		}
	}




	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);

}




bool isOnlyShiftKeyDown(int mods)
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

bool isOnlyCtrlKeyDown(int mods)
{
	if (mods == GLFW_MOD_CONTROL)			
	{
		return true;
	}
	return false;
}

bool isOnlyAltKeyDown(int mods)
{
	if (mods == GLFW_MOD_ALT)
	{
		return true;
	}
	return false;
}

bool isShiftDown(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) { return true; }
	if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT)) { return true; }
	// both are up
	return false;
}

bool isCtrlDown(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) { return true; }
	if (glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL)) { return true; }
	// both are up
	return false;
}

bool isAltDown(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_LEFT_ALT)) { return true; }
	if (glfwGetKey(window, GLFW_KEY_RIGHT_ALT)) { return true; }
	// both are up
	return false;
}

bool areAllModifiersUp(GLFWwindow* window)
{
	if (isShiftDown(window)) { return false; }
	if (isCtrlDown(window)) { return false; }
	if (isAltDown(window)) { return false; }
	// Yup, they are all UP
	return true;
}

// Mouse (cursor) callback
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{

	return;
}



void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	// A regular mouse wheel returns the y value
	::g_pFlyCamera->setMouseWheelDelta(yoffset);

	//	std::cout << "Mouse wheel: " << yoffset << std::endl;

	return;
}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		::g_MouseLeftButtonIsDown = true;
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		::g_MouseLeftButtonIsDown = false;
	}

	return;
}

void ProcessAsyncMouse(GLFWwindow* window)
{
	double x, y;
	glfwGetCursorPos(window, &x, &y);

	::g_pFlyCamera->setMouseXY(x, y);

	const float MOUSE_SENSITIVITY = 0.1f;

	//	std::cout << ::g_pFlyCamera->getMouseX() << ", " << ::g_pFlyCamera->getMouseY() << std::endl;

		// Mouse left (primary?) button pressed? 
		// AND the mouse is inside the window...
	if ((glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		&& ::g_MouseIsInsideWindow)
	{
		// Mouse button is down so turn the camera
		::g_pFlyCamera->Yaw_LeftRight(-::g_pFlyCamera->getDeltaMouseX() * MOUSE_SENSITIVITY);

		::g_pFlyCamera->Pitch_UpDown(::g_pFlyCamera->getDeltaMouseY() * MOUSE_SENSITIVITY);

	}

	// Adjust the mouse speed
	if (::g_MouseIsInsideWindow)
	{
		const float MOUSE_WHEEL_SENSITIVITY = 0.1f;

		// Adjust the movement speed based on the wheel position
		::g_pFlyCamera->movementSpeed += (::g_pFlyCamera->getMouseWheel() * MOUSE_WHEEL_SENSITIVITY);
		if (::g_pFlyCamera->movementSpeed <= 0.0f)
		{
			::g_pFlyCamera->movementSpeed = 0.0f;
		}
	}


	// HACK 
	::g_pFlyCamera->movementSpeed = 2.0f;

	return;
}//ProcessAsyncMouse(...


void ProcessAsyncKeys(GLFWwindow* window)
{
	const float CAMERA_MOVE_SPEED_SLOW = 0.1f;
	const float CAMERA_MOVE_SPEED_FAST = 1.0f;

	const float CAMERA_TURN_SPEED = 0.1f;

	// WASD + q = "up", e = down		y axis = up and down
	//									x axis = left and right
	//									z axis = forward and backward
	// 

	//float cameraSpeed = CAMERA_MOVE_SPEED_SLOW;
	//if ( glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS  )
	//{
	//	cameraSpeed = CAMERA_MOVE_SPEED_FAST;
	//}

	float cameraMoveSpeed = ::g_pFlyCamera->movementSpeed;

	// If no keys are down, move the camera
	if (areAllModifiersUp(window))
	{
		// Note: The "== GLFW_PRESS" isn't really needed as it's actually "1" 
		// (so the if() treats the "1" as true...)


		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			//			g_CameraEye.z += cameraSpeed;
			::g_pFlyCamera->MoveForward_Z(+cameraMoveSpeed);
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)	// "backwards"
		{
			//			g_CameraEye.z -= cameraSpeed;
			::g_pFlyCamera->MoveForward_Z(-cameraMoveSpeed);
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)	// "left"
		{
			//			g_CameraEye.x -= cameraSpeed;
			::g_pFlyCamera->MoveLeftRight_X(-cameraMoveSpeed);
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)	// "right"
		{
			//			g_CameraEye.x += cameraSpeed;
			::g_pFlyCamera->MoveLeftRight_X(+cameraMoveSpeed);
		}
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)	// "up"
		{
			::g_pFlyCamera->MoveUpDown_Y(-cameraMoveSpeed);
			//			::g_pFlyCamera->Roll_CW_CCW( +cameraSpeed );
		}
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)	// "down"
		{
			//			g_CameraEye.y -= cameraSpeed;
			::g_pFlyCamera->MoveUpDown_Y(+cameraMoveSpeed);
			//			::g_pFlyCamera->Roll_CW_CCW( -cameraSpeed );
		}
	}//if(AreAllModifiersUp(window)

	// If shift is down, do the rotation camera stuff...
	// If no keys are down, move the camera
	if (isShiftDown(window))
	{
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)	// "up"
		{
			::g_pFlyCamera->Roll_CW_CCW(-CAMERA_TURN_SPEED);
			//			::g_pFlyCamera->MoveUpDown_Y( +cameraSpeed );
		}
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)	// "down"
		{
			::g_pFlyCamera->Roll_CW_CCW(+CAMERA_TURN_SPEED);
			//			::g_pFlyCamera->MoveUpDown_Y( -cameraSpeed );
		}
	}//IsShiftDown(window)


	return;
}// ProcessAsyncKeys(..
