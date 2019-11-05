#include "HandleDebugLights.h"
#include "../Common/globalStuff.h"
#include <sstream>

void HandleDebugLights(GLuint shaderProgID)
{
	// Set the lighting values for the shader. There is only 1 light right now.
	// uniform vec4 theLights[0].position
	// uniform vec4 theLights[0].diffuse
	// uniform vec4 theLights[0].specular
	// uniform vec4 theLights[0].atten
	// uniform vec4 theLights[0].direction
	// uniform vec4 theLights[0].param1
	// uniform vec4 theLights[0].param2		
	GLint L_0_position = glGetUniformLocation(shaderProgID, "theLights[0].position");
	GLint L_0_diffuse = glGetUniformLocation(shaderProgID, "theLights[0].diffuse");
	GLint L_0_specular = glGetUniformLocation(shaderProgID, "theLights[0].specular");
	GLint L_0_atten = glGetUniformLocation(shaderProgID, "theLights[0].atten");
	GLint L_0_direction = glGetUniformLocation(shaderProgID, "theLights[0].direction");
	GLint L_0_param1 = glGetUniformLocation(shaderProgID, "theLights[0].param1");
	GLint L_0_param2 = glGetUniformLocation(shaderProgID, "theLights[0].param2");

	glUniform4f(L_0_position,
		sexyLightPosition.x,
		sexyLightPosition.y,
		sexyLightPosition.z,
		1.0f);
	glUniform4f(L_0_diffuse, 1.0f, 1.0f, 1.0f, 1.0f);	// White
	glUniform4f(L_0_specular, 1.0f, 1.0f, 1.0f, 1.0f);	// White
	glUniform4f(L_0_atten, 0.0f,  // constant attenuation
		sexyLightLinearAtten,  // Linear 
		sexyLightQuadraticAtten,	// Quadratic 
		1000000.0f);	// Distance cut off

	// Point light:
	glUniform4f(L_0_param1, 0.0f /*POINT light*/, 0.0f, 0.0f, 1.0f);

	//// Spot light
	//glUniform4f(L_0_direction, 
	//			sexyLightSpotDirection.x,		// 0
	//			sexyLightSpotDirection.y,		// -1
	//			sexyLightSpotDirection.z,		// 0
	//			1.0f );	

	//glUniform4f(L_0_param1,
	//			1.0f /*SPOT light*/, 
	//			sexyLightSpotInnerAngle,		// 15
	//			sexyLightSpotOuterAngle,		// 30
	//			1.0f );


	//glUniform4f(L_0_param1,
	//			2.0f /*DIRECTIONAL light*/, 
	//			sexyLightSpotInnerAngle,		// 15
	//			sexyLightSpotOuterAngle,		// 30
	//			1.0f );


	glUniform4f(L_0_param2, 1.0f /*Light is on*/, 0.0f, 0.0f, 1.0f);

	// Also set the position of my "eye" (the camera)
	//uniform vec4 eyeLocation;
	GLint eyeLocation_UL = glGetUniformLocation(shaderProgID, "eyeLocation");

	glUniform4f(eyeLocation_UL,
		old_cameraEye.x, old_cameraEye.y, old_cameraEye.z, 1.0f);


	//std::stringstream ssTitle;
	//ssTitle
	//	<< sexyLightPosition.x << ", "
	//	<< sexyLightPosition.y << ", "
	//	<< sexyLightPosition.z
	//	<< "Atten: "
	//	<< sexyLightConstAtten << " : "
	//	<< sexyLightLinearAtten << " : "
	//	<< sexyLightQuadraticAtten;
	//glfwSetWindowTitle(window, ssTitle.str().c_str());
}