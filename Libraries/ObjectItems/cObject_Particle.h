#pragma once
#include "cObject_Common.h"
#include <vector>

class cObject_Particle : public cObject_Common
{
public:
	// This structure matches the file, so that our life is
	//   simpler and happier, and we all get along.

	cObject_Particle();				// Get's filled in by physics

	cObject_Particle(const std::string& type,
		const std::string& name,
		const std::string& asset_id,
		rapidxml::xml_node<>* node);
	virtual ~cObject_Particle();

	virtual iObject* Clone(const std::string& newName) final;

	virtual void IntegrationStep(float deltaTime) final;

	// Recieve a message
	virtual bool RecieveMessage(const iMessage& message) final;

	// Recieve a message and reply
	virtual bool RecieveAndRespond(const iMessage& in, iMessage& reply) final;

	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const cObject_Particle& val);

private:
	friend class cObjectManager_ParticleEmiiter;
	friend class cObject_ParticleEmitter;
	glm::vec3 m_location;
	glm::vec3 m_velocity;
	float m_lifeTime;
	glm::vec4 m_colourRGBA;	// Colour and transparency
	glm::vec3 m_orientation;
	float m_scale;
	glm::vec3 m_acceleration;	// For each particle

};

