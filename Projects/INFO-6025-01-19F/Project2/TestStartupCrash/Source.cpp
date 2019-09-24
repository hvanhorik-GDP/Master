#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>

//#include "GameLibrary.h"
//#include <boost/make_shared.hpp>

#include <fstream>
#include <iostream>
#include <vector>
#include <streambuf>
#include <sstream>

using namespace std;
using namespace rapidxml;
//using namespace gamelibrary;
//using namespace boost;

void ReadXMLFile()
{
	xml_document<> document;
	xml_node<>* root_node;

	// read
	ifstream sGamelibrary("xmlfile.xml");

	//	stringstream ss;
	//	ss << sGamelibrary.read;

		// Copy file contents into our buffer
	//vector<char> buffer((istreambuf_iterator<char>
	//	(sGamelibrary)), istreambuf_iterator<char>());
	//buffer.push_back('\0');

	////	document.parse<0>(ss.str());
	//document.parse<0>(&buffer[0]);

	//root_node = document.first_node("GameLibrary");
	//XMLNodeBase::spXMLNode root = boost::make_shared<GameLibrary>(GameLibrary(root_node, string("GameLibrary")));
	//root->Load(root);

#if 0
	for (xml_node<>* platform_node = root_node->first_node("Platform");
		platform_node;
		platform_node = platform_node->next_sibling())
	{
		cout << "Platform name: " << platform_node->first_attribute("name")->value() << endl;
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

void ReadDnDFile()
{
	xml_document<> document;
	xml_node<>* root_node;

	// read
	ifstream gamelibrary("DnD.xml");

	//	stringstream ss;
	//	ss << gamelibrary.read;

		// Copy file contents into our buffer
	vector<char> buffer((istreambuf_iterator<char>
		(gamelibrary)), istreambuf_iterator<char>());
	buffer.push_back('\0');

	//	document.parse<0>(ss.str());
	document.parse<0>(&buffer[0]);

	root_node = document.first_node("GameLibrary");

	xml_node<>* name = root_node->first_node("GameName");
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
#if 0
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
	ReadDnDFile();
	system("pause");
	return 0;
}