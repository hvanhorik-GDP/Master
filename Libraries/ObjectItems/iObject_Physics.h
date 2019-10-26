#pragma once

#include <glm/glm.hpp>
#include <string>
#include <ostream>

class iObject;

class iObject_Physics
{
public:

	enum eShapeTypes
	{
		UNKNOWN,				// Default is unknown
		AABB,					// min and max corners 
		SPHERE,					// Radius
		CAPSULE,
		PLANE,
		MESH,					// Triangle test
	};

	iObject_Physics() {};
	virtual ~iObject_Physics() {}

	virtual void Copy_iObject_Physics(const iObject_Physics& from) = 0;

	virtual const glm::vec3& GetVelocity() const = 0;
	virtual const glm::vec3& GetPreviousVelocity() const = 0;
	virtual const glm::vec3& GetAcceleration() const = 0;
	virtual float GetBounce() const = 0;
	virtual float GetInverseMass() const = 0;
	virtual eShapeTypes GetPhysicalShapeType() const = 0;
	virtual float GetSPHERERadius() const = 0;

	// TODO - replace
	virtual const glm::vec3& GetAABB_min() const = 0;
	virtual const glm::vec3& GetAABB_max() const = 0;

	// Physics integration step. Do something to the object based on deltatime
	virtual void IntegrationStep(float deltaTime) = 0;
	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const iObject_Physics& val);

	static iObject_Physics* GetPhysicsInterface(iObject* in);
	static bool HasPhysicsInterface(iObject* in);

};
