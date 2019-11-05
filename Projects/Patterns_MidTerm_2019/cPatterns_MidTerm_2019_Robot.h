#pragma once
#include "iPatterns_MidTerm_2019_Robot.h"
#include "iPatterns_MidTerm_2019_Weapon.h"
#include "ObjectItems/cObject_Model.h"

// INFO6044 - robot class

class cPatterns_MidTerm_2019_Robot: public iPatterns_MidTerm_2019_Robot
{
public:
	cPatterns_MidTerm_2019_Robot();
	virtual ~cPatterns_MidTerm_2019_Robot();

	virtual glm::vec3 GetLocation() final;
	virtual void Step(float deltatime);
private:
	friend class cPatterns_MidTerm_2019_World_impl;

	int m_life;
	glm::vec3 m_location;
	iPatterns_MidTerm_2019_Weapon* m_Weapon;
	cObject_Model* m_Model;
	cObject_Model* m_Box;
	float m_TeleportCountdownTimer;
};
