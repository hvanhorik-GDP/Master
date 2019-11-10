#include "Media_Project_02_ObjectCreator.h"
#include "cObjectWatcher.h"

#include "AssetItems/cItem_Model.h"
#include "Physics/cPhysics_Henky.h"
#include "ObjectItems/cObject_Group.h"
#include "ObjectItems/cObject_ChannelGroup.h"
#include "ObjectItems/cObject_Channel.h"
#include "Utilities/cRandom.h"


#include <cstdlib>
#include <time.h>
#include <iostream>

static void highPointOfbox(glm::vec3& min, glm::vec3& max)
{
	auto temp = cObjectManager().FindObjectByName("low_cube");
	cObject_Model* cubeObject = dynamic_cast<cObject_Model*>(temp);
	assert(cubeObject);
	cPhysics_Henky::boundsOfObject(*cubeObject, min, max);
}

static float gMaxHeightOfPyramid = 0.0f;

void CreatePyramids(int number, cObjectManager& objectManager, rapidxml::xml_node<>* parent)
{
	srand(unsigned int(time(NULL)));

	iObject* temp = objectManager.FindObjectByName("ground_plane");
	assert(temp);
	cObject_Group* groundGroup = dynamic_cast<cObject_Group*> (temp);
	assert(groundGroup);

	// See where to place the pyrmids
	glm::vec3 minBox;
	glm::vec3 maxBox;
	highPointOfbox(minBox, maxBox);
	float surface = maxBox.y;

	// Make a bunch of pyramids
	std::string name = "pyramid_a";
	temp = objectManager.FindObjectByName(name);
	cObject_Model* pyramid_a = dynamic_cast<cObject_Model*>(temp);


	// How big is the pyramid
	glm::vec3 minPyramid;
	glm::vec3 maxPyramid;
	cPhysics_Henky::boundsOfObject(*pyramid_a, minPyramid, maxPyramid);
	float pyramidHeight = maxPyramid.y;

	for (int i = 0; i < number; ++i)
	{
		std::string newName = name + "_" + std::to_string(i);
		auto temp = pyramid_a->Clone(newName);
		assert(temp);
		cObject_Model* newPyramid = dynamic_cast<cObject_Model*>(temp);
		assert(newPyramid);

		float newscale = float((rand()) % 40 + 30);
		newscale /= 120;
		newPyramid->scale = newscale;
		if (pyramidHeight * newscale > gMaxHeightOfPyramid)
			gMaxHeightOfPyramid = pyramidHeight * newscale;
		{
			int min = 50;
			int max = 255;
			int r = cRandom::randInRange(min, max);
			int g = cRandom::randInRange(min, max);
			int b = cRandom::randInRange(min, max);
			glm::vec4 rgb = glm::vec4(float(r) / max, float(g) / max, float(b) / max, 1);
			newPyramid->objectColourRGBA = rgb;
		}
		{
			int minx = ceil(minBox.x) + ceil(newscale * maxPyramid.x);
			int maxx = floor(maxBox.x) + ceil(newscale * minPyramid.x);
			int minz = ceil(minBox.z) + ceil(newscale * maxPyramid.z);
			int maxz = floor(maxBox.z) + ceil(newscale * minPyramid.z);
			int x = cRandom::randInRange(minx, maxx);
			int y = surface;
			int z = cRandom::randInRange(minz, maxz);
			glm::vec3 pos = glm::vec3(float(x), float(y), float(z));
			newPyramid->positionXYZ = pos;
		}
		newPyramid->SetVisable(true);

		// Save the object to the object array
		objectManager.SaveObject(newPyramid, parent);

		// parent/child pointers
		newPyramid->SetParentObject(groundGroup);
		groundGroup->AddChildObject(newPyramid);
	}
}

cObject_Channel* FindObject(cObject_Model* model, const std::string& name)
{
	auto size = name.size();
	for (auto object : model->m_mapObjects)
	{

		std::string sub = object.second->GetName().substr(0, size);
		if (sub == name)
		{
			cObject_Channel* ret = dynamic_cast<cObject_Channel*>(object.second);
			return ret;
		}
	}
	return NULL;
}

extern cAudio_System_FMOD* g_implFMOD;

static cObject_Channel* createRandomSound(cObject_ChannelGroup* in)
{
	static int startNumber = cRandom::randInRange(10000, 99999);
	// A small hack to only take the original few
	if (!in->m_originalSize)
		in->m_originalSize = in->m_mapObjects.size();
	size_t range = in->m_originalSize;
	assert(range);
	size_t rand = cRandom::randInRange(size_t(0), range);
	int pos = 0;
	iObject* original = NULL;
	for (auto sound : in->m_mapObjects)
	{
		cObject_Channel* snd = dynamic_cast<cObject_Channel*>(sound.second);
		if (!snd->m_isAClone)
		{
			if (pos == rand)
			{
				original = sound.second;
				break;
			}
			++pos;
		}
	}
	assert(original);

	std::string groupName = in->GetName();
	std::string newName = groupName + " " + original->GetName() + "_" + std::to_string(startNumber);
	startNumber++;
	auto temp = original->Clone(newName);
	assert(temp);
	cObject_Channel* newSound = dynamic_cast<cObject_Channel*>(temp);
	newSound->m_isAClone = true;
	assert(newSound);
	// Save it on the channel list
	in->m_mapObjects[newName] = newSound;
	// TODO - have an update routine to rewrite an object
//	cObjectManager().SaveObject(newSound, in->GetNode());
	return newSound;
}

extern cObjectWatcher* gObjectWatcher;

void CreateDropBalls(int number, cObjectManager& objectManager, rapidxml::xml_node<>* parent)
{

	cRandom::randSeed();// srand(unsigned int(time(NULL)));

	iObject* object = NULL;
	object = objectManager.FindObjectByName("BallsRolling");
	assert(object);
	auto BallsRolling = dynamic_cast<cObject_ChannelGroup*>(object);
	assert(BallsRolling);

	object = objectManager.FindObjectByName("BallsHitting");
	assert(object);
	auto BallsHitting = dynamic_cast<cObject_ChannelGroup*>(object);
	assert(BallsHitting);

	object = objectManager.FindObjectByName("BallsBouncing");
	assert(object);
	auto BallsBouncing = dynamic_cast<cObject_ChannelGroup*>(object);
	assert(BallsBouncing);

	object = objectManager.FindObjectByName("BallsDropping");
	assert(object);
	auto BallsDropping = dynamic_cast<cObject_ChannelGroup*>(object);
	assert(BallsDropping);

	object = objectManager.FindObjectByName("AllSounds");
	assert(object);
	auto AllSounds = dynamic_cast<cObject_ChannelGroup*>(object);
	assert(AllSounds);

	// Make a bunch of balls
	std::string name = "Sphere#1";
	auto dropBall = dynamic_cast<cObject_Model*>(objectManager.FindObjectByName(name));
	assert(dropBall);

	for (int i = 0; i < number; ++i)
	{
		// First one is always called "Drop_Sphere" so we can track it.
		std::string newName = "Drop_Sphere";
		if (i != 0)
			newName += "_" + std::to_string(i);
		auto temp = dropBall->Clone(newName);
		assert(temp);
		cObject_Model* newBall = dynamic_cast<cObject_Model*>(temp);
		assert(newBall);
		{
			int min = 50;
			int max = 255;
			int r = cRandom::randInRange(min, max);
			int g = cRandom::randInRange(min, max);
			int b = cRandom::randInRange(min, max);
			glm::vec4 rgb = glm::vec4(float(r) / max, float(g) / max, float(b) / max, 1);
			newBall->objectColourRGBA = rgb;
		}
		{
			int min = -50;
			int max = 50;
			int x = cRandom::randInRange(min, max);
			int y = cRandom::randInRange(int(gMaxHeightOfPyramid), int(gMaxHeightOfPyramid) + 50);
			int z = cRandom::randInRange(min, max);
			glm::vec3 pos = glm::vec3(float(x), float(y), float(z));
			newBall->positionXYZ = pos;
		}
		int newscale = rand() % 5;

		//TODO - HACK - turn off scale
		newBall->m_isVisable = true;
		newBall->scale = 1.0;								// float(newscale);
		newBall->SPHERE_radius = 1.0;						// = float(newscale);
		newBall->HACK_Tracking_Position = true;
		newBall->inverseMass = 1.0;

		g_implFMOD->CreateChannelGroup(newBall->GetName(), newBall->m_channelGroup);

		// Add some sounds to the object and to the sound groups
		{
			cObject_Channel* dropping = createRandomSound(BallsDropping);
			dropping->playSound(false);
			dropping->m_channel_group = &newBall->m_channelGroup;
			newBall->m_mapObjects[dropping->GetName()] = dropping;
			AllSounds->m_mapObjects[dropping->GetName()] = dropping;
			objectManager.SaveObject(dropping, parent);
		}
		{
			cObject_Channel* hitting = createRandomSound(BallsHitting);
			hitting->playSound(true);
			hitting->m_channel_group = &newBall->m_channelGroup;
			newBall->m_mapObjects[hitting->GetName()] = hitting;
			AllSounds->m_mapObjects[hitting->GetName()] = hitting;
			objectManager.SaveObject(hitting, parent);
		}
		{
			cObject_Channel* rolling = createRandomSound(BallsRolling);
			rolling->playSound(true);
			rolling->m_channel_group = &newBall->m_channelGroup;
			newBall->m_mapObjects[rolling->GetName()] = rolling;
			AllSounds->m_mapObjects[rolling->GetName()] = rolling;
			objectManager.SaveObject(rolling, parent);
		}
		{
			cObject_Channel* bouncing = createRandomSound(BallsBouncing);
			bouncing->playSound(true);
			bouncing->m_channel_group = &newBall->m_channelGroup;
			newBall->m_mapObjects[bouncing->GetName()] = bouncing;
			AllSounds->m_mapObjects[bouncing->GetName()] = bouncing;
			objectManager.SaveObject(bouncing, parent);
		}

		objectManager.SaveObject(newBall, parent);
		// Keep an eye on this object
		gObjectWatcher->AddObject(newBall);
	}
}

void CloneObject(int number, const std::string& name, rapidxml::xml_node<>* parent)
{
	srand(unsigned int(time(NULL)));
	cObjectManager objectManager;

	auto object = objectManager.FindObjectByName(name);
	for (int i = 0; i < number; ++i)
	{
		std::string newName = name + "_" + std::to_string(i);
		auto temp = object->Clone(newName);
		assert(temp);
		objectManager.SaveObject(temp, parent);
	}
}
