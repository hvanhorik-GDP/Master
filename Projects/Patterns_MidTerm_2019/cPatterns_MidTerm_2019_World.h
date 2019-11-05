#pragma once

#include "iPatterns_MidTerm_2019_World.h"
#include "iPatterns_MidTerm_2019_Robot.h"

#include <rapidxml/rapidxml.hpp>

// INFO6044 - world class (pimpl singletone)

class cPatterns_MidTerm_2019_World_impl;

class cPatterns_MidTerm_2019_World : public iPatterns_MidTerm_2019_World
{
public:
	cPatterns_MidTerm_2019_World();
	virtual ~cPatterns_MidTerm_2019_World();

	virtual iPatterns_MidTerm_2019_Robot* FindClosetRobot(iPatterns_MidTerm_2019_Robot* me, bool inSight, bool & isLineOfSight) final;

	virtual void TeleportRobot(iPatterns_MidTerm_2019_Robot* me) final;
	virtual void CreateRobots(int number, rapidxml::xml_node<>* parent) final;
	virtual void Step(float deltatime) final;

	virtual int NumberOfRobotsLeft() final;
	virtual std::string Winner() final;
};
