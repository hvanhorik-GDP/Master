#include "cPatterns_MidTerm_2019_Init.h"
#include "cPatterns_MidTerm_2019_World.h"
#include "Patterns_MidTerm_2019_Callback.h"

#include <iostream>

cPatterns_MidTerm_2019_World *g_myWorld;

void cPatterns_MidTerm_2019_Init::Init(gamelibrary::GameLibrary& gameLib)
{
	gamelibrary::Objects objectsLib = gameLib.GetObjects();
	// INFO6044 - builder - create the robots
	g_myWorld = new cPatterns_MidTerm_2019_World();
	g_myWorld->CreateRobots(20, objectsLib.GetNode());
}

void cPatterns_MidTerm_2019_Init::Step(float deltaTime)
{
	g_myWorld->Step((float)deltaTime);
}

bool cPatterns_MidTerm_2019_Init::Done()
{
	if (g_myWorld->NumberOfRobotsLeft() <= 1)
	{
		std::cout << "Winner is : " << g_myWorld->Winner() << std::endl;
		return true;
	}
	return false;
}

GLFWkeyfun cPatterns_MidTerm_2019_Init::GetKeyCallback()
{
	return Patterns_MidTerm_2019_key_callback;
}

GLFWmousebuttonfun cPatterns_MidTerm_2019_Init::GetMouseCallback()
{
	return Patterns_MidTerm_2019_mouse_button_callback;
}


