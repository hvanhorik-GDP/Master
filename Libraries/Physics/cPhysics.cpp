#include "cPhysics.h"

cPhysics::cPhysics()
{
	// This is a typical Earth gravity value. 
	// note that this doesn't mean that the simulation will "look good", though... 
//	this->m_Gravity = glm::vec3(0.0f, -9.81f, 0.0f);
	this->m_Gravity = glm::vec3(0.0f, -1.0f, 0.0f);
	return;
}


void cPhysics::setGravity(glm::vec3 newGravityValue)
{
	this->m_Gravity = newGravityValue;
	return;
}

glm::vec3 cPhysics::getGravity(void)
{
	return this->m_Gravity;
}


void cPhysics::IntegrationStep(iObjectManager::iObject_map& map_pGameObjects, float deltaTime)
{


	for (auto object : map_pGameObjects)
	{
		// Get a pointer to the current object (makes the code a little clearer)
		cObject_Model* pCurObj = dynamic_cast<cObject_Model*>(object.second);
		assert(pCurObj);
		if (pCurObj->inverseMass != 0.0f)
		{

			// Forward Explicit Euler Inetegration
			//NewVelocty += Velocity + ( Ax * DeltaTime )

			// 
			pCurObj->accel = this->m_Gravity;


			pCurObj->velocity.x += pCurObj->accel.x * deltaTime;
			pCurObj->velocity.y += pCurObj->accel.y * deltaTime;
			pCurObj->velocity.z += pCurObj->accel.z * deltaTime;
			//		// Or you can do this...
			//		CurObj.velocity += CurObj.accel * deltaTime;

					//NewPosition = Posistion + ( Vx * DeltaTime )

			pCurObj->positionXYZ.x += pCurObj->velocity.x * deltaTime;
			pCurObj->positionXYZ.y += pCurObj->velocity.y * deltaTime;
			pCurObj->positionXYZ.z += pCurObj->velocity.z * deltaTime;


		}
	}//for (unsigned int index = 0;

	return;
}



// Returns all the triangles and the closest points
void cPhysics::GetClosestTriangleToPoint(Point pointXYZ, cItem_Model& mesh, glm::vec3& closestPoint, sPhysicsTriangle& closestTriangle)
{

	// Assume the closest distance is REALLY far away
	float closestDistanceSoFar = FLT_MAX;


	for (unsigned int triIndex = 0;
		 triIndex != mesh.m_vecTriangles.size();
		 triIndex++)
	{
		cItem_Model::sPlyTriangle& curTriangle = mesh.m_vecTriangles[triIndex];

		// Get the vertices of the triangle
		cItem_Model::sPlyVertexXYZ triVert1 = mesh.m_vecVertices[curTriangle.vert_index_1];
		cItem_Model::sPlyVertexXYZ triVert2 = mesh.m_vecVertices[curTriangle.vert_index_2];
		cItem_Model::sPlyVertexXYZ triVert3 = mesh.m_vecVertices[curTriangle.vert_index_3];

		Point triVertPoint1;
		triVertPoint1.x = triVert1.x;
		triVertPoint1.y = triVert1.y;
		triVertPoint1.z = triVert1.z;

		Point triVertPoint2;
		triVertPoint2.x = triVert2.x;
		triVertPoint2.y = triVert2.y;
		triVertPoint2.z = triVert2.z;

		Point triVertPoint3;
		triVertPoint3.x = triVert3.x;
		triVertPoint3.y = triVert3.y;
		triVertPoint3.z = triVert3.z;

		glm::vec3 curClosetPoint = ClosestPtPointTriangle( pointXYZ,
														   triVertPoint1, triVertPoint2, triVertPoint3);

		// Is this the closest so far?
		float distanceNow = glm::distance(curClosetPoint, pointXYZ);

		// is this closer than the closest distance
		if (distanceNow <= closestDistanceSoFar)
		{
			closestDistanceSoFar = distanceNow;

			closestPoint = curClosetPoint;

			// Copy the triangle information over, as well
			closestTriangle.verts[0].x = triVert1.x;
			closestTriangle.verts[0].y = triVert1.y;
			closestTriangle.verts[0].z = triVert1.z;
			closestTriangle.verts[1].x = triVert2.x;
			closestTriangle.verts[1].y = triVert2.y;
			closestTriangle.verts[1].z = triVert2.z;
			closestTriangle.verts[2].x = triVert3.x;
			closestTriangle.verts[2].y = triVert3.y;
			closestTriangle.verts[2].z = triVert3.z;
			
			// TODO: Copy the normal, too	
			// Quick is to average the normal of all 3 vertices
			glm::vec3 triVert1Norm = glm::vec3(triVert1.nx, triVert1.ny, triVert1.nz );
			glm::vec3 triVert2Norm = glm::vec3(triVert2.nx, triVert2.ny, triVert2.nz );
			glm::vec3 triVert3Norm = glm::vec3(triVert3.nx, triVert3.ny, triVert3.nz );

			// Average of the vertex normals... 
			closestTriangle.normal = (triVert1Norm + triVert2Norm + triVert3Norm) / 3.0f;

		}

	}//for (unsigned int triIndex = 0;

	return;
}

// Will return the closest triangles that are within the range "distanceRange".
// This can be used as a "closest triangles to sphere"
void cPhysics::GetClosestTrianglesToSphere(cObject_Model& testSphere, float distanceRange, cItem_Model& mesh, std::vector<sPhysicsTriangle>& vecClosestTriangles)
{



}

// Test each object with every other object
void cPhysics::TestForCollisions(iObjectManager::iObject_map& map_pGameObjects)
{
	// This will store all the collisions in this frame
	std::vector<sCollisionInfo> vecCollisions;

	sCollisionInfo collisionInfo;

	// Set up loop so we don't compare against ourselves or check objects twice
//	auto outer = map_pGameObjects.begin();
	auto outerend = map_pGameObjects.end();
	outerend--;
	//auto inner = outer;
	//inner++;
//	auto innerend = map_pGameObjects.end();

	for (auto outerObject = map_pGameObjects.begin(); outerObject != outerend; ++outerObject)
	{
		// Get a pointer to the current object (makes the code a little clearer)
		auto inner = outerObject;
		inner++;
		for (auto innerObject = inner; innerObject != map_pGameObjects.end(); ++innerObject)
		{
			cObject_Model* pA = dynamic_cast<cObject_Model*>(outerObject->second);
			cObject_Model* pB = dynamic_cast<cObject_Model*>(innerObject->second);

			if (pA == pB)
				assert(false);		// huh
			if (pA->physicsShapeType == cObject_Model::SPHERE &&
				pB->physicsShapeType == cObject_Model::SPHERE)
			{
				if (DoSphereSphereCollisionTest(pA, pB, collisionInfo))
				{
					vecCollisions.push_back(collisionInfo);
				}
			}
			else if (pA->physicsShapeType == cObject_Model::SPHERE &&
					 pB->physicsShapeType == cObject_Model::MESH)
			{
				if (DoShphereMeshCollisionTest(pA, pB, collisionInfo))
				{
					vecCollisions.push_back(collisionInfo);
				}
			}
			else if (pA->physicsShapeType == cObject_Model::MESH &&
				pB->physicsShapeType == cObject_Model::SPHERE)
			{
				// Backwards this time.
				if (DoShphereMeshCollisionTest(pB, pA, collisionInfo))
				{
					vecCollisions.push_back(collisionInfo);
				}
			}
		
		} //for (auto innerObject = inner; innerObject != innerend; ++innerObject)
	} //for (auto outerObject = outer; outerObject != outerend; ++outerObject)
}

bool cPhysics::DoSphereSphereCollisionTest(cObject_Model* pA, cObject_Model* pB,
								 sCollisionInfo& collisionInfo)
{
	// TODO: 
	// Run the sphere-sphere collision test
	// If collided, load the collisionInfo struct and return true
	// else return false;

	return false;
}
bool cPhysics::DoShphereMeshCollisionTest(cObject_Model* pA, cObject_Model* pB,
								sCollisionInfo& collisionInfo)
{
	// TODO: Do the sphere-Mesh collision test
	// If collided, load the collisionInfo struct and return true
	//  else return false


	return true;
}

// Takes a mesh in "model space" and converts it into "world space"
void cPhysics::CalculateTransformedMesh(cItem_Model& originalMesh, glm::mat4 matWorld,
										cItem_Model& mesh_transformedInWorld)
{
	// Make a copy of the mesh...

	mesh_transformedInWorld = originalMesh;

	// Using the same thing that happens in the shader, 
	// we transform the vertices of the mesh by the world matrix
	// 
	// From the vertex shader:
	// fVertWorldLocation = matModel * vec4(vertPosition.xyz, 1.0);
	//

	for (std::vector<cItem_Model::sPlyVertexXYZ>::iterator itVert = mesh_transformedInWorld.m_vecVertices.begin();
		 itVert != mesh_transformedInWorld.m_vecVertices.end(); itVert++)
	{
		glm::vec4 vertex = glm::vec4(itVert->x, itVert->y, itVert->z, 1.0f);

		// boom goes the dynamite
		// https://www.youtube.com/watch?v=W45DRy7M1no
		glm::vec4 vertexWorldTransformed = matWorld * vertex;

		// Update 
		itVert->x = vertexWorldTransformed.x;
		itVert->y = vertexWorldTransformed.y;
		itVert->z = vertexWorldTransformed.z;


		// CALCAULTE THE NORMALS for the this mesh, too (for the response)
		// for the normal, do the inverse transpose of the world matrix
		glm::mat4 matWorld_Inv_Transp = glm::inverse(glm::transpose(matWorld));


		glm::vec4 normal = glm::vec4(itVert->nx, itVert->ny, itVert->nz, 1.0f);

		// boom goes the dynamite
		// https://www.youtube.com/watch?v=W45DRy7M1no
		glm::vec4 normalWorldTransformed = matWorld_Inv_Transp * normal;

		
		// Update 
		itVert->nx = normalWorldTransformed.x;
		itVert->ny = normalWorldTransformed.y;
		itVert->nz = normalWorldTransformed.z;
	}

	return;
}
