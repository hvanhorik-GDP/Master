#include "cPhysics_MidTerm_2019_Init.h"
#include "Physics_MidTerm_2019_Callback.h"
#include "Physics_MidTerm_2019_ObjectCreator.h"

#include <rapidxml/rapidxml.hpp>

rapidxml::xml_node<>* objectLibNode;

void cPhysics_MidTerm_2019_Init::Init(gamelibrary::GameLibrary& gameLib)
{
	cObjectManager objectManager;
	gamelibrary::Objects objectsLib = gameLib.GetObjects();
	Physics_MidTerm_2019_CalculateBounds(objectsLib.GetNode());
	objectLibNode = objectsLib.GetNode();
	Physics_MidTerm_2019_LaserBalls(500, objectManager, objectLibNode);

}

void cPhysics_MidTerm_2019_Init::Step(float deltaTime)
{
	cObjectManager objectManager;
	::Physics_MidTerm_2019_CreateNewAstroid(deltaTime, objectLibNode);
	::Physics_MidTerm_2019_Shoot_Laser(deltaTime);
}

GLFWkeyfun cPhysics_MidTerm_2019_Init::GetKeyCallback()
{
	return Physics_MidTerm_2019_key_callback;
}

GLFWmousebuttonfun cPhysics_MidTerm_2019_Init::GetMouseCallback()
{
	return Physics_MidTerm_2019_mouse_button_callback;
}


