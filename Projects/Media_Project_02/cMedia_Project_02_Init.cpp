#include "cMedia_Project_02_Init.h"
#include "Media_Project_02_Callback.h"
#include "cMedia_Project_02_Tilter.h"
#include "Media_Project_02_ObjectCreator.h"

cMedia_Project_02_Tilter* gMedia_Project_02_Tilter;	

void cMedia_Project_02_Init::Init(gamelibrary::GameLibrary& gameLib)
{
	cObjectManager objectManager;
	gamelibrary::Objects objectsLib = gameLib.GetObjects();
	CreatePyramids(1, objectManager, objectsLib.GetNode());
	CreateDropBalls(1, objectManager, objectsLib.GetNode());

	CloneObject(1, "AudioChannel", objectsLib.GetNode());
	CloneObject(1, "AudioChannelGroup", objectsLib.GetNode());

	// Do an initial tilter
	gMedia_Project_02_Tilter = new cMedia_Project_02_Tilter();
	int random = rand() % 1;
	int plane = (random == 0) ? 0 : 2;		// x or z axis tilt
	random = rand() % 1000 + 100;
	float planeTilt = 0.0005f * random;
	gMedia_Project_02_Tilter->tiltPlane(plane, planeTilt);
}

void cMedia_Project_02_Init::Step(float deltaTime)
{

}

GLFWkeyfun cMedia_Project_02_Init::GetKeyCallback()
{
	return Media_Project_02_key_callback;
}

GLFWmousebuttonfun cMedia_Project_02_Init::GetMouseCallback()
{
	return Media_Project_02_mouse_button_callback;
}


