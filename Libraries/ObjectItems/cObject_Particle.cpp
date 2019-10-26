#include "cObject_Particle.h"
#include <iostream>
#include <ostream>

cObject_Particle::cObject_Particle(const std::string& type,
	const std::string& name,
	const std::string& asset_id,
	rapidxml::xml_node<>* node)
	: cObject_Common()
{
	// Hack for now
	LoadCommon(type, name, asset_id, node);

	m_location = glm::vec3(0.0f, 0.0f, 0.0f);
	m_velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	m_lifeTime = 0.0f;
	m_colourRGBA = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	m_orientation = glm::vec3(0.0f, 0.0f, 0.0f);
	m_scale = 1.0f;
	m_acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
}

cObject_Particle::cObject_Particle()
{

}

cObject_Particle::~cObject_Particle()
{
}

iObject* cObject_Particle::Clone(const std::string& newName)
{
	// Copy everything and change the name
	cObject_Particle* ret =
		new cObject_Particle(*this);
	ret->m_name = newName;
	ret->m_node = NULL;			// No XML so it won't update
	return ret;
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

bool cObject_Particle::RecieveMessage(const iMessage& message)
{
	std::cout << __FILE__ " Recieved an unknown message " << std::endl;
	return false;
}

// Recieve a message and reply
bool cObject_Particle::RecieveAndRespond(const iMessage& in, iMessage& reply)
{
	std::cout << __FILE__ " Recieved an unknown message " << std::endl;
	return false;
}
