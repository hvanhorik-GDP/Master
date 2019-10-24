#pragma once


#include <glm/glm.hpp>
#include <string>
#include <ostream>

class iObject_Physics
{
public:
	iObject_Physics() {};
	virtual ~iObject_Physics() {}

	virtual const glm::vec3& GetVelocity() const = 0;
	virtual const glm::vec3& GetPreviousVelocity() const = 0;
	virtual const glm::vec3& GetAcceleration() const = 0;
	virtual float GetBounce() const = 0;
	virtual float GetInverseMass() const = 0;
	virtual float GetSphereRadius() const = 0;

	virtual void DefineOverrideFunctionsHere() = 0;

	virtual void IntegrationStep(float deltaTime) = 0;
	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const iObject_Physics& val);
};
