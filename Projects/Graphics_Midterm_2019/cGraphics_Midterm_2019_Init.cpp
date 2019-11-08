#include "cGraphics_Midterm_2019_Init.h"
#include "Graphics_Midterm_2019_Callback.h"

void cGraphics_Midterm_2019_Init::Init(gamelibrary::GameLibrary& gameLib)
{
}

void cGraphics_Midterm_2019_Init::Step(float deltaTime)
{
}

GLFWkeyfun cGraphics_Midterm_2019_Init::GetKeyCallback()
{
	return Graphics_MidTerm_2019_key_callback;
}

GLFWmousebuttonfun cGraphics_Midterm_2019_Init::GetMouseCallback()
{
	return Graphics_MidTerm_2019_mouse_button_callback;
}


