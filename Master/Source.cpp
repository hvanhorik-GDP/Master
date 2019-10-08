#include <rapidxml/rapidxml.hpp>

#include "GameLibrary/GameLibrary.h"
#include "GameLibrary/AssetGroups.h"
#include "XML/XMLDocument.h"
#include "AssetManager/cAssetManager.h"
#include "AssetManager/cAssetManager_Audios.h"
#include "cAudio_System.h"
#include "cAudio_System_FMOD.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <streambuf>
#include <sstream>
#include <exception>
#include <experimental/filesystem>

#include <stdio.h>  /* defines FILENAME_MAX */
#include <conio.h>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>

#include <direct.h>

#pragma comment (lib, "gl_OpenGL.lib")

using namespace std;
using namespace rapidxml;
using namespace gamelibrary;

void open_gl();
void test_Audio(cAssetManager& assetManager, cAudio_System& gAudioSystem);

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
	std::cout << fullpath << endl;
	XMLDocument document;
	document.Read(name);

	GameLibrary gameLib(document.GetDocument());

	AssetGroups assets = gameLib.GetAssetGroups();
	gAssetManager.LoadAssets(gameLib.GetNode());

	std::string outfile = workingDir + "/" + "output.xml";
	document.Write(outfile);
	system("pause");
}

int main(int arg, char** argv)
{
	experimental::filesystem::create_directories("sandbox/a/b");
	std::ofstream("sandbox/file1.txt");
	std::ofstream("sandbox/file2.txt");
	for (auto& p : experimental::filesystem::directory_iterator("sandbox"))
		std::cout << p.path() << '\n';
	experimental::filesystem::remove_all("sandbox");

	cAudio_System gAudioSystem;
	gAudioSystem.Init(100);

	open_gl();

	ReadGameLibrary("../assets/GameLibrary.xml");

//	test_Audio();

	return 0;
}

