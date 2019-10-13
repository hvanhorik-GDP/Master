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

#include "LoadGLFW.h"
#include "test_GDP2019.h"
#include "test_Audio.h"
#include "test_gl.h"
#include "test_filesystem.h"
#include "test_AudioEngine.h"
#include "test_Physics.h"

int main(int arg, char** argv)
{
	if (loadGFLW())
		exit(EXIT_FAILURE);

	XMLDocument document;
	document.Read("../assets/GameLibrary.xml");

	gamelibrary::GameLibrary gameLib = gamelibrary::GameLibrary(document.GetDocument());

	// Read in the assets
	gamelibrary::AssetGroups assets = gameLib.GetAssetGroups();
	cAssetManager assetManager;
	assetManager.LoadAssets(gameLib.GetNode());

	gamelibrary::Objects objects = gameLib.GetObjects();
	cObjectManager objectManager;
	objectManager.LoadObjects(objects.GetNode());

	document.Write("../assets/output.xml");

//	test_GDP2019(gameLib);	
	test_Physics(gameLib);

	document.Write("../assets/output2.xml");

	//	test_filesystem();
//	test_AudioEngine();

//	test_Audio(gAssetManager);

	return 0;
}

