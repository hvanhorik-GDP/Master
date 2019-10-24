#pragma once

#include "iObject_3d.h"
#include <glm/glm.hpp>
#include <string>

class cObject_3d: public iObject_3d
{
public:

	cObject_3d();
	virtual ~cObject_3d();

	// We don't handle clone method here
	// but instead have our own clone
	virtual cObject_3d* Clone(const std::string& newName) = 0;
	virtual cObject_3d* Clone_3d(const std::string& newName);

	virtual const glm::vec3& GetPosition() const final;
	virtual const glm::vec3& GetPreviousPosition() const final;
	virtual const glm::vec3& GetRoation() const final;
	virtual float GetScale() const final;
	virtual const glm::mat4& GetMatWorld() const final;

	virtual void IntegrationStep(float deltaTime) = 0;
	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const cObject_3d& val);
private:
	glm::vec3  positionXYZ;
	glm::vec3  previousPosition;
	glm::vec3  rotationXYZ;
	float scale;

	glm::mat4 matWorld;			// Calculated - Not loaded from XML

};
