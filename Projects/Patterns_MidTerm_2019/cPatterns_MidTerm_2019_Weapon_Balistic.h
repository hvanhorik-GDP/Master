#pragma once

#include "cPatterns_MidTerm_2019_Weapon.h"

// INFO6044 - balistic weapon

class cPatterns_MidTerm_2019_Weapon_Balistic :
	public cPatterns_MidTerm_2019_Weapon
{
protected:
	friend class cPatterns_MidTerm_2019_World_impl;

	cPatterns_MidTerm_2019_Weapon_Balistic();
	virtual ~cPatterns_MidTerm_2019_Weapon_Balistic();

	virtual bool IsBalistic() final;
	virtual void Shoot(const glm::vec3& source, const glm::vec3& target) final ;
	virtual bool CanIShoot() final;
	virtual void Step(float deltatime) final;
	virtual bool DidWeHit(glm::vec3& where) final;

private:
	float m_flightTime;
	bool m_weHit;
	glm::vec3 m_whereWeHit;
};

