#pragma once

#include "gl/GLCommon.h"
#include "GameLibrary/GameLibrary.h"

class iMaster_InitTest
{
public:
	iMaster_InitTest() {};
	virtual ~iMaster_InitTest() {};

	virtual void Init(gamelibrary::GameLibrary& gameLib) = 0;
	virtual void Step(float deltaTime) = 0;
	virtual bool Done() = 0;

	virtual GLFWkeyfun GetKeyCallback() = 0;
	virtual GLFWmousebuttonfun GetMouseCallback() = 0;
};