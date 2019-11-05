// LoadModelsIntoScene.cpp

#include "cGameObject.h"
#include "cVAOManager.h"
#include "cModelLoader.h"
#include "DebugRenderer/iDebugRenderer.h"

// HACK
#include "globalStuff.h"		// for the debug sphere

cGameObject* g_pDebugSphere;

// HACK:
cGameObject* pShpere;
cMesh lowrescubeMesh;
cGameObject* pHiResCube;
cMesh singleTriangleMesh;

cMesh spaceStationMesh;


#include <iostream>
#include <vector>

void CalcAABBsForMeshModel(cMesh& theMesh);


void LoadModelsIntoScene(cVAOManager* pTheVAOManager, cModelLoader* pTheModelLoader, 
						 GLuint shaderProgID, iDebugRenderer* pDebugRenderer, 
						 std::vector<cGameObject*> &vec_pGameObjects)
{

	cMesh bunnyMesh;		// This is stack based
//	if ( ! pTheModelLoader->LoadPlyModel("assets/models/Sky_Pirate_Combined_xyz.ply", bunnyMesh) )
//	if ( ! pTheModelLoader->LoadPlyModel("assets/models/bun_zipper_res4_XYZ_N.ply", bunnyMesh) )
//	if (!pTheModelLoader->LoadPlyModel("assets/models/bun_zipper_XYZ_n.ply", bunnyMesh))
	if (!pTheModelLoader->LoadPlyModel("assets/models/bun_zipper_res2_XYZ_n_UV.ply", bunnyMesh))
	{
		std::cout << "Didn't find the file" << std::endl;
	}

	cMesh largeBunnyMesh;
	pTheModelLoader->LoadPlyModel("assets/models/Large_Physics_Bunny_XYZ_N_UV.ply", largeBunnyMesh);

	//cMesh pirateMesh;
	//pTheModelLoader->LoadPlyModel("assets/models/Sky_Pirate_Combined_xyz_n.ply", pirateMesh);

	cMesh terrainMesh;
	if (!pTheModelLoader->LoadPlyModel("assets/models/Terrain_XYZ_n_uv.ply", terrainMesh))
	{
		std::cout << "Didn't load terrain" << std::endl;
	}
	//	pTheModelLoader->LoadPlyModel("assets/models/BigFlatTerrain_XYZ_n.ply", terrainMesh);

//	cMesh cubeMesh;
//	pTheModelLoader->LoadPlyModel("assets/models/Cube_1_Unit_from_origin_XYZ_n.ply", cubeMesh);

	cMesh sphereMesh;
	pTheModelLoader->LoadPlyModel("assets/models/Sphere_Radius_1_XYZ_n_uv.ply", sphereMesh);

	// Example for mesh vs model you are testing in the physics engine
//	cMesh hirescubeMesh;
//	pTheModelLoader->LoadPlyModel("assets/models/cube_Low_Hi_xyz_n.ply", hirescubeMesh);
//	//cMesh lowrescubeMesh;
//	pTheModelLoader->LoadPlyModel("assets/models/cube_Low_Res_xyz_n.ply", lowrescubeMesh);

	//cMesh spaceStationMesh;
//	pTheModelLoader->LoadPlyModel("assets/models/Entire_Babbage_Space_Station_xyz_n.ply", spaceStationMesh);

	//cMesh singleTriangleMesh;
//	pTheModelLoader->LoadPlyModel("assets/models/Single_Triangle_XYZ_n_(XZ_Plane_facing_+ve_Y).ply", singleTriangleMesh);


	// Create the AABBs for the space station
	CalcAABBsForMeshModel( spaceStationMesh );


	// Note, the "filename" here is really the "model name" 
	//  that we can look up later (i.e. it doesn't have to be the file name)
	sModelDrawInfo drawInfo;
	pTheVAOManager->LoadModelIntoVAO("bunny",
									 bunnyMesh,
									 drawInfo,
									 shaderProgID);

	//sModelDrawInfo drawInfoPirate;
	//pTheVAOManager->LoadModelIntoVAO("pirate",
	//								 pirateMesh,
	//								 drawInfoPirate,
	//								 shaderProgID);

	sModelDrawInfo drawInfoTerrain;
	pTheVAOManager->LoadModelIntoVAO("terrain",
									 terrainMesh,
									 drawInfoTerrain,
									 shaderProgID);

	//sModelDrawInfo cubeMeshInfo;
	//pTheVAOManager->LoadModelIntoVAO("cube",
	//								 cubeMesh,			// Cube mesh info
	//								 cubeMeshInfo,
	//								 shaderProgID);

	sModelDrawInfo sphereMeshInfo;
	pTheVAOManager->LoadModelIntoVAO("sphere",
									 sphereMesh,		// Sphere mesh info
									 sphereMeshInfo,
									 shaderProgID);

	sModelDrawInfo largeBunnyDrawInfo;
	pTheVAOManager->LoadModelIntoVAO("large_bunny",
									 largeBunnyMesh,		// Sphere mesh info
									 largeBunnyDrawInfo,
									 shaderProgID);


	//sModelDrawInfo hirescubeDrawInfo;
	//pTheVAOManager->LoadModelIntoVAO("hi_res_cube",
	//								 hirescubeMesh,			// The one we draw
	//								 hirescubeDrawInfo,
	//								 shaderProgID);
	//sModelDrawInfo lowrescubeDrawInfo;
	//pTheVAOManager->LoadModelIntoVAO("low_res_cube",
	//								 lowrescubeMesh,		// the one we test in the physics engine
	//								 lowrescubeDrawInfo,
	//								 shaderProgID);

	//sModelDrawInfo spaceStationDrawInfo;
	//pTheVAOManager->LoadModelIntoVAO("space_station",
	//								 spaceStationMesh,		// the one we test in the physics engine
	//								 spaceStationDrawInfo,
	//								 shaderProgID);

	//sModelDrawInfo singleTriangleDrawInfo;
	//pTheVAOManager->LoadModelIntoVAO("single_triangle",
	//								 singleTriangleMesh,		// the one we test in the physics engine
	//								 singleTriangleDrawInfo,
	//								 shaderProgID);


	// At this point, the model is loaded into the GPU


	//// Load up my "scene" 
	//std::vector<cGameObject*> vec_pGameObjects;

	cGameObject* pPirate = new cGameObject();
	pPirate->meshName = "pirate";
	pPirate->friendlyName = "PirateShip";	// Friendly name
	pPirate->positionXYZ = glm::vec3(-30.0f, 20.0f, 10.0f);
	pPirate->rotationXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
	pPirate->scale = 0.75f;
	pPirate->objectColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	pPirate->inverseMass = 0.0f;
	pPirate->HACK_AngleAroundYAxis = 0.0f;
	pPirate->HACK_speed = 0.0f;
	// Add a debug renderer to this object
	pPirate->setDebugRenderer(pDebugRenderer);

	//
	cGameObject* pBunny = new cGameObject();
	pBunny->meshName = "bunny";
	pBunny->friendlyName = "Bugs";	// Famous bunny
	pBunny->positionXYZ = glm::vec3(50.0f, 20.0f, -2.0f);		// -4 on z
	pBunny->rotationXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
	pBunny->scale = 250.0f;
	pBunny->objectColourRGBA = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	pBunny->inverseMass = 0.0f;
	//
		//cGameObject bunny2;
		//bunny2.meshName = "bunny";
		//bunny2.positionXYZ = glm::vec3(0.0f,0.0f,0.0f);
		//bunny2.rotationXYZ = glm::vec3(0.0f,1.0f,0.0f);
		//bunny2.scale = 3.5f;
		//bunny2.objectColourRGBA = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);
	//
		//cGameObject terrain;
		//terrain.meshName = "terrain";
		//terrain.positionXYZ = glm::vec3(0.0f,-10.0f,0.0f);
		//terrain.rotationXYZ = glm::vec3(0.0f,0.0f,0.0f);
		//terrain.scale = 0.5f;
		//terrain.objectColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

		// Sphere and cube
	pShpere = new cGameObject();

	//cGameObject A; 
	//cGameObject B;
	//A = B;


	pShpere->meshName = "sphere";
	pShpere->friendlyName = "Sphere#1";	// We use to search 
	pShpere->positionXYZ = glm::vec3(0.0f, 30.0, 0.0f);
	pShpere->rotationXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
	pShpere->scale = 1.0f;
	pShpere->objectColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	// Set the sphere's initial velocity, etc.
	pShpere->velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	pShpere->accel = glm::vec3(0.0f, 0.0f, 0.0f);
	pShpere->physicsShapeType = SPHERE;
	pShpere->SPHERE_radius = 1.0f;
	pShpere->inverseMass = 1.0f;
	//	pShpere->inverseMass = 0.0f;			// Sphere won't move

			// Sphere and cube
	cGameObject* pShpere2 = new cGameObject();
	pShpere2->meshName = "sphere";
	pShpere2->friendlyName = "Sphere#2";
	//	pShpere2->positionXYZ = glm::vec3(25.0f, 20.0f, 1.0f);
	pShpere2->rotationXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
	pShpere2->scale = 1.0f;
	pShpere2->objectColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	// Set the sphere's initial velocity, etc.
	//	pShpere2->velocity = glm::vec3(6.0f, -15.0f, 0.0f);
	pShpere2->accel = glm::vec3(0.0f, 0.0f, 0.0f);
	pShpere2->physicsShapeType = SPHERE;
	pShpere2->inverseMass = 0.0f;
	//	pShpere->inverseMass = 0.0f;			// Sphere won't move


	cGameObject* pCube = new cGameObject();			// HEAP
	pCube->meshName = "cube";
	pCube->positionXYZ = glm::vec3(0.0f, -1.0f, 0.0f);
	pCube->rotationXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
	pCube->scale = 1.0f;
	//pCube->objectColourRGBA = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	pCube->debugColour = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	pCube->isWireframe = true;
	// Set the sphere's initial velocity, etc.
	//sphere.velocity = glm::vec3(0.0f,0.0f,0.0f);
	//sphere.accel = glm::vec3(0.0f,0.0f,0.0f);
	pCube->inverseMass = 0.0f;	// Ignored during update


	cGameObject* pTerrain = new cGameObject();			// HEAP
	pTerrain->meshName = "terrain";
	pTerrain->friendlyName = "TheGround";
	pTerrain->positionXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
	pTerrain->rotationXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
	pTerrain->scale = 1.0f;
	pTerrain->objectColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	pTerrain->physicsShapeType = MESH;
	//pTerrain->debugColour = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	//pTerrain->isWireframe = true;
	pTerrain->inverseMass = 0.0f;	// Ignored during update
//	pTerrain->isVisible = false;

	cGameObject* pLargeBunny = new cGameObject();			// HEAP
	pLargeBunny->meshName = "large_bunny";
	pLargeBunny->friendlyName = "largeBunny";
	pLargeBunny->positionXYZ = glm::vec3(30.0f, 0.0f, 0.0f);
	pLargeBunny->rotationXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
	pLargeBunny->scale = 1.0f;	//***** SCALE = 1.0f *****/
	pLargeBunny->objectColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	pLargeBunny->physicsShapeType = MESH;
	//	pTerrain->debugColour = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	//	pTerrain->isWireframe = true;
	pLargeBunny->inverseMass = 0.0f;	// Ignored during update


	// Same orientation and position for BOTH the high resolution AND low resultion objects
	glm::vec3 cubesPosition = glm::vec3(0.0f, -50.0f, 0.0f);
	glm::vec3 cubesRotation = glm::vec3(glm::radians(15.0f), 0.0f, glm::radians(35.0f));


	pHiResCube = new cGameObject();			// HEAP
	pHiResCube->meshName = "hi_res_cube";
	pHiResCube->friendlyName = "hi_cube";
	pHiResCube->positionXYZ = cubesPosition;
	pHiResCube->rotationXYZ = cubesRotation;
	pHiResCube->scale = 1.0f;	//***** SCALE = 1.0f *****/
	pHiResCube->objectColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	pHiResCube->physicsShapeType = MESH;
	//pHiResCube->isWireframe = true;
	//pHiResCube->debugColour = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);		// Yellow
	pHiResCube->inverseMass = 0.0f;	// Ignored during update

	cGameObject* pLowResCube = new cGameObject();			// HEAP
	pLowResCube->meshName = "low_res_cube";
	pLowResCube->friendlyName = "low_cube";
	pLowResCube->positionXYZ = cubesPosition;
	pLowResCube->rotationXYZ = cubesRotation;
	pLowResCube->scale = 1.0f;	//***** SCALE = 1.0f *****/
	pLowResCube->objectColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	pLowResCube->physicsShapeType = MESH;
	pLowResCube->isWireframe = true;
	pLowResCube->debugColour = glm::vec4(1.0f, 1.0f, 0.5f, 1.0f);		// Yellow
	pLowResCube->inverseMass = 0.0f;	// Ignored during update

	cGameObject* pSpaceStation = new cGameObject();			// HEAP
	pSpaceStation->meshName = "space_station";
	pSpaceStation->friendlyName = "space station";
	pSpaceStation->positionXYZ = glm::vec3(100.0f, 0.0f, 0.0f);
	pSpaceStation->rotationXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
	pSpaceStation->scale = 1.0f;	//***** SCALE = 1.0f *****/
	pSpaceStation->objectColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	pSpaceStation->physicsShapeType = MESH;
	pSpaceStation->isWireframe = true;
	pSpaceStation->debugColour = glm::vec4(1.0f, 1.0f, 0.5f, 1.0f);		// Yellow
	pSpaceStation->inverseMass = 0.0f;	// Ignored during update

	cGameObject* pSingleTriangle = new cGameObject();			// HEAP
	pSingleTriangle->meshName = "single_triangle";
	pSingleTriangle->friendlyName = "single triangle";
	pSingleTriangle->positionXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
	pSingleTriangle->rotationXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
	pSingleTriangle->scale = 1.0f;	//***** SCALE = 1.0f *****/
	pSingleTriangle->objectColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	pSingleTriangle->physicsShapeType = MESH;
	//pSingleTriangle->isWireframe = true;
	//pSingleTriangle->debugColour = glm::vec4(1.0f, 1.0f, 0.5f, 1.0f);		// Yellow
	pSingleTriangle->inverseMass = 0.0f;	// Ignored during update


	vec_pGameObjects.push_back(pShpere);
	vec_pGameObjects.push_back(pShpere2);
	vec_pGameObjects.push_back(pCube);
	vec_pGameObjects.push_back(pTerrain);
	vec_pGameObjects.push_back(pPirate);
	vec_pGameObjects.push_back(pBunny);
	vec_pGameObjects.push_back(pLargeBunny);
	vec_pGameObjects.push_back(pSpaceStation);
	vec_pGameObjects.push_back(pSingleTriangle);

	vec_pGameObjects.push_back(pHiResCube);
	vec_pGameObjects.push_back(pLowResCube);




	//::g_map_GameObjectsByFriendlyName[pShpere2->friendlyName] = pShpere;
	//::g_map_GameObjectsByFriendlyName[pTerrain->friendlyName] = pTerrain;
	//::g_map_GameObjectsByFriendlyName[pPirate->friendlyName] = pPirate;
	//::g_map_GameObjectsByFriendlyName[pBunny->friendlyName] = pBunny;


	// Will be moved placed around the scene
	::g_pDebugSphere = new cGameObject();
	::g_pDebugSphere->meshName = "sphere";
	::g_pDebugSphere->friendlyName = "debug_sphere";
	::g_pDebugSphere->positionXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
	::g_pDebugSphere->rotationXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
	::g_pDebugSphere->scale = 0.1f;
	//	::g_pDebugSphere->objectColourRGBA = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	::g_pDebugSphere->debugColour = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	::g_pDebugSphere->isWireframe = true;
	::g_pDebugSphere->inverseMass = 0.0f;			// Sphere won't move

	return;
}


