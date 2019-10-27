#include "cPhysics.h"

// glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr


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
			// We still need to hack the gravity till we move this into
			// it's own space. Probably the world
			pCurObj->acceleration = this->m_Gravity;
			pCurObj->IntegrationStep(deltaTime);
		}
	}//for (unsigned int index = 0;

	return;
}

// Returns all the triangles and the closest points
void cPhysics::GetClosestTriangleToPoint(Point pointXYZ, cItem_Model& mesh, Point& closestPoint, sPhysicsTriangle& closestTriangle)
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
			pA->matWorld = calculateWorldMatrix(*pB);

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
	return false;
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


// This is JUST the transformation lines from the DrawObject call
glm::mat4 cPhysics::calculateWorldMatrix(cObject_Model& pCurrentObject)
{

	glm::mat4 matWorld = glm::mat4(1.0f);

	// ******* TRANSLATION TRANSFORM *********
	glm::mat4 matTrans
		= glm::translate(glm::mat4(1.0f),
			glm::vec3(pCurrentObject.positionXYZ.x,
				pCurrentObject.positionXYZ.y,
				pCurrentObject.positionXYZ.z));
	matWorld = matWorld * matTrans;

	// ******* ROTATION TRANSFORM *********
	glm::mat4 rotateZ = glm::rotate(glm::mat4(1.0f),
		pCurrentObject.rotationXYZ.z,					// Angle 
		glm::vec3(0.0f, 0.0f, 1.0f));
	matWorld = matWorld * rotateZ;

	glm::mat4 rotateY = glm::rotate(glm::mat4(1.0f),
		pCurrentObject.rotationXYZ.y,					// Angle 
		glm::vec3(0.0f, 1.0f, 0.0f));
	matWorld = matWorld * rotateY;

	glm::mat4 rotateX = glm::rotate(glm::mat4(1.0f),
		pCurrentObject.rotationXYZ.x,					// Angle 
		glm::vec3(1.0f, 0.0f, 0.0f));
	matWorld = matWorld * rotateX;

	// ******* SCALE TRANSFORM *********
	glm::mat4 scale = glm::scale(glm::mat4(1.0f),
		glm::vec3(pCurrentObject.scale,
			pCurrentObject.scale,
			pCurrentObject.scale));
	matWorld = matWorld * scale;

	return matWorld;
}

// Returns all the triangles and the closest points
//void GetClosestTriangleToPoint_Henry(Point pointXYZ, cObject_Model& model, 
// Point& closestPoint, sPhysicsTriangle& closestTriangl);

void cPhysics::GetClosestTriangleToPoint_Henry(
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

	// Assume the closest distance is REALLY far away
	float closestDistanceSoFar = FLT_MAX;

	for (unsigned int triIndex = 0;
		triIndex != worldMesh.m_vecTriangles.size();
		triIndex++)
	{
		cItem_Model::sPlyTriangle& curTriangle = worldMesh.m_vecTriangles[triIndex];

		// Get the vertices of the triangle
		cItem_Model::sPlyVertexXYZ triVert1 = worldMesh.m_vecVertices[curTriangle.vert_index_1];
		cItem_Model::sPlyVertexXYZ triVert2 = worldMesh.m_vecVertices[curTriangle.vert_index_2];
		cItem_Model::sPlyVertexXYZ triVert3 = worldMesh.m_vecVertices[curTriangle.vert_index_3];

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
			glm::vec3 triVert1Norm = glm::vec3(triVert1.nx, triVert1.ny, triVert1.nz);
			glm::vec3 triVert2Norm = glm::vec3(triVert2.nx, triVert2.ny, triVert2.nz);
			glm::vec3 triVert3Norm = glm::vec3(triVert3.nx, triVert3.ny, triVert3.nz);

			// Average of the vertex normals... 
			closestTriangle.normal = (triVert1Norm + triVert2Norm + triVert3Norm) / 3.0f;
		}

	}//for (unsigned int triIndex = 0;

	return;
}

bool cPhysics::DoShphereMeshCollisionTest(cObject_Model* pSphere, cObject_Model* pModel,
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
	GetClosestTriangleToPoint_Henry(worldSphere.c, *pModel, closestPoint, closestTriangle);

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
		glm::vec3 vecDirection = /*-closestTriangle.normal;*/  glm::normalize(pSphere->velocity);

		glm::vec3 vecPositionAdjust = (-vecDirection) * lengthPositionAdjustment;

		// 5. Reposition sphere 
		pSphere->positionXYZ += (vecPositionAdjust);
		//pSphere->inverseMass = 0.0f;

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

		const float minimumspeed = 2.0f;
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
		//	return true;
	}
	return false;
}


void cPhysics::SetDebugRenderer(cDebugRenderer* pDebugRenderer)
{
	mDebugRenderer = pDebugRenderer;
}

#include "cPhysics.h"

// Taken from Ericson's book:
cPhysics::Point cPhysics::ClosestPtPointTriangle(Point p, Point a, Point b, Point c)
{
	Vector ab = b - a;
	Vector ac = c - a;
	Vector bc = c - b;

	// Compute parametric position s for projection P' of P on AB,
	// P' = A + s*AB, s = snom/(snom+sdenom)
	float snom = glm::dot(p - a, ab), sdenom = glm::dot(p - b, a - b);

	// Compute parametric position t for projection P' of P on AC,
	// P' = A + t*AC, s = tnom/(tnom+tdenom)
	float tnom = glm::dot(p - a, ac), tdenom = glm::dot(p - c, a - c);

	if (snom <= 0.0f && tnom <= 0.0f) return a; // Vertex region early out

	// Compute parametric position u for projection P' of P on BC,
	// P' = B + u*BC, u = unom/(unom+udenom)
	float unom = glm::dot(p - b, bc), udenom = glm::dot(p - c, b - c);

	if (sdenom <= 0.0f && unom <= 0.0f) return b; // Vertex region early out
	if (tdenom <= 0.0f && udenom <= 0.0f) return c; // Vertex region early out


	// P is outside (or on) AB if the triple scalar product [N PA PB] <= 0
	Vector n = glm::cross(b - a, c - a);
	float vc = glm::dot(n, glm::cross(a - p, b - p));
	// If P outside AB and within feature region of AB,
	// return projection of P onto AB
	if (vc <= 0.0f && snom >= 0.0f && sdenom >= 0.0f)
		return a + snom / (snom + sdenom) * ab;

	// P is outside (or on) BC if the triple scalar product [N PB PC] <= 0
	float va = glm::dot(n, glm::cross(b - p, c - p));
	// If P outside BC and within feature region of BC,
	// return projection of P onto BC
	if (va <= 0.0f && unom >= 0.0f && udenom >= 0.0f)
		return b + unom / (unom + udenom) * bc;

	// P is outside (or on) CA if the triple scalar product [N PC PA] <= 0
	float vb = glm::dot(n, glm::cross(c - p, a - p));
	// If P outside CA and within feature region of CA,
	// return projection of P onto CA
	if (vb <= 0.0f && tnom >= 0.0f && tdenom >= 0.0f)
		return a + tnom / (tnom + tdenom) * ac;

	// P must project inside face region. Compute Q using barycentric coordinates
	float u = va / (va + vb + vc);
	float v = vb / (va + vb + vc);
	float w = 1.0f - u - v; // = vc / (va + vb + vc)
	return u * a + v * b + w * c;
}

int cPhysics::TestSphereTriangle(Sphere s, Point a, Point b, Point c, Point& p)
{
	// Find point P on triangle ABC closest to sphere center
	p = this->ClosestPtPointTriangle(s.c, a, b, c);

	// Sphere and triangle intersect if the (squared) distance from sphere
	// center to point p is less than the (squared) sphere radius
	Vector v = p - s.c;
	return glm::dot(v, v) <= s.r * s.r;
}

int cPhysics::TestSphereSphere(Sphere a, Sphere b)
{
	// Calculate squared distance between centers

	Vector d = a.c - b.c;
	float dist2 = glm::dot(d, d);
	// Spheres intersect if squared distance is less than squared sum of radii
	float radiusSum = a.r + b.r;
	return dist2 <= radiusSum * radiusSum;
}

