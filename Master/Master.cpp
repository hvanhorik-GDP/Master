#include <rapidxml/rapidxml.hpp>

#include "GameLibrary/GameLibrary.h"
#include "GameLibrary/AssetGroups.h"
#include "XML/XMLDocument.h"
#include "AssetManager/cAssetManager.h"
#include "AssetManager/cAssetManager_Audios.h"
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


#include "test_GDP2019.h"
#include "test_Audio.h"
#include "test_gl.h"
#include "test_filesystem.h"
#include "test_AudioEngine.h"


std::string GetCurrentWorkingDir(void) {
	char buff[FILENAME_MAX];
	_getcwd(buff, FILENAME_MAX);
	std::string current_working_dir(buff);
	return current_working_dir;
}

cAssetManager gAssetManager;

void ReadGameLibrary(const std::string& name)
{
	std::string workingDir = GetCurrentWorkingDir();
	std::string fullpath = workingDir + "/" + name;
	std::cout << fullpath << std::endl;
	XMLDocument document;
	document.Read(name);

	gamelibrary::GameLibrary gameLib(document.GetDocument());

	gamelibrary::AssetGroups assets = gameLib.GetAssetGroups();
	gAssetManager.LoadAssets(gameLib.GetNode());

	std::string outfile = workingDir + "/" + "output.xml";
	document.Write(outfile);
	system("pause");
}

int main(int arg, char** argv)
{
	test_gl();
	ReadGameLibrary("../assets/GameLibrary.xml");
//	test_filesystem();
//	test_GDP2019();
//	test_AudioEngine();

//	test_Audio(gAssetManager);

	return 0;
}

