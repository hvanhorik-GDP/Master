#pragma once
#include "cObject_Common.h"
#include <vector>

class cObject_Light : public cObject_Common
{
public:
	enum eLightType
	{
		UNKNOWN,
		POINT,
		DIRECTIONAL,
		SPOT,
	};
	// This structure matches the file, so that our life is
	//   simpler and happier, and we all get along.

	cObject_Light() {};				// Get's filled in by physics

	cObject_Light(const std::string& type,
		const std::string& name,
		const std::string& asset_id,
		rapidxml::xml_node<>* node);
	virtual ~cObject_Light();

	virtual void IntegrationStep(float deltaTime) final {}

	static std::string LightTypeToString(cObject_Light::eLightType in);
	static cObject_Light::eLightType StringToLightType(std::string& in);

	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const cObject_Light& val);

	// from iMessageInterface
	// Recieve a message
	virtual bool RecieveMessage(const iMessage& message);

	// Recieve a message and reply
	virtual bool RecieveAndRespond(const iMessage& in, iMessage& reply);

private:
	friend class cObjectManager_Light;
	friend class cLightManager;
	std::string shaderEntry;		// theLights[x]
	eLightType lightType;
	glm::vec3 positionXYZ;
	glm::vec4 diffuseColour;
	glm::vec4 specularColour;
	float constantAttenuation;
	float linearAttenuation;
	float quadradicAttenuation;
	float distanceCutOff;

	// Spotlight only
	float spotInnerangle;
	float spotOuterangle;

	glm::vec3 direction;
	// Debug
	bool DebugSpheres;
};
