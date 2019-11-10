#include "cObjectWatcher.h"
#include "Media_Project_02_ObjectCreator.h"
#include <iostream>

cObjectWatcher::cObjectWatcher()
{
}

cObjectWatcher::~cObjectWatcher()
{
}

void cObjectWatcher::AddObject(cObject_Model* object)
{
	assert(object);
	m_VecObjectsWatching.push_back(object);
}

static void PauseAllSounds(cObject_Model* object)
{
	std::vector<std::string> names;
	names.push_back("BallsDropping");
	names.push_back("BallsRolling");
	names.push_back("BallsHitting");
	names.push_back("BallsBouncing");

	for (auto name : names)
	{
		auto sound = FindObject(object, name);
		auto channel = sound->m_channel;
		std::cout << "Pausing " << sound->GetName() << " channel ID: " << channel->m_channel << std::endl;
		if (channel->isPlaying())
			channel->Pause(true);
	}
}

static void RestartChannel(cObject_Channel* sound)
{
	// Turn off the DSP
	std::cout << "Setting Position " << sound->GetName() << " channel ID: " << sound->m_channel->m_channel << std::endl;
	sound->m_channel->SetPosition(0);
	std::cout << "Setting Pause (NOT) " << sound->GetName() << " channel ID: " << sound->m_channel->m_channel << std::endl;
	sound->m_channel->Pause(false);
}

void  cObjectWatcher::Watch(float deltaTime)
{
	waitTime -= deltaTime;
	if (waitTime > 0)
		return;
	for (auto object : m_VecObjectsWatching)
	{
		// Fell off the edge so move the object
		if ((object->positionXYZ.y < -40.0f))
		{
			{
				int min = 50;
				int max = 255;
				int r = rand() % (max - min) + min;
				int g = rand() % (max - min) + min;
				int b = rand() % (max - min) + min;
				glm::vec4 rgb = glm::vec4(float(r) / max, float(g) / max, float(b) / max, 1);
				object->objectColourRGBA = rgb;
			}
			{
				int min = -50;
				int max = 50;
				int x = rand() % (max - min) + min;
				int y = rand() % (50) + 40;
				int z = rand() % (max - min) + min;
				glm::vec3 pos = glm::vec3(float(x), float(y), float(z));
				object->positionXYZ = pos;
			}
			object->velocity = glm::vec3(0.0f, 0.0f, 0.0f);
			object->acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
			int newscale = rand() % 5;

			PauseAllSounds(object);
			auto sound = FindObject(object, "BallsDropping");
			// Turn off the DSP
			RestartChannel(sound);
			waitTime = deltaTime * 60;
		}
		if (object->positionXYZ.y < -10)
		{
			PauseAllSounds(object);
			auto sound = FindObject(object, "BallsDropping");
			// Turn off the DSP
			RestartChannel(sound);
			// turn on the DSP for dropping the ball
			waitTime = deltaTime * 60;
		}
		if (object->HACK_Hit_Sphere)
		{
			PauseAllSounds(object);
			auto sound = FindObject(object, "BallsHitting");
			// Turn off the DSP
			RestartChannel(sound);
			object->HACK_Hit_Sphere = false;
			waitTime = deltaTime * 60;
		}
		if (object->HACK_Hit_plane)
		{
			PauseAllSounds(object);
			auto sound = FindObject(object, "BallsHitting");
			// Turn off the DSP
			RestartChannel(sound);
			object->HACK_Hit_plane = false;
			waitTime = deltaTime * 60;
		}
	}
}