#include "cPhysics_Henky.h"

#include "ObjectManager/cObjectManager.h"
#include "VAOManager/cVAOManager.h"
#include "ObjectItems/cObject_Group.h"

// glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <iostream>


cPhysics_Henky::cPhysics_Henky()
{
	// This is a typical Earth gravity value. 
	// note that this doesn't mean that the simulation will "look good", though... 
//	this->m_Gravity = glm::vec3(0.0f, -9.81f, 0.0f);
	this->m_Gravity = glm::vec3(0.0f, -3.0f, 0.0f);
	return;
}


void cPhysics_Henky::setGravity(glm::vec3 newGravityValue)
{
	this->m_Gravity = newGravityValue;
	return;
}

glm::vec3 cPhysics_Henky::getGravity(void)
{
	return this->m_Gravity;
}


void cPhysics_Henky::IntegrationStep(iObjectManager::iObject_map& map_pGameObjects, float deltaTime)
{


	for (auto object : map_pGameObjects)
	{
		// Get a pointer to the current object (makes the code a little clearer)
		cObject_Model* pCurObj = dynamic_cast<cObject_Model*>(object.second);
		assert(pCurObj);
		// TODO - hack We still need to hack the gravity till we move this into
		// it's own space. Probably the world
		pCurObj->accel = this->m_Gravity;
		pCurObj->IntegrationStep(deltaTime);
	}//for (unsigned int index = 0;

	return;
}

// Returns all the triangles and the closest points
void cPhysics_Henky::GetClosestTriangleToPoint(Point pointXYZ, cItem_Model& mesh, Point& closestPoint, sPhysicsTriangle& closestTriangle)
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

		Point curClosetPoint = ClosestPtPointTriangle( pointXYZ,
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
void cPhysics_Henky::GetClosestTrianglesToSphere(cObject_Model& testSphere, float distanceRange, cItem_Model& mesh, std::vector<sPhysicsTriangle>& vecClosestTriangles)
{


}

// Test each object with every other object
void cPhysics_Henky::TestForCollisions(iObjectManager::iObject_map& map_pGameObjects)
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
		if (outerObject->second->GetType() != "model")
			continue;
		auto inner = outerObject;
		inner++;
		for (auto innerObject = inner; innerObject != map_pGameObjects.end(); ++innerObject)
		{
			if (innerObject->second->GetType() != "model")
				continue;
			cObject_Model* pA = dynamic_cast<cObject_Model*>(outerObject->second);
			assert(pA);
			cObject_Model* pB = dynamic_cast<cObject_Model*>(innerObject->second);
			assert(pB);
			if (pA == pB)
				assert(false);		// huh
			// Ignore invisible objects
			if (!pA->IsVisable() || !pB->IsVisable())
				continue;
			// Calculate our current world coordinates
			pA->matWorld = calculateWorldMatrix(*pA);
			pB->matWorld = calculateWorldMatrix(*pB);

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


// Takes a mesh in "model space" and converts it into "world space"
void cPhysics_Henky::CalculateTransformedMesh(cItem_Model& originalMesh, glm::mat4 matWorld,
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


 //This is JUST the transformation lines from the DrawObject call
glm::mat4 cPhysics_Henky::calculateWorldMatrix(iObject& pCurrentObject)
{
	// TODO  - Hack since we don't have a common route for groups
	// and Models

	glm::vec3 positionXYZ;
	glm::vec3 rotationXYZ;
	float objectScale;
	iObject* parent = pCurrentObject.GetParentObject();
	if (pCurrentObject.GetType() == "model")
	{
		cObject_Model* model = dynamic_cast<cObject_Model*>(&pCurrentObject);
		assert(model);
		positionXYZ = model->positionXYZ;
		rotationXYZ = model->rotationXYZ;
		objectScale = model->scale;
	} 
	else if (pCurrentObject.GetType() == "group")
	{
		cObject_Group* model = dynamic_cast<cObject_Group*>(&pCurrentObject);
		assert(model);
		positionXYZ = model->positionXYZ;
		rotationXYZ = model->rotationXYZ;
		objectScale = model->scale;
	}

	// what to apply first? 
	// Local modifications followed by parent
	// or visa versa;
	glm::mat4 matWorld = glm::mat4(1.0f);
	if (parent)
		matWorld = calculateWorldMatrix(*parent);

	// ******* TRANSLATION TRANSFORM *********
	glm::mat4 matTrans
		= glm::translate(glm::mat4(1.0f),
			glm::vec3(positionXYZ.x,
				positionXYZ.y,
				positionXYZ.z));
	matWorld = matWorld * matTrans;

	// ******* ROTATION TRANSFORM *********
	glm::mat4 rotateZ = glm::rotate(glm::mat4(1.0f),
		rotationXYZ.z,					// Angle 
		glm::vec3(0.0f, 0.0f, 1.0f));
	matWorld = matWorld * rotateZ;

	glm::mat4 rotateY = glm::rotate(glm::mat4(1.0f),
		rotationXYZ.y,					// Angle 
		glm::vec3(0.0f, 1.0f, 0.0f));
	matWorld = matWorld * rotateY;

	glm::mat4 rotateX = glm::rotate(glm::mat4(1.0f),
		rotationXYZ.x,					// Angle 
		glm::vec3(1.0f, 0.0f, 0.0f));
	matWorld = matWorld * rotateX;

	// ******* SCALE TRANSFORM *********
	glm::mat4 scale = glm::scale(glm::mat4(1.0f),
		glm::vec3(objectScale,
			objectScale,
			objectScale));
	matWorld = matWorld * scale;

	// what to apply first? 
	// Local modifications followed by parent
	// or visa versa;
	// This seems wrong since the above works fine
	//if (parent)
	//	matWorld *= calculateWorldMatrix(*parent);

	return matWorld;
}


// Returns all the triangles and the closest points
//void GetClosestTriangleToPoint_Henry(Point pointXYZ, cObject_Model& model, 
// Point& closestPoint, sPhysicsTriangle& closestTriangl);

void cPhysics_Henky::GetClosestTriangleToPoint(
	Point pointXYZ, cObject_Model& object,
	Point& closestPoint, sPhysicsTriangle& closestTriangle)
{
	iItem* item = object.GetItem();
	assert(item);
	cItem_Model* drawMesh = dynamic_cast<cItem_Model*>(item);
	assert(drawMesh);
	// We need to test world coordinates
	auto matWorld = object.matWorld;

	cItem_Model worldMesh;
	CalculateTransformedMesh(*drawMesh, matWorld, worldMesh);

	GetClosestTriangleToPoint(pointXYZ, worldMesh, closestPoint, closestTriangle);
}

// Returns all the triangles and the closest points
//void GetClosestTriangleToPoint_Henry(Point pointXYZ, cObject_Model& model, 
// Point& closestPoint, sPhysicsTriangle& closestTriangl);

void cPhysics_Henky::GetClosestTriangleToPoint_Henry_save(
	Point pointXYZ, cObject_Model& object,
	Point& closestPoint, sPhysicsTriangle& closestTriangle)
{
	iItem* item = object.GetItem();
	assert(item);
	cItem_Model* mesh = dynamic_cast<cItem_Model*>(item);
	assert(mesh);
	// We need to test world coordinates
	auto matWorld = object.matWorld;

	// Assume the closest distance is REALLY far away
	float closestDistanceSoFar = FLT_MAX;

	for (unsigned int triIndex = 0;
		triIndex != mesh->m_vecTriangles.size();
		triIndex++)
	{
		cItem_Model::sPlyTriangle& curTriangle = mesh->m_vecTriangles[triIndex];

		// Get the vertices of the triangle
		cItem_Model::sPlyVertexXYZ triVert1 = mesh->m_vecVertices[curTriangle.vert_index_1];
		cItem_Model::sPlyVertexXYZ triVert2 = mesh->m_vecVertices[curTriangle.vert_index_2];
		cItem_Model::sPlyVertexXYZ triVert3 = mesh->m_vecVertices[curTriangle.vert_index_3];

		glm::vec4 tri4VertPoint1;
		tri4VertPoint1.x = triVert1.x;
		tri4VertPoint1.y = triVert1.y;
		tri4VertPoint1.z = triVert1.z;
		glm::vec4 worldPoint1 = matWorld * tri4VertPoint1;
		glm::vec3 triVertPoint1 = worldPoint1;

		glm::vec4 tri4VertPoint2;
		tri4VertPoint2.x = triVert2.x;
		tri4VertPoint2.y = triVert2.y;
		tri4VertPoint2.z = triVert2.z;
		glm::vec4 worldPoint2 = matWorld * tri4VertPoint2;
		glm::vec3 triVertPoint2 = worldPoint2;

		glm::vec4 tri4VertPoint3;
		tri4VertPoint3.x = triVert3.x;
		tri4VertPoint3.y = triVert3.y;
		tri4VertPoint3.z = triVert3.z;
		glm::vec4 worldPoint3 = matWorld * tri4VertPoint3;
		glm::vec3 triVertPoint3 = worldPoint3;

		Point curClosetPoint = ClosestPtPointTriangle(pointXYZ,
			triVertPoint1, triVertPoint2, triVertPoint3);

		// Is this the closest so far?
		float distanceNow = glm::distance(curClosetPoint, pointXYZ);

		// is this closer than the closest distance
		if (distanceNow <= closestDistanceSoFar)
		{
			closestDistanceSoFar = distanceNow;

			closestPoint = curClosetPoint;

			// Copy the triangle information over, as well
			closestTriangle.verts[0] = triVertPoint1;
			closestTriangle.verts[1] = triVertPoint2;
			closestTriangle.verts[2] = triVertPoint3;

			// Quick is to average the normal of all 3 vertices
			glm::vec4 triVert1Norm = glm::vec4(triVert1.nx, triVert1.ny, triVert1.nz, 1.0f);
			glm::vec4 triVert2Norm = glm::vec4(triVert2.nx, triVert2.ny, triVert2.nz, 1.0f);
			glm::vec4 triVert3Norm = glm::vec4(triVert3.nx, triVert3.ny, triVert3.nz, 1.0f);

			// Average of the vertex normals... 
			glm::vec4 objectNormal = (triVert1Norm + triVert2Norm + triVert3Norm) / 3.0f;
			// Put in world coordinates
			glm::vec4 worldNormal = matWorld * objectNormal;
			closestTriangle.normal = worldNormal;
		}

	}//for (unsigned int triIndex = 0;

	return;
}

void cPhysics_Henky::SetDebugRenderer(cDebugRenderer* pDebugRenderer)
{
	mDebugRenderer = pDebugRenderer;
}


void cPhysics_Henky::boundsOfObject(cObject_Model& pObject, glm::vec3& minLimit, glm::vec3& maxLimit)
{
	auto mesh = pObject.GetItem();
	assert(mesh);
	cItem_Model* objectItem = dynamic_cast<cItem_Model*>(mesh);
	assert(objectItem);
	float min = std::numeric_limits<float>::min();
	float max = std::numeric_limits<float>::max();
	glm::vec3 minSoFar(max, max, max);
	glm::vec3 maxSoFar(min, min, min);
	for (auto vertice : objectItem->m_vecVertices)
	{
		if (vertice.x > maxSoFar.x)
			maxSoFar.x = vertice.x;
		if (vertice.y > maxSoFar.y)
			maxSoFar.y = vertice.y;
		if (vertice.z > maxSoFar.z)
			maxSoFar.z = vertice.z;

		if (vertice.x < minSoFar.x)
			minSoFar.x = vertice.x;
		if (vertice.y < minSoFar.y)
			minSoFar.y = vertice.y;
		if (vertice.z < minSoFar.z)
			minSoFar.z = vertice.z;
	}
	minLimit = minSoFar;
	maxLimit = maxSoFar;
}


bool cPhysics_Henky::DoSphereSphereCollisionTest(cObject_Model* pA, cObject_Model* pB,
	sCollisionInfo& collisionInfo)
{
	glm::vec3 distance = pA->positionXYZ - pB->positionXYZ;
	float size = glm::length(distance);
	float radiusSum = pA->SPHERE_radius + pB->SPHERE_radius;
	bool colide = size <= radiusSum;

	if (colide)
	{
		sphereCollisionResponse(pA, pB);
		return true;
	}
	return false;
}

// Borrowed from Michael
void cPhysics_Henky::sphereCollisionResponse(cObject_Model* pA, cObject_Model* pB)
{

	float m1, m2, x1, x2;
	glm::vec3 v1, v2, v1x, v2x, v1y, v2y; 
	glm::vec3 x(pA->positionXYZ - pB->positionXYZ);

	assert(pA->scale == 1.0f);
	assert(pB->scale == 1.0f);

	glm::normalize(x);
	v1 = pA->velocity;
	x1 = glm::dot(x, v1);
	v1x = x * x1;
	v1y = v1 - v1x;
	m1 = pA->inverseMass;

	x = x * -1.0f;
	v2 = pB->velocity;
	x2 = glm::dot(x, v2);
	v2x = x * x2;
	v2y = v2 - v2x;
	m2 = pB->inverseMass;

	//set the position of the spheres to their previous non contact positions to unstick them.
	pA->positionXYZ = pA->previousPosition;
	pB->positionXYZ = pB->previousPosition;

	// Swap the colours to denote a hit
	auto aColour = pA->objectColourRGBA;
	pA->objectColourRGBA = pB->objectColourRGBA;
	pB->objectColourRGBA = aColour;
	//std::cout << "pA - hit: "
	//	<< " x: " << pA->velocity.x
	//	<< " y: " << pA->velocity.y
	//	<< " z: " << pA->velocity.z;
	pA->velocity = glm::vec3(v1x * (m1 - m2) / (m1 + m2) + v2x * (2 * m2) / (m1 + m2) + v1y) / 4.0f;
	pA->velocity -= pA->bounce;
	//std::cout << " to: "
	//	<< " x: " << pA->velocity.x
	//	<< " y: " << pA->velocity.y
	//	<< " z: " << pA->velocity.z
	//	<< std::endl;
	//std::cout << "pb - hit: "
	//	<< " x: " << pB->velocity.x
	//	<< " y: " << pB->velocity.y
	//	<< " z: " << pB->velocity.z;
	pB->velocity = glm::vec3(v1x * (2 * m1) / (m1 + m2) + v2x * (m2 - m1) / (m1 + m2) + v2y) / 4.0f;
	pB->velocity -= pB->bounce;
	//std::cout << " to: "
	//	<< " x: " << pB->velocity.x
	//	<< " y: " << pB->velocity.y
	//	<< " z: " << pB->velocity.z
	//	<< std::endl << std::endl;

}

bool cPhysics_Henky::DoShphereMeshCollisionTest(cObject_Model* pSphere, cObject_Model* pModel,
	sCollisionInfo& collisionInfo)
{
	Sphere worldSphere;
	glm::vec4 worldSpherevec = /*pSphere->matWorld * */ glm::vec4(pSphere->positionXYZ, 1.0f);
	worldSphere.c = worldSpherevec;
	worldSphere.r = pSphere->SPHERE_radius/* * pSphere->scale*/;

	iItem* itemMesh = pModel->GetItem();
	assert(itemMesh);
	cItem_Model* modelMesh = dynamic_cast<cItem_Model*>(itemMesh);
	assert(modelMesh);
	sPhysicsTriangle closestTriangle;
	Point closestPoint;
	GetClosestTriangleToPoint(worldSphere.c, *pModel, closestPoint, closestTriangle);

	// Highlight the triangle that I'm closest to
	if (mDebugRenderer)
	{
		mDebugRenderer->addTriangle(closestTriangle.verts[0],
			closestTriangle.verts[1],
			closestTriangle.verts[2],
			glm::vec3(1.0f, 0.0f, 0.0f));
	}

	// Highlight the triangle that I'm closest to
	// To draw the normal, calculate the average of the 3 vertices, 
	// then draw that average + the normal (the normal starts at the 0,0,0 OF THE TRIANGLE)
	glm::vec3 centreOfTriangle = (closestTriangle.verts[0] +
		closestTriangle.verts[1] +
		closestTriangle.verts[2]) / 3.0f;		// Average

	glm::vec3 normalInWorld = centreOfTriangle + (closestTriangle.normal * 20.0f);	// Normal x 10 length

	if (mDebugRenderer)
	{
		mDebugRenderer->addLine(centreOfTriangle,
			normalInWorld,
			glm::vec3(1.0f, 1.0f, 0.0f));

		{
			cObjectManager objectManager;
			auto object = objectManager.FindObjectByName("debug_sphere");
			assert(object);
			cObject_Model* pDebugSphere = dynamic_cast<cObject_Model*>(object);
			glm::mat4 matModel = glm::mat4(1.0f);
			pDebugSphere->positionXYZ = closestPoint;
			pDebugSphere->scale = 1.0f;
			pDebugSphere->debugColour = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);
			pDebugSphere->isWireframe = true;
			pDebugSphere->SetVisable(true);
			cVAOManager().DrawObject(matModel, pDebugSphere);
			pDebugSphere->SetVisable(false);		// Don't display it anymore
		}

		// How far did we penetrate the surface?
		glm::vec3 CentreToClosestPoint = pSphere->positionXYZ - closestPoint;

		// Direction that ball is going is normalized velocity
		glm::vec3 directionBall = glm::normalize(pSphere->velocity);	// 1.0f

		// Calcualte direction to move it back the way it came from
		glm::vec3 oppositeDirection = -directionBall;				// 1.0f

		float distanceToClosestPoint = glm::length(CentreToClosestPoint);

		mDebugRenderer->addLine(pSphere->positionXYZ,
			closestPoint,
			glm::vec3(0.0f, 1.0f, 0.0f),
			1.0f);
	}

	// Are we hitting the triangle? 
	float distance = glm::length(worldSphere.c - closestPoint);

	if (distance <= worldSphere.r)
	{

		// ************************************************************************

		// If you want, move the sphere back to where it just penetrated...
		// So that it will collide exactly where it's supposed to. 
		// But, that's not a big problem.

		// 1. Calculate vector from centre of sphere to closest point
		glm::vec3 vecSphereToClosestPoint = closestPoint - worldSphere.c;

		// 2. Get the length of this vector
		float centreToContractDistance = glm::length(vecSphereToClosestPoint);

		// 3. Create a vector from closest point to radius
		float lengthPositionAdjustment = worldSphere.r - centreToContractDistance;

		// 4. Sphere is moving in the direction of the velocity, so 
		//    we want to move the sphere BACK along this velocity vector

//		glm::vec3 vecDirection = glm::normalize(pSphere->velocity);
		glm::vec3 vecDirection = -closestTriangle.normal;//  glm::normalize(pSphere->velocity);

		glm::vec3 vecPositionAdjust = (-vecDirection) * lengthPositionAdjustment;

		// 5. Reposition sphere 
		pSphere->positionXYZ += (vecPositionAdjust);
		//	pSphere->inverseMass = 0.0f;

		// Push back the sphere to previous position to stop overlap
//		pSphere->positionXYZ = pSphere->previousPosition;
//		pSphere->velocity = pSphere->previousVelocity;
		// TODO - test - Models will be moving in the future
//		if (pModel->inverseMass != 0.0f)
//		{
//			pModel->positionXYZ = pModel->previousPosition;
//			pModel->velocity = pModel->previousVelocity;
//		}



		// ************************************************************************


		// Is in contact with the triangle... 
		// Calculate the response vector off the triangle. 
		glm::vec3 velocityVector = glm::normalize(pSphere->velocity);

		// closestTriangle.normal
		glm::vec3 reflectionVec = glm::reflect(velocityVector, closestTriangle.normal);
		reflectionVec = glm::normalize(reflectionVec);

		// Stop the sphere and draw the two vectors...
		//			pShpere->inverseMass = 0.0f;	// Stopped

		glm::vec3 velVecX20 = velocityVector * 10.0f;
		if (mDebugRenderer)
		{
			mDebugRenderer->addLine(closestPoint, velVecX20,
				glm::vec3(1.0f, 0.0f, 0.0f), 30.0f /*seconds*/);
		}

		glm::vec3 reflectionVecX20 = reflectionVec * 10.0f;
		if (mDebugRenderer)
		{
			mDebugRenderer->addLine(closestPoint, reflectionVecX20,
				glm::vec3(0.0f, 1.0f, 1.0f), 30.0f /*seconds*/);
		}

		// Change the direction of the ball (the bounce off the triangle)

		// Get length of the velocity vector
		float speed = glm::length(pSphere->velocity);

		const float minimumspeed = 0.005f;
		const float minimumbouncd = 1.0f;
		if (speed < minimumspeed)
			speed = minimumspeed;
		float bounce = (speed > minimumbouncd) ? pSphere->bounce : 1.0f;
		pSphere->velocity = reflectionVec * speed * bounce;
		//std::cout << "speed: " << speed
		//	<< " Bounce: " << bounce 
		//	<< " Velocity : x: " << pSphere->velocity.x
		//	<< " : y: " << pSphere->velocity.y
		//	<< " : z: " << pSphere->velocity.z << std::endl;
		return true;
	}

	return false;
}

