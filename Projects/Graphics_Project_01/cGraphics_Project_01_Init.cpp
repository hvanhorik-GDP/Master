#include "cGraphics_Project_01_Init.h"
#include "Graphics_Project_01_Callback.h"

void cGraphics_Project_01_Init::Init(gamelibrary::GameLibrary& gameLib)
{
}

void cGraphics_Project_01_Init::Step(float deltaTime)
{
}

GLFWkeyfun cGraphics_Project_01_Init::GetKeyCallback()
{
	return Graphics_Project_01_key_callback;
}

GLFWmousebuttonfun cGraphics_Project_01_Init::GetMouseCallback()
{
	return Graphics_Project_01_mouse_button_callback;
}


