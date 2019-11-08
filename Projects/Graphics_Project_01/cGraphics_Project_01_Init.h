#pragma once
#include "../../Master/iMaster_InitTest.h"

#pragma comment (lib, "Graphics_Project_01.lib")

class cGraphics_Project_01_Init :
	public iMaster_InitTest
{
public:
	cGraphics_Project_01_Init() {}
	virtual ~cGraphics_Project_01_Init() {}
	virtual void Init(gamelibrary::GameLibrary& gameLib);
	virtual void Step(float deltaTime);
	virtual bool Done() {
		return false;
	}

	virtual GLFWkeyfun GetKeyCallback();
	virtual GLFWmousebuttonfun GetMouseCallback();
};

