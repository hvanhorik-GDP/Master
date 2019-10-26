#include "cObject_ParticleEmitter.h"
#include "Utilities/cRandom.h"

#include <cassert>

cObject_ParticleEmitter::cObject_ParticleEmitter(const std::string& type,
	const std::string& name,
	const std::string& asset_id,
	rapidxml::xml_node<>* node)
	: cObject_Common()
{
	// Hack for now
	LoadCommon(type, name, asset_id, node);

	m_initialized = false;
}

cObject_ParticleEmitter::~cObject_ParticleEmitter()
{
}


iObject* cObject_ParticleEmitter::Clone(const std::string& newName)
{
	// Copy everything and change the name
	cObject_ParticleEmitter* ret =
		new cObject_ParticleEmitter(*this);
	ret->m_name = newName;
	ret->m_node = NULL;			// No XML so it won't update
	return ret;
}

// For debugging purposes - dumps the contents in human readable form
std::ostream& operator<<(std::ostream& stream, const cObject_ParticleEmitter& val)
{
	assert(val.m_initialized);
	stream << "std::ostream& operator<<(std::ostream& stream, const cObject_ParticleEmitter& val)" << "Not Implemented" << std::endl;
	return stream;
}


void cObject_ParticleEmitter::IntegrationStep(float deltaTime)
{
	assert(m_initialized);

	// Loop through the particles:
	// - Decrease the life by "deltaTime"
	// - If "still alive" (lifeTime > 0.0):
	//    - Move the particle
	for (std::vector<cObject_Particle*>::iterator itPart = this->m_vec_pParticles.begin();
		itPart != this->m_vec_pParticles.end();  itPart++)
	{
		cObject_Particle* pCurParticle = *itPart;	// Dereference iterator, giving us the original type
		pCurParticle->IntegrationStep(deltaTime);
	}

	// How many new particles should we create this frame? 
	int numParticleToCreate = cRandom::randInRange<int>(this->m_minParticlesPerFrame, this->m_maxParticlesPerFrame);

	for (int count = 0; count != numParticleToCreate; count++)
	{
		this->m_CreateNewParticle(this->m_minVelocity, this->m_maxVelocity,
			this->m_minDeltaPosition, this->m_maxDeltaPosition,
			this->m_minLifeSeconds, this->m_maxLifeSeconds);
	}//for (int count = 0;

	return;
}

void cObject_ParticleEmitter::Initialize(glm::vec3 minVelocity, glm::vec3 maxVelocity,
	glm::vec3 minDeltaPosition, glm::vec3 maxDeltaPosition,
	float minLifeSeconds, float maxLifeSeconds,
	int minParticlesPerFrame, int maxParticlesPerFrame)
{
	assert(!m_initialized);			// Only one initialize call to an emmitter

	this->m_minVelocity = minVelocity;
	this->m_maxVelocity = maxVelocity;
	this->m_minDeltaPosition = minDeltaPosition;
	this->m_maxDeltaPosition = maxDeltaPosition;
	this->m_minLifeSeconds = minLifeSeconds;
	this->m_maxLifeSeconds = maxLifeSeconds;
	this->m_minParticlesPerFrame = minParticlesPerFrame;
	this->m_maxParticlesPerFrame = maxParticlesPerFrame;

	// Load the vector with the maximum number of particles
	// Reserve doesn't create the objects, it just sets asside space in 1 step
	this->m_vec_pParticles.reserve(cObject_ParticleEmitter::DEFAULT_NUM_PARTICLES);

	for (int count = 0; count != cObject_ParticleEmitter::DEFAULT_NUM_PARTICLES; count++)
	{
		cObject_Particle* pNewParticle = new cObject_Particle();

		// Set the lifetime to 0.0 for all of them
		pNewParticle->m_lifeTime = 0.0f;
		pNewParticle->m_acceleration = m_acceleration;

		this->m_vec_pParticles.push_back(pNewParticle);
	}

	return;
}



void cObject_ParticleEmitter::m_CreateNewParticle(
	glm::vec3 minVelocity, glm::vec3 maxVelocity,
	glm::vec3 minDeltaPosition, glm::vec3 maxDeltaPosition,
	float minLifeSeconds, float maxLifeSeconds)
{
	assert(m_initialized);	

	// Find the 1st particle that has life <= 0.0f
	for (vec_Particles::iterator itPart = this->m_vec_pParticles.begin();
		itPart != this->m_vec_pParticles.end();  itPart++)
	{
		// Is this particle "dead"? 
		cObject_Particle* pCurParticle = *itPart;

		if (pCurParticle->m_lifeTime <= 0.0f)
		{
			// Make it "alive" and set to some values
			pCurParticle->m_lifeTime = cRandom::randInRange<float>(minLifeSeconds, maxLifeSeconds);

			// Set the initial velocity
			pCurParticle->m_velocity.x = cRandom::randInRange<float>(minVelocity.x, maxVelocity.x);
			pCurParticle->m_velocity.y = cRandom::randInRange<float>(minVelocity.y, maxVelocity.y);
			pCurParticle->m_velocity.z = cRandom::randInRange<float>(minVelocity.z, maxVelocity.z);
			pCurParticle->m_acceleration = m_acceleration;

			// TODO: Adjust position based on Max and Min delta postiion
			// (For now, just make the particle the same as the emitter)
			pCurParticle->m_location = this->m_location;
		}
	}
	return;
}


void cObject_ParticleEmitter::getParticles(vec_Particles& vec_pParticles)
{
	assert(m_initialized);

	// Copy the internal vector of particles to the one that is passed.

	vec_pParticles.clear();
	vec_pParticles.reserve(this->m_vec_pParticles.size());
	//	// Sets the pointer values to zero (NULL)
	//	vec_pParticles.resize( this->m_vec_pParticles.size(), 0 );

		// NOTE: There has to be space there, 
		// AND the objects have to be initialized already
	//	std::copy( this->m_vec_pParticles.begin(), 
	//			   this->m_vec_pParticles.end(), 
	//			   vec_pParticles.begin() );

	for (vec_Particles::iterator itPart = this->m_vec_pParticles.begin();
		itPart != this->m_vec_pParticles.end(); itPart++)
	{
		// If alive, copy over
		cObject_Particle* pCurPart = *itPart;

		if (pCurPart->m_lifeTime > 0.0f)
		{
			vec_pParticles.push_back(pCurPart);
		}
	}

	return;
}


//TODO - for now just implement them here.
// need to implement them in every class of iObject
// Recieve a message
bool cObject_ParticleEmitter::RecieveMessage(const iMessage& message)
{
	return false;
}

// Recieve a message and reply
bool cObject_ParticleEmitter::RecieveAndRespond(const iMessage& in, iMessage& reply)
{
	return false;

}
