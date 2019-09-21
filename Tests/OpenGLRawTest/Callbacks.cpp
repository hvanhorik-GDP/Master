#include "glfw_raw/glfw_raw_Window.h"
#include "glfw_raw/glfw_raw_Key.h"
#include "Callbacks.h"
#include <iostream>

using namespace glfw::raw;
using namespace glfw::raw::Key;
using namespace std;

static void key_callback(window* window, int key, int scancode, int action, int mods)
{
	// Move the camera (A & D for left and right, along the x axis)
	switch (key)
	{
	case KeyA:
		{
			cout << "KeyA hit !" << endl;
			break;
		}
	case KeyD:
		{
			cout << "KeyD hit !" << endl;
			break;
		}
	case KeyQ:
		{
			cout << "KeyQ hit !" << endl;
			break;
		}
	case KeyE:
		{
			cout << "KeyE hit !" << endl;
			break;
		}
	case KeyW:
		{
			cout << "KeyW hit !" << endl;
			break;
		}
	case KeyS:
		{
			cout << "KeyS hit !" << endl;
			break;
		}
	case KeyJ:
		{
			cout << "KeyJ hit !" << endl;
			break;
		}
	case KeyK:
		{
			cout << "KeyK hit !" << endl;
			break;
		}
	default:
		break;
	}

	if (key == KeyEscape && action == Press)
		cout << "Asking to close the Window!" << endl;
	//if (key == KeyA)
	//{
	//	cout << "KeyA hit !" << endl;
	//}
	//if (key == KeyD)
	//{
	//	cameraEye.x += 0.1f;		// Move the camera +0.01f units
	//}

	//// Move the camera (Q & E for up and down, along the y axis)
	//if (key == KeyQ)
	//{
	//	cameraEye.y -= 0.1f;		// Move the camera -0.01f units
	//}
	//if (key == KeyE)
	//{
	//	cameraEye.y += 0.1f;		// Move the camera +0.01f units
	//}

	//// Move the camera (W & S for towards and away, along the z axis)
	//if (key == GLFW_KEY_W)
	//{
	//	cameraEye.z -= 0.1f;		// Move the camera -0.01f units
	//}
	//if (key == GLFW_KEY_S)
	//{
	//	cameraEye.z += 0.1f;		// Move the camera +0.01f units
	//}


	//if (key == GLFW_KEY_J)
	//{
	//	sexyLightLocation.x -= 0.1f;
	//}
	//if (key == GLFW_KEY_K)
	//{
	//	sexyLightLocation.x += 0.1f;
	//}


	//if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	//	glfwSetWindowShouldClose(window, GLFW_TRUE);

}

static void error_callback(glfw::raw::Error::eError error, const char* description)
{
	cout << "Error: " << error << ", Description:" << description << endl;
}
