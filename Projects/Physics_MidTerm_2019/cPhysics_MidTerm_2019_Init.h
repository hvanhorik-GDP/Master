#pragma once
#include "../../Master/iMaster_InitTest.h"

#pragma comment (lib, "Physics_MidTerm_2019.lib")

class cPhysics_MidTerm_2019_Init :
	public iMaster_InitTest
{
public:
	cPhysics_MidTerm_2019_Init() {}
	virtual ~cPhysics_MidTerm_2019_Init() {}
	virtual void Init(gamelibrary::GameLibrary& gameLib);
	virtual void Step(float deltaTime);
	virtual bool Done() {
		return false;
	}

	virtual GLFWkeyfun GetKeyCallback();
	virtual GLFWmousebuttonfun GetMouseCallback();
};

