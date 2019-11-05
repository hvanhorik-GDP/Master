#pragma once

#include "iPatterns_MidTerm_2019_Robot.h"
#include <rapidxml/rapidxml.hpp>
#include <string>

// INFO6044 - world class - interface

class iPatterns_MidTerm_2019_World
{
public:
	iPatterns_MidTerm_2019_World() {}
	virtual ~iPatterns_MidTerm_2019_World() {}

	virtual iPatterns_MidTerm_2019_Robot* FindClosetRobot(iPatterns_MidTerm_2019_Robot* me, bool inSight, bool &isLineOfSight) = 0;

	virtual void TeleportRobot(iPatterns_MidTerm_2019_Robot* me) = 0;
	virtual void CreateRobots(int number, rapidxml::xml_node<>* parent) = 0;

	virtual void Step(float deltatime) = 0;
	virtual int NumberOfRobotsLeft() = 0;
	virtual std::string Winner() = 0;


};

