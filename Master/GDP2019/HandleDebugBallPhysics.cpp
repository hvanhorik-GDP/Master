#include "HandleDebugBallPhysics.h"

#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp>
// glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include "Physics/cPhysics_Henky.h"
#include "VAOManager/cVAOManager.h"
#include "../Common/pFindObjectByFriendlyName.h"
#include "DebugRenderer/cDebugRenderer.h"

#include <iostream>

// Let's draw all the closest points to the sphere
	// on the terrain mesh....
	// 
	// For each triangle in the terrain mesh:
	// - Run ClosestPointToTriangle
	// - Place the debug sphere "there"
	// - Draw it.

	//**********************************************************
	//**********************************************************

void HandleDebugBallPhysics(	GLuint shaderProgID, 
								cPhysics_Henky * pPhsyics,
								cVAOManager* pTheVAOManager, 
								cDebugRenderer* pDebugRenderer,
								std::map<std::string, cItem_Model*>* mapLoaded
)
{
	glm::vec3 closestPoint = glm::vec3(0.0f, 0.0f, 0.0f);
	cPhysics_Henky::sPhysicsTriangle closestTriangle;


	// Update the mesh to match it's world position
	// 
	// NOTE: I'm DRAWING the high resultion mesh, so I'm taking the transformation 
	//       from the mesh that I'm DRAWING, and transforming the LOW RESOLUTION mesh
	//       into the same orientation (position in world space). 

	cObject_Model* pShpere = pFindObjectByFriendlyName("Drop_Sphere");

	cObject_Model* pModel = pFindObjectByFriendlyName("chocolatebunny");

	pPhsyics->GetClosestTriangleToPoint(pShpere->positionXYZ, *pModel, closestPoint, closestTriangle);

	// Highlight the triangle that I'm closest to
	pDebugRenderer->addTriangle(closestTriangle.verts[0],
		closestTriangle.verts[1],
		closestTriangle.verts[2],
		glm::vec3(1.0f, 0.0f, 0.0f));

	// Highlight the triangle that I'm closest to
	// To draw the normal, calculate the average of the 3 vertices, 
	// then draw that average + the normal (the normal starts at the 0,0,0 OF THE TRIANGLE)
	glm::vec3 centreOfTriangle = (closestTriangle.verts[0] +
		closestTriangle.verts[1] +
		closestTriangle.verts[2]) / 3.0f;		// Average

	glm::vec3 normalInWorld = centreOfTriangle + (closestTriangle.normal * 20.0f);	// Normal x 10 length

	pDebugRenderer->addLine(centreOfTriangle,
		normalInWorld,
		glm::vec3(1.0f, 1.0f, 0.0f));

	// Are we hitting the triangle? 
	float distance = glm::length(pShpere->positionXYZ - closestPoint);

	if (distance <= pShpere->SPHERE_radius)
	{

		// ************************************************************************

		// If you want, move the sphere back to where it just penetrated...
		// So that it will collide exactly where it's supposed to. 
		// But, that's not a big problem.

		// 1. Calculate vector from centre of sphere to closest point
		glm::vec3 vecSphereToClosestPoint = closestPoint - pShpere->positionXYZ;

		// 2. Get the length of this vector
		float centreToContractDistance = glm::length(vecSphereToClosestPoint);

		// 3. Create a vector from closest point to radius
		float lengthPositionAdjustment = pShpere->SPHERE_radius - centreToContractDistance;
		//std::cout << "Radius: " << pShpere->SPHERE_radius  
		//	<< " Scale: " << pShpere->scale
		//	<< " Adjust: " << lengthPositionAdjustment << std::endl;

		// 4. Sphere is moving in the direction of the velocity, so 
		//    we want to move the sphere BACK along this velocity vector
		glm::vec3 vecDirection = glm::normalize(pShpere->velocity);

		glm::vec3 vecPositionAdjust = (-vecDirection) * lengthPositionAdjustment;

		// 5. Reposition sphere 
		pShpere->positionXYZ += (vecPositionAdjust);
		//			pShpere->inverseMass = 0.0f;

		// ************************************************************************


		// Is in contact with the triangle... 
		// Calculate the response vector off the triangle. 
		glm::vec3 velocityVector = glm::normalize(pShpere->velocity);

		// closestTriangle.normal
		glm::vec3 reflectionVec = glm::reflect(velocityVector, closestTriangle.normal);
		reflectionVec = glm::normalize(reflectionVec);

		// Stop the sphere and draw the two vectors...
//		pShpere->inverseMass = 0.0f;	// Stopped

		glm::vec3 velVecX20 = velocityVector * 10.0f;
		pDebugRenderer->addLine(closestPoint, velVecX20,
			glm::vec3(1.0f, 0.0f, 0.0f), 30.0f /*seconds*/);

		glm::vec3 reflectionVecX20 = reflectionVec * 10.0f;
		pDebugRenderer->addLine(closestPoint, reflectionVecX20,
			glm::vec3(0.0f, 1.0f, 1.0f), 30.0f /*seconds*/);

		// Change the direction of the ball (the bounce off the triangle)

		// Get length of the velocity vector
		float speed = glm::length(pShpere->velocity);

		const float minimumspeed = 0.1f;
		float bounce = (speed > minimumspeed)? pShpere->bounce: 1.0f;
		pShpere->velocity = reflectionVec * speed * bounce;
	}

	{
		// Draw closest point
		cObject_Model* pDebugSphere = pFindObjectByFriendlyName("debug_sphere");
		glm::mat4 matModel = glm::mat4(1.0f);
		pDebugSphere->positionXYZ = closestPoint;
		pDebugSphere->scale = 1.0f;
		pDebugSphere->debugColour = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);
		pDebugSphere->isWireframe = true;
		pDebugSphere->isVisible = true;
		pTheVAOManager->DrawObject(matModel, pDebugSphere);
		pDebugSphere->isVisible = false;		// Don't display it anymore
	}

	// How far did we penetrate the surface?
	glm::vec3 CentreToClosestPoint = pShpere->positionXYZ - closestPoint;

	// Direction that ball is going is normalized velocity
	glm::vec3 directionBall = glm::normalize(pShpere->velocity);	// 1.0f

	// Calcualte direction to move it back the way it came from
	glm::vec3 oppositeDirection = -directionBall;				// 1.0f

	float distanceToClosestPoint = glm::length(CentreToClosestPoint);

	pDebugRenderer->addLine(pShpere->positionXYZ,
		closestPoint,
		glm::vec3(0.0f, 1.0f, 0.0f),
		1.0f);
}