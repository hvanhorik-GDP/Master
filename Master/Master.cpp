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
#include "GDP2019/test_GDP2019.h"
#include "AudioTest/test_Audio.h"
#include "OtherTest/test_gl.h"
#include "OtherTest/test_filesystem.h"
#include "AudioTest/test_AudioEngine.h"
#include "Physics/test_Physics.h"
#include "Graphics/test_Graphics.h"
#include "Audio/test_Audio.h"
//#include "MidTerm_2018/MidTerm_2018_test.h"
#include "Physics_MidTerm_2019/Physics_MidTerm_2019_test.h"

int main(int arg, char** argv)
{
	std::string root("../assets/");
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

	// INFO6044 - loads in the game 

	XMLDocument document;
	document.Read(inputLibrary);

	gamelibrary::GameLibrary gameLib = gamelibrary::GameLibrary(document.GetDocument());

	// Read in the assets
	gamelibrary::AssetGroups assets = gameLib.GetAssetGroups();
	cAssetManager assetManager;
	assetManager.LoadAssets(gameLib.GetNode());

	gamelibrary::Objects objects = gameLib.GetObjects();
	cObjectManager objectManager;
	objectManager.LoadObjects(objects.GetNode());

	// INFO6044 -a bit of a hack since the Physics and Graphics operarate somewhat
	// differently

	if (libraryName == "PhysicsLibrary.xml")
		test_Physics(gameLib);
	else if (libraryName == "GraphicsLibrary.xml")
		test_Graphics(gameLib);
	else if (libraryName == "AudioLibrary.xml")
		test_Audio(gameLib);
	else if (libraryName == "Physics_MidTerm_2019.xml")
		Physics_MidTerm_2019_test(gameLib);
	else
	{
		assert(false);
		std::cout << "Unknown library : " << libraryName << std::endl;
	}

	// INFO6044 - a copy of the xml is made which reflects changes to any
	// objects during play


	document.Write(outputLibrary);

	//	test_filesystem();
//	test_AudioEngine();

//	test_Audio(gAssetManager);

	return 0;
}

