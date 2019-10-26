#pragma once
#include "iObject_Physics.h"
#include <vector>

class cObject_Physics : public iObject_Physics
{
public:

	cObject_Physics();
	virtual ~cObject_Physics();

	virtual void Copy_iObject_Physics(const iObject_Physics& from) final;

	virtual const glm::vec3& GetVelocity() const final;
	virtual const glm::vec3& GetPreviousVelocity() const final;
	virtual const glm::vec3& GetAcceleration() const final;
	virtual float GetBounce() const final;
	virtual float GetInverseMass() const final;
	virtual cObject_Physics::eShapeTypes GetPhysicalShapeType() const final;
	virtual float GetSPHERERadius() const final;

	// TODO - replace
	virtual const glm::vec3& GetAABB_min() const final;
	virtual const glm::vec3& GetAABB_max() const final;

	static std::string ShapeTypeToString(iObject_Physics::eShapeTypes in);
	static iObject_Physics::eShapeTypes StringToShapeType(const std::string& in);

	virtual void IntegrationStep(float deltaTime) = 0;

	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const cObject_Physics& val);

protected:
	friend class cObjectManagerPart_Physics;

	// Add some physics things
	glm::vec3 velocity;
	glm::vec3 acceleration;
	glm::vec3 previousVelocity;

	// If the object has an inverse mass of 0.0
	//	then it's not updated by the physics code
	float bounce = 1.0;			// bounce percentage
	float inverseMass;			// 0.0f = Doesn't move

	eShapeTypes physicsShapeType;
	glm::vec3 AABB_min, AABB_max;
	float SPHERE_radius;


};

