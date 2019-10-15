#include "LoadGLFW.h"
#include "globalStuff.h"
#include "GDP2019/GLFW_Callbacks.h"

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

	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);
	return 0;
}


void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

