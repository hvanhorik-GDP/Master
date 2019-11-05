#include "cPatterns_MidTerm_2019_World.h"
#include "cPatterns_MidTerm_2019_World_impl.h"

static cPatterns_MidTerm_2019_World_impl* gPatterns_MidTerm_2019_World_impl = NULL;		// The one and only

cPatterns_MidTerm_2019_World::cPatterns_MidTerm_2019_World()
{
	if (!gPatterns_MidTerm_2019_World_impl)
		gPatterns_MidTerm_2019_World_impl = new cPatterns_MidTerm_2019_World_impl();
};

cPatterns_MidTerm_2019_World::~cPatterns_MidTerm_2019_World()
{
};

iPatterns_MidTerm_2019_Robot* cPatterns_MidTerm_2019_World::FindClosetRobot(iPatterns_MidTerm_2019_Robot* me, bool inSight, bool & isLineOfSight)
{
	assert(gPatterns_MidTerm_2019_World_impl);
	return gPatterns_MidTerm_2019_World_impl->FindClosetRobot(me, inSight, isLineOfSight);
}

void cPatterns_MidTerm_2019_World::TeleportRobot(iPatterns_MidTerm_2019_Robot* me)
{
	assert(gPatterns_MidTerm_2019_World_impl);
	gPatterns_MidTerm_2019_World_impl->TeleportRobot(me);
}

void cPatterns_MidTerm_2019_World::CreateRobots(int number, rapidxml::xml_node<>* parent)
{
	assert(gPatterns_MidTerm_2019_World_impl);
	gPatterns_MidTerm_2019_World_impl->CreateRobots(number, parent);
}

void cPatterns_MidTerm_2019_World::Step(float deltatime)
{
	assert(gPatterns_MidTerm_2019_World_impl);
	gPatterns_MidTerm_2019_World_impl->Step(deltatime);

}

int cPatterns_MidTerm_2019_World::NumberOfRobotsLeft()
{
	assert(gPatterns_MidTerm_2019_World_impl);
	return gPatterns_MidTerm_2019_World_impl->NumberOfRobotsLeft();
}

std::string cPatterns_MidTerm_2019_World::Winner()
{
	return gPatterns_MidTerm_2019_World_impl->Winner();
}