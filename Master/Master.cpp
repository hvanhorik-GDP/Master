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

int main(int arg, char** argv)
{
	std::string root("../assets/");
	std::string libraryName("GameLibrary.xml");
	if (arg > 1)
	{
		libraryName = argv[1];
	}
	std::string inputLibrary = root + libraryName;
	std::string outputLibrary = root + "output_" + libraryName;
	if (loadGFLW())
		exit(EXIT_FAILURE);

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

//	test_GDP2019(gameLib);	
	test_Physics(gameLib);

	document.Write(outputLibrary);

	//	test_filesystem();
//	test_AudioEngine();

//	test_Audio(gAssetManager);

	return 0;
}

