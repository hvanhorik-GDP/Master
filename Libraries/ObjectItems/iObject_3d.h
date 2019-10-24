#pragma once


#include <glm/glm.hpp>
#include <string>
#include <ostream>

class iObject_3d
{
public:

	iObject_3d() {};
	virtual ~iObject_3d() {}

	virtual void DefineOverrideFunctionsHere() = 0;

	virtual const glm::vec3& GetPosition() const = 0;
	virtual const glm::vec3& GetPreviousPosition() const = 0;
	virtual const glm::vec3& GetRoation() const = 0;
	virtual float GetScale() const = 0;
	virtual const glm::mat4& GetMatWorld() const = 0;

	virtual void IntegrationStep(float deltaTime) = 0;
	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const iObject_3d& val);
};
