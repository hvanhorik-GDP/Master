#include <rapidxml/rapidxml.hpp>

#include "GameLibrary/GameLibrary.h"
#include "GameLibrary/AssetGroups.h"
#include "GameLibrary/Objects.h"
#include "XML/XMLDocument.h"
#include "AssetManager/cAssetManager.h"
#include "AssetManager/cAssetManager_Audios.h"
#include "ObjectManager/cObjectManager.h"

#include "AudioEngine/cAudio_System.h"
#include "AudioEngine/cAudio_System_FMOD.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <streambuf>
#include <sstream>
#include <exception>
#include <filesystem>
#include <cstdio>  /* defines FILENAME_MAX */
#include <conio.h>
#include <direct.h>

#include "Common/LoadGLFW.h"
#include "../Projects/GDP2019_Test/test_GDP2019.h"
//#include "AudioTest/test_Audio.h"
//#include "OtherTest/test_gl.h"
//#include "OtherTest/test_filesystem.h"
//#include "AudioTest/test_AudioEngine.h"
#include "../Projects/Physics_Project_01/test_Physics.h"
#include "../Projects//Graphics_Project_01/test_Graphics.h"
#include "../Projects/Media_Project_02/Media_Project_02_test.h"
#include "../Projects/Physics_MidTerm_2019/Physics_MidTerm_2019_test.h"
#include "../Projects/Graphics_MidTerm_2019/Graphics_MidTerm_2019_test.h"
#include "../Projects/Patterns_MidTerm_2019/Patterns_MidTerm_2019_test.h"

int main(int arg, char** argv)
{
	std::cout << "starting up" << std::endl;
	std::string root("./assets/");
	std::string libraryName("GameLibrary.xml");
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
	//  Loads in objects and assets
	gamelibrary::AssetGroups assets = gameLib.GetAssetGroups();
	cAssetManager assetManager;
	assetManager.LoadAssets(gameLib.GetNode());

	gamelibrary::Objects objects = gameLib.GetObjects();
	cObjectManager objectManager;
	objectManager.LoadObjects(objects.GetNode());

	//  bit of a hack since the Physics and Graphics operarate somewhat
	// differently

	if (libraryName == "PhysicsLibrary.xml")
		test_Physics(gameLib);
	else if (libraryName == "GraphicsLibrary.xml")
		test_Graphics(gameLib);
	else if (libraryName == "AudioLibrary.xml")
		Audio_test(gameLib);
	else if (libraryName == "Physics_MidTerm_2019.xml")
		Physics_MidTerm_2019_test(gameLib);
	else if (libraryName == "Graphics_MidTerm_2019.xml")
		Graphics_MidTerm_2019_test(gameLib);
	else if (libraryName == "Patterns_MidTerm_2019.xml")
		//    Loads in and calls the proper code
		Patterns_MidTerm_2019_test(gameLib);
	else
	{
		assert(false);
		std::cout << "Unknown library : " << libraryName << std::endl;
	}

	document.Write(outputLibrary);

	//	test_filesystem();
//	test_AudioEngine();

//	test_Audio(gAssetManager);

	return 0;
}

