#ifndef _cPhysics_HG_
#define _cPhysics_HG_

//#include "..//ObjectManager/cGameObject.h"
#include "ObjectItems/cObject_Model.h"
#include "../ObjectManager/iObjectManager.h"
#include "../AssetItems/cItem_Model.h"
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <vector>

#pragma comment(lib, "Physics.lib")

class cPhysics
{
public:
	cPhysics();

	// Alias to a type "existing type" "new type name"
	typedef glm::vec3 Point;
	typedef glm::vec3 Vector;

	struct Sphere
	{
		glm::vec3 c;
		float r;
	};	

	struct sPhysicsTriangle
	{
		glm::vec3 verts[3];
		glm::vec3 normal;
	};

	struct sCollisionInfo
	{
		glm::vec3 closestPoint;
		glm::vec3 directionOfApproach;
		float penetrationDistance;
		glm::vec3 adjustmentVector;
		unsigned int Object1_ID;		// Shpere
		unsigned int Object2_ID;		// Sphere or Triangle
	};
	
	// This "moves" the objects based on the inegration step
	void IntegrationStep(iObjectManager::iObject_map& map_pGameObjects,
					      float deltaTime );

	void TestForCollisions(iObjectManager::iObject_map& map_pGameObjects);

	// Returns all the triangles and the closest points
	void GetClosestTriangleToPoint( Point pointXYZ, cItem_Model &model, glm::vec3 &closestPoint, sPhysicsTriangle &closestTriangle );

	// Will return the closest triangles that are within the range "distanceRange".
	// This can be used as a "closest triangles to sphere"
	void GetClosestTrianglesToSphere(cObject_Model& testSphere, float distanceRange, cItem_Model &model, std::vector<sPhysicsTriangle> &vecClosestTriangles );


	// Taken from Ericson's book:
	Point ClosestPtPointTriangle(Point p, Point a, Point b, Point c);
	int TestSphereTriangle(Sphere s, Point a, Point b, Point c, Point& p);

	void setGravity( glm::vec3 newGravityValue );
	glm::vec3 getGravity(void);

	// Takes a mesh in "model space" and converts it into "world space"
	void CalculateTransformedMesh(cItem_Model &originalMesh, glm::mat4 matWorld,
		cItem_Model &mesh_transformedInWorld );

	static glm::mat4 calculateWorldMatrix(cObject_Model& pCurrentObject);
private:

	// Does collision test and returns collision information
	// Returns true if collision, and will load collisionInfo struct
	bool DoSphereSphereCollisionTest(cObject_Model* pA, cObject_Model*pB,
									  sCollisionInfo &collisionInfo );
	bool DoShphereMeshCollisionTest(cObject_Model* pA, cObject_Model* pB,
									 sCollisionInfo &collisionInfo );


	glm::vec3  m_Gravity;

};

#endif
