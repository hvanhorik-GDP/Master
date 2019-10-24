#include "cObject_Physics.h"

cObject_Physics::cObject_Physics()
{

}

cObject_Physics::~cObject_Physics()
{
}

// For debugging purposes - dumps the contents in human readable form
std::ostream& operator<<(std::ostream& stream, const cObject_Physics& val)
{
	stream << "std::ostream& operator<<(std::ostream& stream, const cObject_Physics& val)" << "Not Implemented" << std::endl;
	return stream;
}

const glm::vec3& cObject_Physics::GetVelocity() const
{
	return velocity;
}

const glm::vec3& cObject_Physics::GetPreviousVelocity() const
{
	return previousVelocity;
}

const glm::vec3& cObject_Physics::GetAcceleration() const
{
	return acceleration;
}
float cObject_Physics::GetBounce() const
{
	return bounce;
}
float cObject_Physics::GetInverseMass() const
{
	return inverseMass;
}

cObject_Physics::eShapeTypes cObject_Physics::GetShapeType() const
{
	return physicsShapeType;
}

float cObject_Physics::GetSphereRadius() const
{
	return SPHERE_radius;
}
