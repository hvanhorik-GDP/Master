#pragma once

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <string>

class cGameObject
{
public:
	cGameObject()
	{
		scale = 0.0f;
	}
	std::string meshName;
	glm::vec3  positionXYZ;
	glm::vec3  rotationXYZ;
	glm::vec4  objectColourRGBA;
	float scale;
};


