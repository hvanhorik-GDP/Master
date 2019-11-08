#include "cPhysics_Project_01_Init.h"
#include "Physics_Project_01_Callback.h"
#include "ObjectManager/cObjectManager.h"
#include "Physics_Project_01_ObjectCreator.h"
#include "cPhysics_Project_01_Tilter.h"

extern cPhysics_Project_01_Tilter* gPhysics_Project_01_Tilter;		// TODO - Hack

void cPhysics_Project_01_Init::Init(gamelibrary::GameLibrary& gameLib)
{
	cObjectManager manager;
	gamelibrary::Objects objectsLib = gameLib.GetObjects();
	::Physics_Project_01_CreatePyramids(10, manager, objectsLib.GetNode());
	::Physics_Project_01_CreateDropBalls(100, manager, objectsLib.GetNode());

	// Do an initial tilter
	gPhysics_Project_01_Tilter = new cPhysics_Project_01_Tilter();
	int random = rand() % 1;
	int plane = (random == 0) ? 0 : 2;		// x or z axis tilt
	random = rand() % 1000 + 100;
	float planeTilt = 0.0005f * random;
	gPhysics_Project_01_Tilter->tiltPlane(plane, planeTilt);
}

void cPhysics_Project_01_Init::Step(float deltaTime)
{
}

GLFWkeyfun cPhysics_Project_01_Init::GetKeyCallback()
{
	return Physics_Project_01_key_callback;
}

GLFWmousebuttonfun cPhysics_Project_01_Init::GetMouseCallback()
{
	return Physics_Project_01_mouse_button_callback;
}


