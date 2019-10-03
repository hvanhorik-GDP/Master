#include <rapidxml/rapidxml.hpp>

#include "GameLibrary/GameLibrary.h"
#include "GameLibrary/AssetGroups.h"
#include "XML/XMLDocument.h"
#include "AssetManager/cAssetManager.h"
#include "AssetManager/cAssetManager_Audios.h"
#include "AssetItems/cItem_Audio.h"
#include "cAudio_System.h"
#include "cAudio_System_FMOD.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <streambuf>
#include <sstream>
#include <exception>

#include <stdio.h>  /* defines FILENAME_MAX */
#include <conio.h>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>

#include <direct.h>


using namespace std;
using namespace rapidxml;
using namespace gamelibrary;



void clear() {
	// CSI[2J clears screen, CSI[H moves the cursor to top-left corner
	for (int i = 0; i < 20; ++i)
		std::cout << endl;
	//	std::cout << "\x1B[2J\x1B[H";
}


void test_Audio(cAssetManager &assetManager, cAudio_System& gAudioSystem)
{
	try
	{
		//		auto baseManager = gAssetManager.GetAssetManager("audios");
		iAssetManager::iItems_map* items = assetManager.GetItems("audios");

		cAudio_System_FMOD* audioSystem = dynamic_cast<cAudio_System_FMOD*>(gAudioSystem.Get_impl());
		assert(audioSystem);

		std::cout << "Would you like Raw Files:";
		system("pause");

		bool shouldExit = false;
		bool raw = false;
		while (!shouldExit)
		{
			if (_kbhit())
			{
				char cur = _getch();
				if (cur == 'y')
					shouldExit = raw = true;
				else if (cur == 'n')
				{
					shouldExit = true;
					raw = false;
				}
			}
			Sleep(10);
		}


		// Treat everything as an indexed group
		std::vector<std::vector<std::string>> groups;

		// We have speakers with individual songs
		std::vector<std::string> speaker1;
		if (raw)
			speaker1.push_back("That's Amore wav");
		else
			speaker1.push_back("That's Amore");

		std::vector<std::string> speaker2;
		if (raw)
			speaker2.push_back("Auld Lang Syne wav");
		else
			speaker2.push_back("Auld Lang Syne");


		std::vector<std::string> speaker3;
		if (raw)
			speaker3.push_back("Hello, Dolly wav");
		else
			speaker3.push_back("Hello, Dolly");

		std::vector<std::string> speaker4;
		if (raw)
			speaker4.push_back("Spanish Flea wav");
		else
			speaker4.push_back("Spanish Flea");


		// Pushback our speakers
		groups.push_back(speaker1);
		groups.push_back(speaker2);
		groups.push_back(speaker3);
		groups.push_back(speaker4);
		int numberOfSpeakers = 4;

		std::vector<std::string> oldman;
		oldman.push_back("let me guess");
		oldman.push_back("Just An Old Man");
		oldman.push_back("Let Me Get My Wheelchair");
		oldman.push_back("One Good Looking Young Lady");
		oldman.push_back("Telling You Right");
		oldman.push_back("Way Too Fast");
		groups.push_back(oldman);

		std::vector<std::string> oldwoman1;
		oldwoman1.push_back("walk that dog");
		oldwoman1.push_back("blackboard");
		groups.push_back(oldwoman1);

		std::vector<std::string> oldwoman2;
		oldwoman2.push_back("He Was So");
		oldwoman2.push_back("I am not Dead");
		oldwoman2.push_back("I had all These Plans");
		groups.push_back(oldwoman2);
		int numberOfPeople = 3;

		int totalSize = numberOfPeople + numberOfSpeakers;
		for (auto i : groups)
		{
			for (auto j : i)
			{
				auto baseItem = (*items)[j];
				auto audioItem = dynamic_cast<cItem_Audio*>(baseItem);
				assert(audioItem);
				std::cout << "Loading Audio File: " << audioItem->GetIndex() << ": " << audioItem->GetRelativeName() << std::endl;
				cAudio_Sound_FMOD* sound = audioItem->GetSound();
				cAudio_Channel_FMOD* channel = audioItem->GetChannel();

				audioSystem->CreateSound(*sound, audioItem->GetRelativeName(), FMOD_CREATESTREAM);
				audioSystem->PlaySound(*sound, *channel);
				channel->Pause(true);
			}
		}

		stringstream help;
		help << "Commands are: " << endl;
		help << "    (space) or (tab) - Move between speakers or people" << endl;
		help << "     u/d             - volume up/down by 5%" << endl;
		help << "     i/o             - pitch up/down by 5%" << endl;
		help << "     b/v             - balance left/right by .05" << endl;
		help << "                        *** NOTE - Pan does not work in speaker mode" << endl;
		help << "     0, 1, 2, 3, 4   - Get a response from active person" << endl;
		help << "     r               - replay track" << endl;
		help << "     ?               - Information on current track" << endl;
		help << "Character interactions: (Case sensitive)" << endl;
		help << "     S               - Seduce" << endl;
		help << "     J               - Tell Joke" << endl;
		help << "     W               - Go for a walk" << endl;
		help << "     D               - Walk the dog" << endl;
		help << "     M               - Watch Monty Python" << endl;
		help << "     (esc)           - To Exit" << endl;
		help << endl << endl << endl;
		help << " Hit a key: ";


		cout << help.str();
		int currentGroupNumber = 0;
		auto currentGroup = groups[currentGroupNumber][0];
		auto baseItem = (*items)[currentGroup];
		auto currentItem = dynamic_cast<cItem_Audio*>(baseItem);
		currentItem->GetChannel()->Pause(false);
		int point = 0;
		shouldExit = false;

		while (!shouldExit)
		{
			if (_kbhit())
			{
				char cur = _getch();
				if (point > 511)
					point = 511;
				switch (cur)
				{
				case ' ':
				case '\t':
				{
					currentItem->GetChannel()->Pause(true);
					currentGroupNumber++;
					clear();
					if (currentGroupNumber < numberOfSpeakers)
					{
						cout << "Switching to: next speaker: " << endl;
					}
					else if (currentGroupNumber < totalSize)
					{
						cout << "Switching to next person:" << endl;
					}
					else
					{
						currentGroupNumber = 0;
						cout << "Wrapping around to first speaker: " << endl;
					}
					currentGroup = groups[currentGroupNumber][0];
					auto baseItem = (*items)[currentGroup];
					currentItem = dynamic_cast<cItem_Audio*>(baseItem);
					currentItem->GetChannel()->SetPosition(0);
					currentItem->GetChannel()->Pause(false);
					cout << "Audio File : " << currentItem->GetIndex() << " : " << currentItem->GetRelativeName() << std::endl;
					break;
				}
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				{
					size_t index = cur - '0';
					size_t number = groups[currentGroupNumber].size();
					if (index < number)
					{
						currentGroup = groups[currentGroupNumber][index];
						baseItem = (*items)[currentGroup];
						currentItem = dynamic_cast<cItem_Audio*>(baseItem);
						currentItem->GetChannel()->SetPosition(0);
						currentItem->GetChannel()->Pause(false);
						clear();
						cout << "Audio File : " << currentItem->GetIndex() << " : " << currentItem->GetRelativeName() << std::endl;
					}
					break;
				}
				case '?':
				{
					// Information
					cItem_Audio::format format = currentItem->GetFormat();
					clear();
					cout << "Audio file information:" << endl << endl;
					cout << "  Name:      " << currentItem->GetRelativeName() << endl;
					cout << "  Type:      " << currentItem->get_type_string() << endl;
					cout << "  Format:    " << currentItem->get_format_string() << endl;
					cout << "  Channels:  " << format.channels << endl;
					cout << "  Bits:      " << format.bits << endl;
					cout << "  Pitch:      " << currentItem->GetChannel()->GetPitch() << endl;
					cout << "  Volume:      " << currentItem->GetChannel()->GetVolume() << endl;
					cout << "  Position:      " << currentItem->GetChannel()->GetPosition() << endl;
					break;
				}
				case 'S':		// - Seduce" << endl;
				{
					{
						auto baseItem = (*items)["One Good Looking Young Lady"];
						auto audioItem = dynamic_cast<cItem_Audio*>(baseItem);
						std::cout << "Loading Audio File: " << audioItem->GetAssetID() << ": " << audioItem->GetRelativeName() << std::endl;
						if (audioItem->GetChannel() == 0)
						{
							audioSystem->CreateSound(*audioItem->GetSound(), audioItem->GetRelativeName(), FMOD_CREATESTREAM);
							audioSystem->PlaySound(*audioItem->GetSound(), *audioItem->GetChannel());
						}
						else
							audioItem->GetChannel()->SetPosition(0);

						audioItem->GetChannel()->Pause(false);
						// Wait for first to finish
						while (audioItem->GetChannel()->isPlaying())
							Sleep(10);
					}

					{
						auto baseItem = (*items)["sensual giggly laughter"];
						auto audioItem = dynamic_cast<cItem_Audio*>(baseItem);
						std::cout << "Loading Audio File: " << audioItem->GetAssetID() << ": " << audioItem->GetRelativeName() << std::endl;
						if (audioItem->GetChannel() == 0)
						{
							audioSystem->CreateSound(*audioItem->GetSound(), audioItem->GetRelativeName(), FMOD_CREATESTREAM);
							audioSystem->PlaySound(*audioItem->GetSound(), *audioItem->GetChannel());
						}
						else
							audioItem->GetChannel()->SetPosition(0);

						audioItem->GetChannel()->SetVolume(audioItem->GetChannel()->GetVolume() * 3);
						audioItem->GetChannel()->Pause(false);
						while (audioItem->GetChannel()->isPlaying())
							Sleep(10);
					}
					break;
				}
				case 'J':         //      - Tell Joke" << endl;
				{
					{
						auto baseItem = (*items)["belly laughter"];
						auto audioItem = dynamic_cast<cItem_Audio*>(baseItem);
						std::cout << "Loading Audio File: " << audioItem->GetAssetID() << ": " << audioItem->GetRelativeName() << std::endl;
						if (audioItem->GetChannel() == 0)
						{
							audioSystem->CreateSound(*audioItem->GetSound(), audioItem->GetRelativeName(), FMOD_CREATESTREAM);
							audioSystem->PlaySound(*audioItem->GetSound(), *audioItem->GetChannel());
						}
						else
							audioItem->GetChannel()->SetPosition(0);
						audioItem->GetChannel()->Pause(false);
					}

					{
						auto baseItem = (*items)["sensual giggly laughter"];
						auto audioItem = dynamic_cast<cItem_Audio*>(baseItem);
						std::cout << "Loading Audio File: " << audioItem->GetAssetID() << ": " << audioItem->GetRelativeName() << std::endl;
						if (audioItem->GetChannel() == 0)
						{
							audioSystem->CreateSound(*audioItem->GetSound(), audioItem->GetRelativeName(), FMOD_CREATESTREAM);
							audioSystem->PlaySound(*audioItem->GetSound(), *audioItem->GetChannel());
						}
						else
							audioItem->GetChannel()->SetPosition(0);

						audioItem->GetChannel()->SetVolume(audioItem->GetChannel()->GetVolume() * 3);
						audioItem->GetChannel()->Pause(false);
					}
					break;
				}
				case 'W':          //     - Go for a walk" << endl;
				{
					{
						auto baseItem = (*items)["Let Me Get My Wheelchair"];
						auto audioItem = dynamic_cast<cItem_Audio*>(baseItem);
						std::cout << "Loading Audio File: " << audioItem->GetAssetID() << ": " << audioItem->GetRelativeName() << std::endl;
						if (audioItem->GetChannel() == 0)
						{
							audioSystem->CreateSound(*audioItem->GetSound(), audioItem->GetRelativeName(), FMOD_CREATESTREAM);
							audioSystem->PlaySound(*audioItem->GetSound(), *audioItem->GetChannel());
						}
						else
							audioItem->GetChannel()->SetPosition(0);
						audioItem->GetChannel()->Pause(false);
						while (audioItem->GetChannel()->isPlaying())
							Sleep(10);
					}

					{
						auto baseItem = (*items)["Way Too Fast"];
						auto audioItem = dynamic_cast<cItem_Audio*>(baseItem);
						std::cout << "Loading Audio File: " << audioItem->GetAssetID() << ": " << audioItem->GetRelativeName() << std::endl;
						if (audioItem->GetChannel() == 0)
						{
							audioSystem->CreateSound(*audioItem->GetSound(), audioItem->GetRelativeName(), FMOD_CREATESTREAM);
							audioSystem->PlaySound(*audioItem->GetSound(), *audioItem->GetChannel());
						}
						else
							audioItem->GetChannel()->SetPosition(0);
						audioItem->GetChannel()->Pause(false);
						while (audioItem->GetChannel()->isPlaying())
							Sleep(10);
					}

					{
						auto baseItem = (*items)["Way Too Fast"];
						auto audioItem = dynamic_cast<cItem_Audio*>(baseItem);
						std::cout << "Loading Audio File: " << audioItem->GetAssetID() << ": " << audioItem->GetRelativeName() << std::endl;
						if (audioItem->GetChannel() == 0)
						{
							audioSystem->CreateSound(*audioItem->GetSound(), audioItem->GetRelativeName(), FMOD_CREATESTREAM);
							audioSystem->PlaySound(*audioItem->GetSound(), *audioItem->GetChannel());
						}
						else
							audioItem->GetChannel()->SetPosition(0);
						audioItem->GetChannel()->Pause(false);
						while (audioItem->GetChannel()->isPlaying())
							Sleep(10);
					}
					{
						auto baseItem = (*items)["Just An Old Man"];
						auto audioItem = dynamic_cast<cItem_Audio*>(baseItem);
						std::cout << "Loading Audio File: " << audioItem->GetAssetID() << ": " << audioItem->GetRelativeName() << std::endl;
						if (audioItem->GetChannel() == 0)
						{
							audioSystem->CreateSound(*audioItem->GetSound(), audioItem->GetRelativeName(), FMOD_CREATESTREAM);
							audioSystem->PlaySound(*audioItem->GetSound(), *audioItem->GetChannel());
						}
						else
							audioItem->GetChannel()->SetPosition(0);
						audioItem->GetChannel()->Pause(false);
					}
				}
				case 'D':          //     - walk that dog" << endl;
				{
					auto baseItem = (*items)["walk that dog"];
					auto audioItem = dynamic_cast<cItem_Audio*>(baseItem);
					std::cout << "Loading Audio File: " << audioItem->GetAssetID() << ": " << audioItem->GetRelativeName() << std::endl;
					if (audioItem->GetChannel() == 0)
					{
						audioSystem->CreateSound(*audioItem->GetSound(), audioItem->GetRelativeName(), FMOD_CREATESTREAM);
						audioSystem->PlaySound(*audioItem->GetSound(), *audioItem->GetChannel());
					}
					else
						audioItem->GetChannel()->SetPosition(0);
					audioItem->GetChannel()->Pause(false);
				}
				case 'M':             //  - Watch Monty Python" << endl;
				{
					auto baseItem = (*items)["I am not Dead"];
					auto audioItem = dynamic_cast<cItem_Audio*>(baseItem);
					std::cout << "Loading Audio File: " << audioItem->GetAssetID() << ": " << audioItem->GetRelativeName() << std::endl;
					if (audioItem->GetChannel() == 0)
					{
						audioSystem->CreateSound(*audioItem->GetSound(), audioItem->GetRelativeName(), FMOD_CREATESTREAM);
						audioSystem->PlaySound(*audioItem->GetSound(), *audioItem->GetChannel());
					}
					else
						audioItem->GetChannel()->SetPosition(0);
					audioItem->GetChannel()->SetVolume(audioItem->GetChannel()->GetVolume() * 3);
					audioItem->GetChannel()->Pause(false);
				}
				case 'u':
				{
					// Up volume
					clear();
					cout << "Increasing volume by 5%";
					float current = currentItem->GetChannel()->GetVolume();
					currentItem->GetChannel()->SetVolume(current * 1.05f);
					float newvolume = currentItem->GetChannel()->GetVolume();
					cout << " Old: " << current << " New: " << newvolume << endl;;
					break;
				}
				case 'd':
				{
					// Up volume
					clear();
					cout << "Decreasing volume by 5%";
					float current = currentItem->GetChannel()->GetVolume();
					currentItem->GetChannel()->SetVolume(current * .95f);
					float newvolume = currentItem->GetChannel()->GetVolume();
					cout << " Old: " << current << " New: " << newvolume << endl;
					break;
				}
				case 'r':
				{
					// Up volume
					clear();
					cout << "Replay Track: " << endl;
					cout << currentItem->GetIndex() << " : " << currentItem->GetRelativeName() << std::endl;
					currentItem->GetChannel()->SetPitch(0);
					break;
				}
				case 'b':
				{
					// balance up
					//clear();
					//cout << "Increasing pan by .05";
					//float current = currentItem->get_pan();
					//currentItem->set_pan(current + .05);
					//float newvolume = currentItem->get_pan();
					//cout << " Old: " << current << " New: " << newvolume << endl;
					break;
				}
				case 'v':
				{
					// balance down
					//clear();
					//cout << "Decreasing pan by .05%";
					//float current = currentItem->get_pan();
					//currentItem->set_pan(current - .05);
					//float newvolume = currentItem->get_pan();
					//cout << " Old: " << current << " New: " << newvolume << endl;
					break;
				}
				case 'i':
				{
					// pitch up
					clear();
					cout << "Increasing pitch by 5%";
					float current = currentItem->GetChannel()->GetPitch();
					currentItem->GetChannel()->SetPitch(current * 1.05f);
					float newvolume = currentItem->GetChannel()->GetPitch();
					cout << " Old: " << current << " New: " << newvolume << endl;
					break;
				}
				case 'p':
				{
					clear();
					bool pause = currentItem->GetChannel()->isPaused();
					std::string s = (pause) ? "Resuming" : "Pausing";
					cout << s << " - The Stream" << endl;
					currentItem->GetChannel()->Pause(!pause);
					break;
				}

				case 'o':
				{
					// pitch down
					clear();
					cout << "Decreasing pan by 5%";
					float current = currentItem->GetChannel()->GetPitch();
					currentItem->GetChannel()->SetPitch(current * 0.95f);
					float newvolume = currentItem->GetChannel()->GetPitch();
					cout << " Old: " << current << " New: " << newvolume << endl;
					break;
				}
				case 27: //ESC key pressed
				{
					shouldExit = true;
					break;
				}
				default:
				{
					clear();
					cout << "Unknown item " << cur << endl;
					// We want to play another audio sound
				}
				}
				cout << help.str();
				Sleep(10);
			}
			Sleep(10);
		}

	}
	catch (std::exception ex)
	{

	}
	catch (...)
	{
		cout << "Unknown Exception";
	}
}