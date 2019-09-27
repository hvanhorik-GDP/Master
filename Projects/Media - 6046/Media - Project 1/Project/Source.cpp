#include <rapidxml/rapidxml.hpp>

#include "XML/GameLibrary.h"
#include "XML/AssetGroups.h"
#include "XML/XMLDocument.h"
#include "AssetManager/cAssetManager.h"
#include "AssetManager/cAudioAssetManager.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <streambuf>
#include <sstream>
#include <exception>

#include <stdio.h>  /* defines FILENAME_MAX */


#include <direct.h>
#define GetCurrentDir _getcwd

std::string GetCurrentWorkingDir(void) {
	char buff[FILENAME_MAX];
	GetCurrentDir(buff, FILENAME_MAX);
	std::string current_working_dir(buff);
	return current_working_dir;
}

using namespace std;
using namespace rapidxml;
using namespace gamelibrary;

void ReadGameLibrary(const std::string &name)
{
	std::string workingDir = GetCurrentWorkingDir();
	std::string fullpath = workingDir +"/" + name;
	cout << fullpath << endl;
	XMLDocument document;
	document.Read(name);

	GameLibrary gameLib(document.GetDocument());
//	cout << "Library Name: " << gameLib << endl;

	AssetGroups assets = gameLib.GetAssetGroups();
	cAssetManager manager;
	manager.LoadAssets(gameLib.GetNode());

	audioFMOD::initFMOD();
	auto baseManager = manager.GetAssetManager("audios");
	cAudioAssetManager* audioManger = dynamic_cast<cAudioAssetManager*>(baseManager);
	audioManger->PlaySomething();

	//auto gameName = gameLib.GetGameName();
	//cout << "Game Name: " << gameName << endl;
	//{
	//	string newone("A new String");
	//	gameName.SetValue(newone);
	//}
	//cout << "Game Name changed to: " << gameName << endl;

	//auto assets = gameLib.GetGameAssets();
	//cout << " Game Assets all: " << assets << endl;

	//GameAsset_type type(assets.GetNode());
	//cout << "Game Asset Type: " << type.GetValue() << endl;
	
	//GameAsset_open open(assets.GetNode());
	//cout << "Game Asset Open: " << open.GetValue() << endl;



	//for (xml_node<>* player_node = gameLib.GetNode()->first_node("GameAsset");
	//	player_node;
	//	player_node = player_node->next_sibling())
	//{
	//	cout << "player_node - Type: " << 
	//		player_node->first_attribute("type")->value()  << " Open: " <<
	//		player_node->first_attribute("open")-> value() <<
	//		endl;
	//	xml_node<>* namep = player_node->first_node("AssetRoot");
	//	if (namep)
	//		cout << "AssetRoot: " << namep->value() << endl;
	//}

	//DMName dmName(gameLib);
	//cout << "Dungeon Master Name: " << dmName << endl;

	//player::Player rootPlayer(gameLib.GetPlayers());
	//cout << "Players: " << rootPlayer << endl;
	//{
	//	player::PlayerName playerName(rootPlayer.GetPlayerName());
	//	cout << "   Player Name: " << playerName << endl;

	//	player::Description Description(rootPlayer.GetDescription());
	//	cout << "   Player Description: " << Description << endl;

	//	player::HeightCM HeightCM(rootPlayer.GetHeightCM());
	//	cout << "   Player HeightCM: " << HeightCM << endl;

	//	player::WeightKG WeightKG(rootPlayer.GetWeightKG());
	//	cout << "   Player WeightKG: " << WeightKG << endl;
	//}


#if 0
	root_node = document.first_node("Game");

	xml_node<>* name = root_node->first_node("Name");
	if (name)
		cout << "Name: " << name->value() << endl;

	xml_node<>* level = root_node->first_node("Level");
	if (level)
		cout << "Game Level: " << level->value() << endl;

	xml_node<>* dmName = root_node->first_node("DMName");
	if (level)
		cout << "DM Name: " << dmName->value() << endl;

	for (xml_node<>* player_node = root_node->first_node("Player");
		player_node;
		player_node = player_node->next_sibling())
	{
		//		cout << "player_node " << player_node->first_attribute("name")->value() << endl;
		xml_node<>* namep = player_node->first_node("Name");
		if (namep)
			cout << "Name: " << namep->value() << endl;

		xml_node<>* description = player_node->first_node("Description");
		if (description)
			cout << "Description: " << description->value() << endl;

	}
	for (xml_node<>* game_node = platform_node->first_node("Game");
		game_node;
		game_node = game_node->next_sibling())
	{
		cout << "Game Node: " << game_node->first_attribute("name")->value() << endl;
		xml_node<>* genre = game_node->first_node("Genre");
		if (genre)
			cout << "Genre: " << genre->value() << endl;
		xml_node<>* review = game_node->first_node("Review");
		if (review)
			cout << "Review: " << review->value() << endl;
	}
}
#endif
}

int main(int arg, char** argv)
{
	try
	{
		ReadGameLibrary("./assets/GameLibrary.xml");
	}
	catch (std::exception ex)
	{

	}
	catch (...)
	{
		cout << "Unknown Exception";
	}
	system("pause");
	return 0;
}
