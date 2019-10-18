#include "cLightManager.h"
#include "ObjectManager/cObjectManager.h"
#include "ObjectItems/cObject_Light.h"
#include "ObjectItems/cObject_World.h"
#include "ObjectItems/cObject_Model.h"
#include "VAOManager/cVAOManager.h"
#include "../Physics/cPhysics_Henky.h"

//static 
const float cLightManager::DEFAULT_ATTEN_CONST = 0.1f;

//static 
const float cLightManager::DEFAULT_ATTEN_LINEAR = 0.1f;

//static 
const float cLightManager::DEFAULT_ATTEN_QUADRATIC = 0.1f;

//static
const float cLightManager::DEFAULT_AMBIENT_TO_DIFFUSE_RATIO = 0.8f;

//static 
const float cLightManager::DEFAULTINFINITEDISTANCE = 10000.0f;

//static 
const float cLightManager::DEFAULDIFFUSEACCURACYTHRESHOLD = 0.001f;

cLightManager::cLightManager(GLint shader)
	: m_ShaderID(shader)
{

}

cLightManager::~cLightManager()
{

}

float cLightManager::calcApproxDistFromAtten(float targetLightLevel)	// Uses the defaults
{
	return this->calcApproxDistFromAtten(targetLightLevel, cLightManager::DEFAULDIFFUSEACCURACYTHRESHOLD);
}

float cLightManager::calcApproxDistFromAtten(float targetLightLevel, float accuracy)	// Uses the defaults
{
	return this->calcApproxDistFromAtten(targetLightLevel, accuracy,
		cLightManager::DEFAULT_ATTEN_CONST,
		cLightManager::DEFAULT_ATTEN_LINEAR,
		cLightManager::DEFAULT_ATTEN_QUADRATIC,
		cLightManager::DEFAULTINFINITEDISTANCE, cLightManager::DEFAULTMAXITERATIONS);
}

float cLightManager::calcApproxDistFromAtten(float targetLightLevel, float accuracy,
	float infiniteDistance,
	float constAttenuation,
	float linearAttenuation,
	float quadraticAttenuation,
	unsigned int maxIterations /*= DEFAULTMAXITERATIONS = 50*/)
{
	// See if the accuracy being set it too big for the targetLightLevel, unless targetLightLevel is actually zero (0.0f)
	// If it's actually zero, then adjusting the accuracy to a tenth of zero would give... wait for it...
	//	zero, and we would max out the iterations
	if (targetLightLevel != 0.0f)
	{
		if ((accuracy * 10.0f) >= targetLightLevel * 10.0f)
		{	// Adjust the accuracy by a hundreth
			accuracy = targetLightLevel / 10.0f;
		}
	}//if ( targetLightLevel != 0.0f )	

	float targetLightLevelLow = targetLightLevel - accuracy;
	//if ( targetLightLevelLow <= 0.0f )	{ targetLightLevel = 0.0f; }
	float targetLightLevelHigh = targetLightLevel + accuracy;

	// See if we're getting a value at infinite. i.e. at 'infinite distance', is the light level too high already
	if (this->calcDiffuseFromAttenByDistance(cLightManager::DEFAULTINFINITEDISTANCE,
		constAttenuation, linearAttenuation, quadraticAttenuation,
		accuracy) > targetLightLevelHigh)
	{	// Yes, so we can never get down to this light level
		return cLightManager::DEFAULTINFINITEDISTANCE;
	}

	// There is a light level somewhere between a distance of 0.0 to DEFAULTINFINITEDISTANCE
	// Set initial guesses
	float distanceGuessLow = 0.0f;
	float distanceGuessHigh = cLightManager::DEFAULTINFINITEDISTANCE;

	unsigned int iterationCount = 0;
	while (iterationCount < maxIterations)
	{
		// Pick a distance between the high and low
		float curDistanceGuess = ((distanceGuessHigh - distanceGuessLow) / 2.0f) + distanceGuessLow;
		// 
		float curDiffuseAtGuessDistance
			= this->calcDiffuseFromAttenByDistance(curDistanceGuess, constAttenuation,
				linearAttenuation, quadraticAttenuation, DEFAULTZEROTHRESHOLD);
		// Could be three possibilities: too low, too high, or in between
		if (curDiffuseAtGuessDistance < targetLightLevelLow)
		{	// Light is too dark, so distance is to HIGH. Reduce and guess again.
			distanceGuessHigh = curDistanceGuess;		// Lower the high limit for the guesses
		}
		else if (curDiffuseAtGuessDistance > targetLightLevelHigh)
		{	// Light is too bright, so distance is to LOW. Increase and guess again
			distanceGuessLow = curDistanceGuess;
		}
		else
		{	// Nailed it! Light level is within range, so return this distance
			return curDistanceGuess;
		}

		iterationCount++;

	}// while ( iterationCount < maxIterations )
	// If we are here, then we ran out of iterations.
	// Pick a distance between the low and high
	float distance = (distanceGuessHigh - distanceGuessLow) / 2.0f;

	return distance;
}

//static 
const float cLightManager::DEFAULTZEROTHRESHOLD = 0.0001f;

float cLightManager::calcDiffuseFromAttenByDistance(
	float distance,
	float constAttenuation,
	float linearAttenuation,
	float quadraticAttenuation,
	float zeroThreshold /*= DEFAULTZEROTHRESHOLD*/)
{
	float diffuse = 1.0f;		// Assume full brightness

	float denominator = constAttenuation +
		linearAttenuation * distance +
		quadraticAttenuation * distance * distance;
	// Is this zero (we don't want a divide by zero, do we)?
	if (denominator <= zeroThreshold)
	{	// Let's just say it's zero, shall we?
		diffuse = 1.0f;
	}
	else
	{
		float atten = 1.0f / denominator;
		diffuse *= atten;
		if (diffuse > 1.0f)
		{
			diffuse = 1.0f;
		}
	}//if ( denominator <= zeroThreshold )
	return diffuse;
}

void cLightManager::ApplyLights()
{
	cObjectManager manager;
	auto lights = manager.GetObjects("light");
	assert(lights);
	for (auto object : (*lights))
	{
		cObject_Light* light = dynamic_cast<cObject_Light *>(object.second);
		assert(light);
		ApplyLight(*light);
	}

	// Also set the position of my "eye" (the camera)
	// uniform vec4 eyeLocation;
	//TODO - for now only a single world
	auto object = manager.FindObjectByName("world");
	assert(object);
	cObject_World* world = dynamic_cast<cObject_World*>(object);

	GLint eyeLocation_UL = glGetUniformLocation(m_ShaderID, "eyeLocation");

	glUniform4f(eyeLocation_UL,
		world->cameraEye.x, 
		world->cameraEye.y, 
		world->cameraEye.z, 
		1.0f);
}

void cLightManager::ApplyLight(cObject_Light& lightObject)
{
	glm::mat4 m(1.0f);
	
	auto parent = lightObject.GetParentObject();
	if (parent)
		m = cPhysics_Henky::calculateWorldMatrix(*parent);

	std::string lightPrefix = lightObject.shaderEntry;
	// Set the lighting values for the shader. There is only 1 light right now.
	// uniform vec4 theLights[x].position
	// uniform vec4 theLights[x].diffuse
	// uniform vec4 theLights[x].specular
	// uniform vec4 theLights[x].atten
	// uniform vec4 theLights[x].direction
	// uniform vec4 theLights[x].param1
	// uniform vec4 theLights[x].param2		
	GLint L_0_position = glGetUniformLocation(m_ShaderID,  (lightPrefix + ".position").c_str());
	GLint L_0_diffuse = glGetUniformLocation(m_ShaderID,   (lightPrefix + ".diffuse").c_str());
	GLint L_0_specular = glGetUniformLocation(m_ShaderID,  (lightPrefix + ".specular").c_str());
	GLint L_0_atten = glGetUniformLocation(m_ShaderID,     (lightPrefix + ".atten").c_str());
	GLint L_0_direction = glGetUniformLocation(m_ShaderID, (lightPrefix + ".direction").c_str());
	GLint L_0_param1 = glGetUniformLocation(m_ShaderID,    (lightPrefix + ".param1").c_str());
	GLint L_0_param2 = glGetUniformLocation(m_ShaderID,    (lightPrefix + ".param2").c_str());

	auto lightPosition = m * glm::vec4(lightObject.positionXYZ, 1.0f);
	glUniform4f(L_0_position,
		lightPosition.x,
		lightPosition.y,
		lightPosition.z,
		1.0f);

	auto diffuseColour = lightObject.diffuseColour;
	glUniform4f(L_0_diffuse,
		lightObject.diffuseColour.x,
		lightObject.diffuseColour.y,
		lightObject.diffuseColour.z,
		lightObject.diffuseColour.w);
	auto specular = lightObject.specularColour;
	glUniform4f(L_0_specular,
		lightObject.specularColour.x,
		lightObject.specularColour.y,
		lightObject.specularColour.z,
		lightObject.specularColour.w);

	glUniform4f(L_0_atten, 
		lightObject.constantAttenuation,
		lightObject.linearAttenuation,
		lightObject.quadradicAttenuation,
		lightObject.distanceCutOff);	// Distance cut off

	GLfloat lightType = 0.0f;
	switch (lightObject.lightType)
	{
	case cObject_Light::eLightType::POINT:
	{
		lightType = 0.0f;
		lightObject.direction = glm::vec3(0.0f, 0.0f, 0.0f);
		lightObject.spotInnerangle = 0;
		lightObject.spotOuterangle = 0;
		break;
	}
	case cObject_Light::eLightType::SPOT:
	{
		lightType = 1.0f;
		break;
	}
	case cObject_Light::eLightType::DIRECTIONAL:
	{
		lightType = 2.0f;
		lightObject.spotInnerangle = 0;
		lightObject.spotOuterangle = 0;
		break;
	}
	}

	auto direction = m * glm::vec4(lightObject.direction, 1.0f);

	glUniform4f(L_0_direction, 
		direction.x,
		direction.y,
		direction.z,
		1.0f );	

	// Point light:
	glUniform4f(L_0_param1, 
		lightType,
		lightObject.spotInnerangle,
		lightObject.spotOuterangle,
		1.0f);

	glUniform4f(L_0_param2, 
		lightObject.m_isVisable,
		0.0f, 
		0.0f, 
		1.0f);

	//if (lightObject.DebugSpheres)
	{
		cObjectManager manager;
		auto object = manager.FindObjectByName("debug_sphere");
		cObject_Model* pDebugSphere = dynamic_cast<cObject_Model*>(object);
		{
			pDebugSphere->SetVisable(true);
			glm::mat4 matModel = glm::mat4(1.0f);
			pDebugSphere->positionXYZ = lightPosition;
			pDebugSphere->scale = 0.5f;
			pDebugSphere->debugColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			pDebugSphere->isWireframe = true;
			cVAOManager().DrawObject(matModel, pDebugSphere);
		}
		// Draw spheres to represent the attenuation...
		{   // Draw a sphere at 1% brightness
			glm::mat4 matModel = glm::mat4(1.0f);
			pDebugSphere->positionXYZ = lightPosition;
			float sphereSize = calcApproxDistFromAtten(
				0.01f,		// 1% brightness (essentially black)
				0.001f,		// Within 0.1%  
				100000.0f,	// Will quit when it's at this distance
				lightObject.constantAttenuation,
				lightObject.linearAttenuation,
				lightObject.constantAttenuation);
			pDebugSphere->scale = sphereSize;
			pDebugSphere->debugColour = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
			pDebugSphere->isWireframe = true;
			cVAOManager().DrawObject(matModel, pDebugSphere);
		}
		pDebugSphere->SetVisable(false);

	}
}
