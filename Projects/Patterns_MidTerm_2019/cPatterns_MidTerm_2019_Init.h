#pragma once
#include "../../Master/iMaster_InitTest.h"

#pragma comment (lib, "Patterns_MidTerm_2019.lib")

class cPatterns_MidTerm_2019_Init :
	public iMaster_InitTest
{
public:
	cPatterns_MidTerm_2019_Init() {}
	virtual ~cPatterns_MidTerm_2019_Init() {}
	virtual void Init(gamelibrary::GameLibrary& gameLib);
	virtual void Step(float deltaTime);
	virtual bool Done();

	virtual GLFWkeyfun GetKeyCallback();
	virtual GLFWmousebuttonfun GetMouseCallback();
};

