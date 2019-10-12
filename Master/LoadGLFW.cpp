#include "LoadGLFW.h"
#include "globalStuff.h"
#include "GFLW_Callbacks.h"

int loadGFLW(void)
{


	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
	{
		return(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return(EXIT_FAILURE);
	}

	glfwSetKeyCallback(window, key_callback);
	// Set the mouse button callback
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);
	return 0;
}
