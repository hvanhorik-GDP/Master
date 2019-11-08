#include <rapidxml/rapidxml.hpp>

#include "GameLibrary/GameLibrary.h"
#include "GameLibrary/AssetGroups.h"
#include "GameLibrary/Objects.h"
#include "XML/XMLDocument.h"
#include "AssetManager/cAssetManager.h"
#include "AssetManager/cAssetManager_Audios.h"
#include "ObjectManager/cObjectManager.h"
#include "ObjectItems/cObject_World.h"

#include "AudioEngine/cAudio_System.h"
#include "AudioEngine/cAudio_System_FMOD.h"
#include "iMaster_InitTest.h"
#include "Master_RunTest.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <streambuf>
#include <sstream>
#include <exception>
#include <filesystem>
#include <cstdio> 
#include <conio.h>
#include <direct.h>

#include "Common/LoadGLFW.h"

#include "cTest_Init.h"
#include "../Projects/Physics_Project_01/cPhysics_Project_01_Init.h"
#include "../Projects/Graphics_Project_01/cGraphics_Project_01_Init.h"
#include "../Projects/Media_Project_02/cMedia_Project_02_Init.h"
#include "../Projects/Physics_MidTerm_2019/cPhysics_MidTerm_2019_Init.h"
#include "../Projects/Graphics_Midterm_2019/cGraphics_Midterm_2019_Init.h"
#include "../Projects/Patterns_MidTerm_2019/cPatterns_MidTerm_2019_Init.h"

int main(int arg, char** argv)
{
	std::cout << "starting up" << std::endl;
	std::string root("./assets/");
	std::string libraryName("test.xml");
	if (arg > 1)
	{
		libraryName = argv[1];
	}
	std::string inputLibrary = root + libraryName;
	std::size_t pos = libraryName.find(".");
	std::string outName = libraryName.substr(0, pos) + "(output).xml";
	std::string outputLibrary = root + outName;
	if (loadGFLW())
		exit(EXIT_FAILURE);

	// loads in the game 
	XMLDocument document;
	document.Read(inputLibrary);
	gamelibrary::GameLibrary gameLib = gamelibrary::GameLibrary(document.GetDocument());

	// Read in the assets
	gamelibrary::AssetGroups assets = gameLib.GetAssetGroups();
	cAssetManager assetManager;
	assetManager.LoadAssets(gameLib.GetNode());

	// Read all of the objects
	gamelibrary::Objects objects = gameLib.GetObjects();
	cObjectManager objectManager;
	objectManager.LoadObjects(objects.GetNode());

	iMaster_InitTest* init;

	if (libraryName == "Physics_Project_01.xml")
		init = new cPhysics_Project_01_Init();
	else if (libraryName == "Graphics_Project_01.xml")
		init =  new cGraphics_Project_01_Init();
	else if (libraryName == "Media_Project_02.xml")
		init = new cMedia_Project_02_Init();
	else if (libraryName == "Physics_MidTerm_2019.xml")
		init = new cPhysics_MidTerm_2019_Init();
	else if (libraryName == "Graphics_MidTerm_2019.xml")
		init = new cGraphics_Midterm_2019_Init();
	else if (libraryName == "Patterns_MidTerm_2019.xml")
		init = new cPatterns_MidTerm_2019_Init();
	else if (libraryName == "test.xml")
	{
		init = new cTest_Init();
	}
	else
	{
		assert(false);
		std::cout << "Unknown library : " << libraryName << std::endl;
		return 1;
	}

	Master_RunTest(gameLib, init);
	document.Write(outputLibrary);

	return 0;
}

