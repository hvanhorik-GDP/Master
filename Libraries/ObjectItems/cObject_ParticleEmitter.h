#pragma once
#include "cObject_Common.h"
#include "cObject_Particle.h"
#include <vector>

class cObject_ParticleEmitter : public cObject_Common
{
public:
	typedef std::vector<cObject_Particle*> vec_Particles;
	// This structure matches the file, so that our life is
	//   simpler and happier, and we all get along.

	cObject_ParticleEmitter() {};				// Get's filled in by physics

	cObject_ParticleEmitter(const std::string& type,
		const std::string& name,
		const std::string& asset_id,
		rapidxml::xml_node<>* node);
	virtual ~cObject_ParticleEmitter();

	virtual iObject* Clone(const std::string& newName) final;


	virtual void IntegrationStep(float deltaTime) final;

	void Initialize(glm::vec3 minVelocity, glm::vec3 maxVelocity,
		glm::vec3 minDeltaPosition, glm::vec3 maxDeltaPosition,
		float minLifeSeconds, float maxLifeSeconds,
		int minParticlesPerFrame, int maxParticlesPerFrame);

	// This will be called when we want to draw them
	// Note: returns nothing and passed by reference ("&")

	void getParticles(vec_Particles& vec_pParticles);

	// Recieve a message
	virtual bool RecieveMessage(const iMessage& message) final;

	// Recieve a message and reply
	virtual bool RecieveAndRespond(const iMessage& in, iMessage& reply) final;

	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const cObject_ParticleEmitter& val);

private:
	friend class cObjectManager_ParticleEmitter;

	static const unsigned int DEFAULT_NUM_PARTICLES = 1000;

	glm::vec3 m_acceleration;
	glm::vec3 m_location;

	vec_Particles m_vec_pParticles;

	// Saved for when we call Step()
	// These are set when we call Initialize();
	glm::vec3 m_minVelocity;
	glm::vec3 m_maxVelocity;
	glm::vec3 m_minDeltaPosition;
	glm::vec3 m_maxDeltaPosition;
	float m_minLifeSeconds;
	float m_maxLifeSeconds;
	int m_minParticlesPerFrame;
	int m_maxParticlesPerFrame;
	bool m_initialized;

	// Creates a single particle (called by Initialize and Step)
	void m_CreateNewParticle(glm::vec3 minVelocity, glm::vec3 maxVelocity,
		glm::vec3 minDeltaPosition, glm::vec3 maxDeltaPosition,
		float minLifeSeconds, float maxLifeSeconds);

};

