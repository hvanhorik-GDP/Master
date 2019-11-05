#pragma once
#include "iPatterns_MidTerm_2019_World.h"
#include "../../Libraries/ObjectItems/cObject_Model.h"

#include <map>
#include <vector>
#include <string>
#include <rapidxml/rapidxml.hpp>

class cPatterns_MidTerm_2019_Robot;
class cPatterns_MidTerm_2019_Weapon;

// INFO6044 - world class (imple singletone)
// INFO0644 - Main mediator and builder

class cPatterns_MidTerm_2019_World_impl : public iPatterns_MidTerm_2019_World
{
protected:
	friend class cPatterns_MidTerm_2019_World;

	cPatterns_MidTerm_2019_World_impl();
	virtual ~cPatterns_MidTerm_2019_World_impl();

	virtual iPatterns_MidTerm_2019_Robot* FindClosetRobot(iPatterns_MidTerm_2019_Robot* me , bool insight, bool & isLineOfSight) final;

	virtual void TeleportRobot(iPatterns_MidTerm_2019_Robot* me) final;
	virtual void CreateRobots(int number, rapidxml::xml_node<>* parent) final;

	virtual void Step(float deltatime) final;

	virtual int NumberOfRobotsLeft() final;

	virtual std::string Winner() final;

protected:
	cObject_Model* m_terrain;
	std::vector< cPatterns_MidTerm_2019_Robot*> m_robots;
	std::vector< cPatterns_MidTerm_2019_Weapon *> m_wepons;
};

