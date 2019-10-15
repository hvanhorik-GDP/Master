// Master.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "test_gl.h"

#include "gl_OpenGL/glfw_raw/glfw_raw_Common.h"
#include "gl_OpenGL/glfw_raw/glfw_raw_System.h"
#include "gl_OpenGL/glfw_raw/glfw_raw_Window.h"

#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <cstdlib>		// c libs
#include <cstdio>		// c libs
#include <iostream>		// C++ IO standard stuff

#include "GLCommon.h"
#include "GDP2019/GLFW_Callbacks.h"

#pragma comment(lib, "gl_OpenGL.lib")

void test_gl()
{
	std::cout << "Hello World!" << std::endl;

	glfw::raw::window* window;
	//GLuint vertex_buffer, vertex_shader, fragment_shader, program;
//	GLint mvp_location;

	glfw::raw::System::WindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfw::raw::System::WindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	window = glfw::raw::System::CreateWindow(640, 480, "Simple example", NULL, NULL);
	if (!window)
	{
		glfw::raw::System::Terminate();
		exit(EXIT_FAILURE);
	}

//	glfw::raw::Window::SetKeyCallback(window, key_callback);
	glfw::raw::Window::MakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfw::raw::System::GetProcAddress);
	glfw::raw::System::SwapInterval(1);

}
