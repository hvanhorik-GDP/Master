#pragma once

#include <glm/glm.hpp>

// INFO6044 - Weapon Abstract factory - pure virtual
class iPatterns_MidTerm_2019_Weapon
{
public:
	iPatterns_MidTerm_2019_Weapon() {}
	virtual ~iPatterns_MidTerm_2019_Weapon() {}

	virtual bool IsBalistic() = 0;
	virtual void Shoot(const glm::vec3& source, const glm::vec3& target) = 0;
	virtual bool CanIShoot() = 0;
	virtual void Step(float deltatime) = 0;
	virtual bool DidWeHit(glm::vec3& where) = 0;

};

