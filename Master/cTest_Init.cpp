#include "cTest_Init.h"
#include "Test_Callback.h"

void cTest_Init::Init(gamelibrary::GameLibrary& gameLib)
{
}

void cTest_Init::Step(float deltaTime)
{
}

GLFWkeyfun cTest_Init::GetKeyCallback()
{
	return Test_key_callback;
}

GLFWmousebuttonfun cTest_Init::GetMouseCallback()
{
	return Test_mouse_button_callback;
}


