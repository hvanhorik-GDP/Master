#include "cMesh.h"
#include <glm/glm.hpp>
#include <glm/vec3.hpp>

#include <vector>
#include <map>

#include "cAABB.h"

// This will hold the AABBs for 
std::map<unsigned long long /*ID*/, cAABB*> g_mapAABBs_World;

// Take the space station model
// Figure out which triangles are in which AABB

void CalcAABBsForMeshModel(cMesh& theMesh)
{
	// For the space station, I'll make a size of -5,000 to 5,000
	const float WorldSize = 5000.0f;
	const float AABBsize = 100.0f;
	for (float x = -WorldSize; x <= WorldSize; x += AABBsize)
	{
		for (float y = -WorldSize; y <= WorldSize; y += AABBsize)
		{
			for (float z = -WorldSize; z <= WorldSize; z += AABBsize)
			{
				cAABB* pAABB = new cAABB();
				pAABB->minXYZ.x = x;
				pAABB->minXYZ.y = y;
				pAABB->minXYZ.z = z;
				pAABB->length = 100.0f;
				
				// Save the mesh to look up triangles. 
				// NOTE: you likely don't want to do this.
				// You likely want to make a new structure just for this
				// (the PlyTriangles store and indes to the vertices, which is not needed)
				
				// Store a pointer to the mesh
				pAABB->pTheMesh = &theMesh;

				unsigned long long ID = pAABB->getID();

				::g_mapAABBs_World[ID] = pAABB;
			}
		}
	}

	// Check which AABB this triangle is in

	for (std::vector<sPlyTriangle>::iterator itTri = theMesh.vecTriangles.begin();
		 itTri != theMesh.vecTriangles.end(); itTri++)
	{
		glm::vec3 v1;
		v1.x = theMesh.vecVertices[itTri->vert_index_1].x;
		v1.y = theMesh.vecVertices[itTri->vert_index_1].y;
		v1.z = theMesh.vecVertices[itTri->vert_index_1].z;
		glm::vec3 v2;
		v2.x = theMesh.vecVertices[itTri->vert_index_2].x;
		v2.y = theMesh.vecVertices[itTri->vert_index_2].y;
		v2.z = theMesh.vecVertices[itTri->vert_index_2].z;
		glm::vec3 v3;
		v3.x = theMesh.vecVertices[itTri->vert_index_3].x;
		v3.y = theMesh.vecVertices[itTri->vert_index_3].y;
		v3.z = theMesh.vecVertices[itTri->vert_index_3].z;

		// Is the triangle too big?? 
		// Is the length of ANY side longer than the AABB (longer than a half the AABB)

		// Slice the triangle. 


		// Get the ID of the AABB that this vertex is inside of 
		unsigned long long ID_AABB_V1 = cAABB::get_ID_of_AABB_I_Might_Be_In(v1);
		unsigned long long ID_AABB_V2 = cAABB::get_ID_of_AABB_I_Might_Be_In(v2);
		unsigned long long ID_AABB_V3 = cAABB::get_ID_of_AABB_I_Might_Be_In(v3);

		// Add this triangle to that box
		// sPlyTriangle& refTriangle = *itTri;
		// so &refTriangle returns the pointer to the triangle in the vector

		std::map<unsigned long long, cAABB* >::iterator itAABB 
			= ::g_mapAABBs_World.find(ID_AABB_V1);

		//if (itAABB == ::g_mapAABBs_World.end())
		//{
		//	bool ohNO = true;
		//}
		//::g_mapAABBs_World[ID_AABB_V1]->vecTriangles.push_back(&(*itTri) );

		//::g_mapAABBs_World[ID_AABB_V2]->vecTriangles.push_back( &(*itTri) );

		//::g_mapAABBs_World[ID_AABB_V3]->vecTriangles.push_back( &(*itTri) );
	}

//	unsigned long long ID = get_ID_of_AABB_I_Might_Be_In(glm::vec3 minXYZ, glm::vec3 testLocation)

	return;
}
