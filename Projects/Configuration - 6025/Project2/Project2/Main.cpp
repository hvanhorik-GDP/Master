#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>

#include "../Libraries/XML/XMLDocument.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <streambuf>
#include <sstream>
#include <map>
#include <locale.h>
#include <algorithm>

using namespace std;
using namespace rapidxml;

struct sProperty
{
	std::string m_id;
	std::string m_name;
	std::string m_value;
	xml_node<>* m_node;
};

typedef std::map<std::string, sProperty> mapProperies;

struct sAttributes
{
	std::string m_name;
	mapProperies m_mapPoperties;
	xml_node<>* m_node;
};

typedef std::map<std::string, sAttributes> mapAttributes;

struct sPlayer
{
	std::string m_name;
	mapProperies m_mapProperties;
	mapAttributes m_Attributes;
	xml_node<>* m_node;
};

typedef std::map<std::string, sPlayer> mapPlayers;

struct sConfiguration
{
	std::string m_name;
	mapProperies m_mapProperties;
	xml_node<>* m_node;
};

struct sTranslation
{
	std::string m_id;
	std::string m_name;
	xml_node<>* m_node;
};

typedef std::map<string, sTranslation> mapTranslations;

struct sLanguage
{
	std::string m_name;
	mapTranslations m_translations;
	xml_node<>* m_node;
};

typedef std::map<string, sLanguage> mapLanguages;

struct sGameLibrary
{
	sConfiguration m_Configuration;
	mapLanguages m_mapLanguages;
	mapPlayers m_mapPlayers;

};

void ReadProperty(sProperty& inout, xml_node<>* node)
{
	//	id = "1" name = "Player" value = "Henry Van Horik" / >
	auto id = node->first_attribute("id");
	auto name = node->first_attribute("name");
	auto value = node->first_attribute("value");
	if (id)
		inout.m_id = id->value();
	if (name)
		inout.m_name = name->value();
	if (value)
		inout.m_value = value->value();
	inout.m_node = node;
}

void ReadProperties(mapProperies& inout, xml_node<>* node)
{
	for (auto property = node->first_node("Property");
		property;
		property = property->next_sibling())
	{
		if (string(property->name()) == string("Property"))
		{
			sProperty prop;
			::ReadProperty(prop, property);
			inout[prop.m_name] = prop;
		}
	}
}

void ReadAttribute(sAttributes& inout, xml_node<>* node)
{
	auto name = node->first_attribute("name");
	if (name) 
	{
		inout.m_name = name->value();
		::ReadProperties(inout.m_mapPoperties, node);
		inout.m_node = node;
	}
}

void ReadAttributes(mapAttributes& inout, xml_node<>* node)
{
	for (auto attribute = node->first_node("Attributes");
		attribute;
		attribute = attribute->next_sibling())
	{
		if (string(attribute->name()) == string("Attributes"))
			sProperty prop;
		{
			sAttributes attrib;
			::ReadAttribute(attrib, attribute);
			inout[attrib.m_name] = attrib;
		}
	}
}

void ReadPlayers(mapPlayers& inout, xml_node<>* node)
{
	for (auto playernode = node->first_node("Player");
		playernode;
		playernode = playernode->next_sibling())
	{
		if (string(playernode->name()) == string("Player"))
		{
			sPlayer player;
			auto attr = playernode->first_attribute("name");
			if (attr)
			{
				player.m_name = attr->value();
				::ReadAttributes(player.m_Attributes, playernode);
				::ReadProperties(player.m_mapProperties, playernode);
			}
			player.m_node = playernode;
			inout[player.m_name] = player;
		}
	}
}

void ReadConfiguration(sConfiguration& inout, xml_node<>* node)
{
	auto config = node->first_node("Configuration");
	::ReadProperties(inout.m_mapProperties, config);
}


void ReadTranslation(sTranslation& inout, xml_node<>* node)
{
	//	id = "1" name = "Player" value = "Henry Van Horik" / >
	auto id = node->first_attribute("id");
	auto name = node->first_attribute("name");
	if (id)
		inout.m_id = id->value();
	if (name)
		inout.m_name = name->value();
	inout.m_node = node;
}

void ReadTranslations(mapTranslations& inout, xml_node<>* node)
{
	for (auto trans = node->first_node("Translation");
		trans;
		trans = trans->next_sibling())
	{
		if (string(trans->name()) == string("Translation"))
		{
			sTranslation translaton;
			::ReadTranslation(translaton, trans);
			inout[translaton.m_id] = translaton;
		}
	}
}

void ReadLanguage(sLanguage& inout, xml_node<>* node)
{
	::ReadTranslations(inout.m_translations, node);
}

void ReadLanguages(mapLanguages& inout, xml_node<>* node)
{
	for (auto lang = node->first_node("Language");
		lang;
		lang = lang->next_sibling())
	{
		if (string(lang->name()) == string("Language"))
		{
			auto ln = lang->first_attribute("name");
			if (ln)
			{
				auto name = ln->value();
				sLanguage language;
				::ReadLanguage(language, lang);
				inout[name] = language;
			}
		}
	}
}

void ReadGameLibrary(sGameLibrary& inout, xml_node<>* node)
{
	auto gameLibrary = node->first_node("GameLibrary");

	::ReadConfiguration(inout.m_Configuration, gameLibrary);

	::ReadPlayers(inout.m_mapPlayers, gameLibrary);

	::ReadLanguages(inout.m_mapLanguages, gameLibrary);

}


bool HasPlayer(mapPlayers& players, const std::string& inPlayer)
{
	auto player = players.find(inPlayer);
	return (player != players.end());
}

sProperty GetProperty(mapProperies& properties, const std::string& inName)
{
	sProperty ret;
	ret.m_id = -1;
	ret.m_name = "??Unknown??";
	ret.m_value = "";
	auto prop = properties.find(inName);
	if (prop != properties.end())
		ret = properties[inName];
		return ret;
}

bool HasProperty(mapProperies& properties, const std::string& inProperty)
{
	auto property = properties.find(inProperty);
	return (property != properties.end());
}

bool HasLanguage(mapLanguages& languages, const std::string& inlanguage)
{
	auto language = languages.find(inlanguage);
	return (language != languages.end());
}

std::string Translate(const std::string& id, mapLanguages& languages, const std::string& inlanguage)
{
	auto defaultLanguage = languages["english"];
	auto useLanguage = defaultLanguage;
	auto language = languages.find(inlanguage);
	if (language != languages.end())
		useLanguage = languages[inlanguage];

	std::string result = "??? UnKnown ID: " + id;
	auto translateString = useLanguage.m_translations.find(id);
	if (translateString != useLanguage.m_translations.end())
	{
		result = useLanguage.m_translations[id].m_name;
	}
	else
	{
		auto translateString = defaultLanguage.m_translations.find(id);
		if (translateString != defaultLanguage.m_translations.end())
		{
			result = useLanguage.m_translations[id].m_name;
		}
	}
	return result;
}

std::wstring toWstring(const std::string& in)
{
	std::wstring str2(in.length(), L' '); // Make room for characters

	// Copy string to wstring.
	std::copy(in.begin(), in.end(), str2.begin());
	return str2;
}

std::string GenerateHelpMessage(mapLanguages& languages, const std::string& currentLanguage)
{


	std::string sure = Translate("24", languages, currentLanguage);
	std::string validCommands = Translate("25", languages, currentLanguage);

	std::string help = "help - ";
	std::string helpText = Translate("40", languages, currentLanguage);

	std::string language = "language - ";
	std::string launguageText = Translate("41", languages, currentLanguage);

	std::string hit = "hit - ";
	std::string hitText = Translate("42", languages, currentLanguage);

	std::string end = "end - ";
	std::string endText = Translate("43", languages, currentLanguage);

	std::string talk = "talk - ";
	std::string talkText = Translate("44", languages, currentLanguage);

	std::string info = "info - ";
	std::string infoText = Translate("45", languages, currentLanguage);

	std::string spaces = "     ";

	stringstream ss;
	ss << sure << endl
		<< validCommands << ": " << endl
		<< spaces << help << helpText << endl
		<< spaces << language << launguageText << endl
		<< spaces << hit << hitText << endl
		<< spaces << info << infoText << endl
		<< spaces << talk << talkText << endl
		<< spaces << end << endText << endl;

	return ss.str();
	//<Translation id = "40" name = "This message" / >
	//	<Translation id = "41" name = "Set Language to {Value}" / >
	//	<Translation id = "42" name = "Hit Player {Player}" / >
	//	<Translation id = "43" name = "End Game" / >
	//	<Translation id = "44" name = "Say something profain" / >
	//     <Translation id="45" name="Get information on player {player}"/>
	//<Translation id = "24" name = "You really expected me to help you?" / >
	//	<Translation id = "25" name = "Valid Commands are" / >

}

using namespace std;

void Tokens(const std::string& in, std::vector<std::string>& out, const string& separators)
{
	std::string temp = in;
	for (size_t i = 1; i < separators.size(); ++i)
	{
		std::replace(temp.begin(), temp.end(), separators[i], separators[0]);
	}

	stringstream check(temp);

	string intermediate;

	// Tokenizing w.r.t. space ' ' 
	while (getline(check, intermediate, separators[0]))
	{
		if (intermediate.size() != 0)
			out.push_back(intermediate);
	}
}

void SetLanguage(sConfiguration& config, const std::string& newLanguage)
{
	auto properties = config.m_mapProperties;
	auto language = properties["Language"];
	auto node = language.m_node;
	auto attribute = node->first_attribute("value");

	// We need to allocate memory for the string from rapidXML or it will go out of scope
	xml_document<>* doc = node->document();
	auto newstring = doc->allocate_string(newLanguage.c_str());	// Must let rapidxml hold the strings
	attribute->value(newstring);

}

void padTo(std::string& str, const size_t num, const char paddingChar = ' ')
{
	if (num > str.size())
		str.insert(str.size(), num - str.size(), paddingChar);
}

void DisplayProperties(mapProperies props, mapLanguages& languages, const std::string& currentLanguage)
{
	bool odd = true;
	for (auto property : props)
	{
		std::string id1 = property.second.m_id;
		std::string val1 = property.second.m_value;
		std::string text1 = ::Translate(id1, languages, currentLanguage);
		std::string out1 = text1 + ": " + val1;
		padTo(out1, 50, ' ');
		cout << out1;
		if (!odd)
			cout << endl;
		odd = !odd;
	}
	cout << endl;
}

void DisplayInformation(sPlayer& player, mapLanguages& languages, const std::string& currentLanguage)
{
	::DisplayProperties(player.m_mapProperties, languages, currentLanguage);
	//<Translation id = "46" name = "Current Abilities" / >
	cout << endl << ::Translate("46", languages, currentLanguage) << endl;
	::DisplayProperties(player.m_Attributes["Current"].m_mapPoperties, languages, currentLanguage);
	//	<Translation id = "47" name = "Maximum Abilities" / >
	cout << endl << ::Translate("47", languages, currentLanguage) << endl;
	::DisplayProperties(player.m_Attributes["Maximum"].m_mapPoperties, languages, currentLanguage);
	cout << endl;

}

int main(int arg, char** argv)
{
	rapidxml::xml_node<>* ref;
	ref = 0;

	XMLDocument document;
	document.Read("gamedata.xml");
	document.Write("gamedata_backup.xml");

	auto root = document.GetDocument();

	sGameLibrary gameLibrary;
	::ReadGameLibrary(gameLibrary, root);

	auto config = gameLibrary.m_Configuration;
	auto players = gameLibrary.m_mapPlayers;
	auto languages = gameLibrary.m_mapLanguages;
	auto lang = GetProperty(config.m_mapProperties, "Language");
	auto currentLanguage = lang.m_value;
	//currentLanguage = "french";
	//setlocale(LC_ALL, "french");

	if (!HasLanguage(languages, currentLanguage))
	{
		cout << "Invalid Language... back to English" << endl;
		currentLanguage = "english";
	}

	string helpText = GenerateHelpMessage(languages, currentLanguage);

	std::ofstream fs("dump.txt");
	fs << helpText;

	auto wide = toWstring(helpText);
	wcout << wide;

	//<Translation id = "20" name = "Welcome to the super duper Dungeons and Dragons Dungeon Master helper" / >
	std::string welcome = Translate("20", languages, currentLanguage);

	cout << welcome << endl << endl;
	cout << helpText;
	bool end = false;

	while (!end)
	{
		//<Translation id = "26" name = "Command" / >

		std::string prompt = Translate("26", languages, currentLanguage);
		cout << prompt << ": ";
		std::string command;
		getline(cin, command);
		std::vector<std::string> tokens;
		
		Tokens(command, tokens, " "s);
		if (tokens.size() == 0)
		{
			//<Translation id = "22" name = "Unknown Command" / >
			cout << Translate("22", languages, currentLanguage) << endl;
			cout << helpText << endl;
		}
		else if (tokens[0] == "help")
		{
			cout << helpText;
		}
		else if (tokens[0] == "info")
		{
			if (tokens.size() <= 1)			// hack default
				tokens.push_back("henry");
			bool validPlayer = false;
			if (tokens.size() > 1)
			{
				if (HasPlayer(players, tokens[1]))
				{
					validPlayer = true;
					auto player = players[tokens[1]];
					::DisplayInformation(player, languages, currentLanguage);
				}
			}
			if (!validPlayer)
			{
				//< Translation id = "27" name = "Invalid Player" / >
				cout << Translate("27", languages, currentLanguage) << ": " << command << endl;
				cout << helpText << endl;
			}
		}
		else if (tokens[0] == "end")
		{
			end = true;
		}
		else if (tokens[0] == "talk")
		{
			//    <Translation id="30" name="He’s not the Messiah – he’s a very naughty boy."/>
			cout << Translate("30", languages, currentLanguage) << endl;
		}
		else if (tokens[0] == "hit")
		{
			bool validPlayer = false;
			if (tokens.size() > 1)
			{
				if (HasPlayer(players, tokens[1]))
				{
					//    <Translation id="28" name="Hitting Player"/>
					cout << Translate("28", languages, currentLanguage) << ": " << tokens[1] << endl;
					//     <Translation id="48" name="Sorry! You Missed"/>

					// HACK - No time to implement this and not part of the requirements
					cout << Translate("48", languages, currentLanguage) << ": " << tokens[1] << endl;
					validPlayer = true;
				}
			}
			if (!validPlayer)
			{ 
				//< Translation id = "27" name = "Invalid Player" / >
				cout << Translate("27", languages, currentLanguage) << ": " << command << endl;
				cout << helpText << endl;
			}
		} 
		else if (tokens[0] == "language")
		{
			bool validLanguage = false;
			if (tokens.size() > 1)
			{
				if (HasLanguage(languages, tokens[1]))
				{
					//         <Translation id="23" name="Unknown language selected. Yrsssss."/>
					//cout << Translate("23") << ": " << tokens[1] << endl;
					currentLanguage = tokens[1];
					SetLanguage(config, currentLanguage);
					helpText = GenerateHelpMessage(languages, currentLanguage);
					cout << helpText << endl;
					validLanguage = true;
				}
			}
			if (!validLanguage)
			{
				//  <Translation id="23" name="Unknown language selected. Yrsssss."/>
				cout << Translate("23", languages, currentLanguage) << ": " << command << endl;
				//<Translation id = "29" name = "Valid Languages are" / >
				cout << Translate("29", languages, currentLanguage) << ": ";
				for (auto lang : languages)
				{
					cout << lang.first << ", ";
				}
				cout << endl;

			}

		}
		else
		{
			//<Translation id = "22" name = "Unknown Command" / >
			cout << Translate("22", languages, currentLanguage) << ": " << command << endl;
			cout << helpText << endl;
		}
	}
	document.Write("gamedata.xml");
	return 0;
}