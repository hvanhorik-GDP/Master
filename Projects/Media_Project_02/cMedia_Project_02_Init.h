#pragma once
#include "../../Master/iMaster_InitTest.h"

#pragma comment (lib, "Media_Project_02.lib")

class cMedia_Project_02_Init :
	public iMaster_InitTest
{
public:
	cMedia_Project_02_Init() {}
	virtual ~cMedia_Project_02_Init() {}
	virtual void Init(gamelibrary::GameLibrary& gameLib);
	virtual void Step(float deltaTime);
	virtual bool Done() {
		return false;
	}

	virtual GLFWkeyfun GetKeyCallback();
	virtual GLFWmousebuttonfun GetMouseCallback();
};

