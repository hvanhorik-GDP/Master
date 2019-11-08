#pragma once
#include "iMaster_InitTest.h"

class cTest_Init :
	public iMaster_InitTest
{
public:
	cTest_Init() {}
	virtual ~cTest_Init() {}
	virtual void Init(gamelibrary::GameLibrary& gameLib);
	virtual void Step(float deltaTime);
	virtual bool Done() {
		return false;
	}

	virtual GLFWkeyfun GetKeyCallback();
	virtual GLFWmousebuttonfun GetMouseCallback();
};

