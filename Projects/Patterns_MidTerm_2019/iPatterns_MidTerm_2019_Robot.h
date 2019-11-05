#pragma once
#include <glm/glm.hpp>

// INFO6044 - robot interface

class iPatterns_MidTerm_2019_Robot
{
public:
	iPatterns_MidTerm_2019_Robot() {};
	virtual ~iPatterns_MidTerm_2019_Robot() {};

	virtual glm::vec3 GetLocation() = 0;
	virtual void Step(float deltatime) = 0;
};

