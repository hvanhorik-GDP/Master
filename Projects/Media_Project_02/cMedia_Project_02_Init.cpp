#include "cMedia_Project_02_Init.h"
#include "Media_Project_02_Callback.h"
#include "cMedia_Project_02_Tilter.h"
#include "Media_Project_02_ObjectCreator.h"
#include "ObjectItems/cObject_ChannelGroup.h"

cMedia_Project_02_Tilter* gMedia_Project_02_Tilter;	
cObjectWatcher* gObjectWatcher = NULL;
extern cAudio_System_FMOD* g_implFMOD;


void cMedia_Project_02_Init::Init(gamelibrary::GameLibrary& gameLib)
{
	gObjectWatcher = new cObjectWatcher();
	cObjectManager objectManager;
	gamelibrary::Objects objectsLib = gameLib.GetObjects();
	CreatePyramids(5, objectManager, objectsLib.GetNode());
	CreateDropBalls(1, objectManager, objectsLib.GetNode());

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
	gObjectWatcher->Watch(deltaTime);
	g_implFMOD->Update();
}

GLFWkeyfun cMedia_Project_02_Init::GetKeyCallback()
{
	return Media_Project_02_key_callback;
}

GLFWmousebuttonfun cMedia_Project_02_Init::GetMouseCallback()
{
	return Media_Project_02_mouse_button_callback;
}


