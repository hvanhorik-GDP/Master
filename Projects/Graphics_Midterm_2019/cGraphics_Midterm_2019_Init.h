#pragma once

#include "../../Master/iMaster_InitTest.h"

#pragma comment (lib, "Graphics_Midterm_2019.lib")

class cGraphics_Midterm_2019_Init :
	public iMaster_InitTest
{
public:
	cGraphics_Midterm_2019_Init() {}
	virtual ~cGraphics_Midterm_2019_Init() {}
	virtual void Init(gamelibrary::GameLibrary& gameLib);
	virtual void Step(float deltaTime);
	virtual bool Done() {
		return false;
	}

	virtual GLFWkeyfun GetKeyCallback();
	virtual GLFWmousebuttonfun GetMouseCallback();
};

