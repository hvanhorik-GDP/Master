#include "cObject_3d.h"
#include <ostream>
#include <iostream>
#include <cassert>

cObject_3d::cObject_3d()
{
}

cObject_3d::~cObject_3d()
{
}


std::ostream& operator<<(std::ostream& stream, const cObject_3d& val)
{
	stream << "Got to iAssetManager:cObject3ds by accident" << std::endl;
	return stream;
}

cObject_3d* cObject_3d::Clone_3d(const std::string& newName)
{
	assert(false);
	//TODO - implement
}

const glm::vec3& cObject_3d::GetPosition() const
{
	return positionXYZ;
}

const glm::vec3& cObject_3d::GetPreviousPosition() const
{
	return previousPosition;
}

const glm::vec3& cObject_3d::GetRoation() const
{
	return rotationXYZ;
}

float cObject_3d::GetScale() const
{
	return scale;
}

const glm::mat4& cObject_3d::cObject_3d::GetMatWorld() const
{
	return matWorld;
}
