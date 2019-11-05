#include "LightDebugSheres.h"
#include "Common/globalStuff.h"
#include "VAOManager/cVAOManager.h"
#include "LightManager/cLightHelper.h"
#include "Common/pFindObjectByFriendlyName.h"

void LightDebugSheres(GLuint shaderProgID, cVAOManager *pTheVAOManager)
{
	cLightHelper pLightHelper;
	cObject_Model* pDebugSphere = pFindObjectByFriendlyName("debug_sphere");
	if (bLightDebugSheresOn)
	{
		pDebugSphere->SetVisable(true);
		{// Draw where the light is at
			glm::mat4 matModel = glm::mat4(1.0f);
			pDebugSphere->positionXYZ = sexyLightPosition;
			pDebugSphere->scale = 0.5f;
			pDebugSphere->debugColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			pDebugSphere->isWireframe = true;
			pTheVAOManager->DrawObject(matModel, pDebugSphere);
		}

		// Draw spheres to represent the attenuation...
		{   // Draw a sphere at 1% brightness
			glm::mat4 matModel = glm::mat4(1.0f);
			pDebugSphere->positionXYZ = sexyLightPosition;
			float sphereSize = pLightHelper.calcApproxDistFromAtten(
				0.01f,		// 1% brightness (essentially black)
				0.001f,		// Within 0.1%  
				100000.0f,	// Will quit when it's at this distance
				sexyLightConstAtten,
				sexyLightLinearAtten,
				sexyLightQuadraticAtten);
			pDebugSphere->scale = sphereSize;
			pDebugSphere->debugColour = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
			pDebugSphere->isWireframe = true;
			pTheVAOManager->DrawObject(matModel, pDebugSphere);
		}
		{   // Draw a sphere at 25% brightness
			glm::mat4 matModel = glm::mat4(1.0f);
			pDebugSphere->positionXYZ = sexyLightPosition;
			float sphereSize = pLightHelper.calcApproxDistFromAtten(
				0.25f,		// 1% brightness (essentially black)
				0.001f,		// Within 0.1%  
				100000.0f,	// Will quit when it's at this distance
				sexyLightConstAtten,
				sexyLightLinearAtten,
				sexyLightQuadraticAtten);
			pDebugSphere->scale = sphereSize;
			pDebugSphere->debugColour = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
			pDebugSphere->isWireframe = true;
			pTheVAOManager->DrawObject(matModel, pDebugSphere);
		}
		{   // Draw a sphere at 50% brightness
			glm::mat4 matModel = glm::mat4(1.0f);
			pDebugSphere->positionXYZ = sexyLightPosition;
			float sphereSize = pLightHelper.calcApproxDistFromAtten(
				0.50f,		// 1% brightness (essentially black)
				0.001f,		// Within 0.1%  
				100000.0f,	// Will quit when it's at this distance
				sexyLightConstAtten,
				sexyLightLinearAtten,
				sexyLightQuadraticAtten);
			pDebugSphere->scale = sphereSize;
			pDebugSphere->debugColour = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);
			pDebugSphere->isWireframe = true;
			pTheVAOManager->DrawObject(matModel, pDebugSphere);
		}
		{   // Draw a sphere at 75% brightness
			glm::mat4 matModel = glm::mat4(1.0f);
			pDebugSphere->positionXYZ = sexyLightPosition;
			float sphereSize = pLightHelper.calcApproxDistFromAtten(
				0.75f,		// 1% brightness (essentially black)
				0.001f,		// Within 0.1%  
				100000.0f,	// Will quit when it's at this distance
				sexyLightConstAtten,
				sexyLightLinearAtten,
				sexyLightQuadraticAtten);
			pDebugSphere->scale = sphereSize;
			pDebugSphere->debugColour = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
			pDebugSphere->isWireframe = true;
			pTheVAOManager->DrawObject(matModel, pDebugSphere);
		}
		{   // Draw a sphere at 95% brightness
			glm::mat4 matModel = glm::mat4(1.0f);
			pDebugSphere->positionXYZ = sexyLightPosition;
			float sphereSize = pLightHelper.calcApproxDistFromAtten(
				0.95f,		// 1% brightness (essentially black)
				0.001f,		// Within 0.1%  
				100000.0f,	// Will quit when it's at this distance
				sexyLightConstAtten,
				sexyLightLinearAtten,
				sexyLightQuadraticAtten);
			pDebugSphere->scale = sphereSize;
			pDebugSphere->debugColour = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
			pDebugSphere->isWireframe = true;
			pTheVAOManager->DrawObject(matModel, pDebugSphere);
		}
		pDebugSphere->SetVisable(false);				// stop displaying it
	}// if (bLightDebugSheresOn) 
}