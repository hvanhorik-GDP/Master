#include "cObject_Physics.h"

cObject_Physics::cObject_Physics()
{
}

cObject_Physics::~cObject_Physics()
{
}

void cObject_Physics::Copy_iObject_Physics(const iObject_Physics& from)
{
	velocity = from.GetVelocity();
	acceleration = from.GetAcceleration();
	previousVelocity = from.GetPreviousVelocity();
	bounce = from.GetBounce();
	inverseMass = from.GetInverseMass();
	physicsShapeType = from.GetPhysicalShapeType();
	SPHERE_radius = from.GetSPHERERadius();
	AABB_max = from.GetAABB_max();
	AABB_min = from.GetAABB_min();
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

iObject_Physics::eShapeTypes cObject_Physics::GetPhysicalShapeType() const
{
	return physicsShapeType;
}

float cObject_Physics::GetSPHERERadius() const
{
	return SPHERE_radius;
}


std::string cObject_Physics::ShapeTypeToString(iObject_Physics::eShapeTypes in)
{
	switch (in)
	{
	case eShapeTypes::AABB:
		return "AABB";
	case eShapeTypes::CAPSULE:
		return "CAPSULE";
	case eShapeTypes::MESH:
		return "MESH";
	case eShapeTypes::PLANE:
		return "PLANE";
	case eShapeTypes::SPHERE:
		return "SPHERE";
	}
	return "UNKNOWN";
}

iObject_Physics::eShapeTypes cObject_Physics::StringToShapeType(const std::string& in)
{
	if (in == "AABB")
		return eShapeTypes::AABB;
	if (in == "CAPSULE")
		return eShapeTypes::CAPSULE;
	if (in == "MESH")
		return eShapeTypes::MESH;
	if (in == "PLANE")
		return eShapeTypes::PLANE;
	if (in == "SPHERE")
		return eShapeTypes::SPHERE;
	return eShapeTypes::UNKNOWN;
}
