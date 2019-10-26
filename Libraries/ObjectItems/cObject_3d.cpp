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

// objects can clone themselves (We don't do it)
void cObject_3d::Copy_iObject_3d(const iObject_3d& from)
{
	positionXYZ = from.GetPosition();
	previousPosition = from.GetPreviousPosition();
	rotationXYZ = from.GetRoation();
	scale = from.GetScale();
	matWorld = from.GetMatWorld();
}


std::ostream& operator<<(std::ostream& stream, const cObject_3d& val)
{
	stream << "Got to iAssetManager:cObject3ds by accident" << std::endl;
	return stream;
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
