#include "cObject_Particle.h"

cObject_Particle::cObject_Particle(const std::string& type,
	const std::string& name,
	const std::string& asset_id,
	rapidxml::xml_node<>* node)
	: cObject_Common(type, name, asset_id, node)
{
	m_location = glm::vec3(0.0f, 0.0f, 0.0f);
	m_velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	m_lifeTime = 0.0f;
	m_colourRGBA = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	m_orientation = glm::vec3(0.0f, 0.0f, 0.0f);
	m_scale = 1.0f;
	m_acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
}

cObject_Particle::~cObject_Particle()
{
}

// For debugging purposes - dumps the contents in human readable form
std::ostream& operator<<(std::ostream& stream, const cObject_Particle& val)
{
	stream << "std::ostream& operator<<(std::ostream& stream, const cObject_Particle& val)" << "Not Implemented" << std::endl;
	return stream;
}


void cObject_Particle::IntegrationStep(float deltaTime)
{
	m_lifeTime -= deltaTime;

	// Is it dead, Jim? (Star Trek reference)
	if (m_lifeTime > 0.0f)
	{
		// Update velocity from acceler
		m_velocity += (m_acceleration * deltaTime);

		// Update position from velocity
		m_location += (m_velocity * deltaTime);
	}
}