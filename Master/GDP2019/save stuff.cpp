#if 0
// this was all of the old loading stuff
// Now comes from the xml file
{
cObject_Model* pPirate = new cObject_Model("model", "PirateShip", "Sky_Pirate_Combined_xyz_n", NULL);
pPirate->meshName = "pirate";
pPirate->friendlyName = "PirateShip";	// Friendly name
pPirate->positionXYZ = glm::vec3(-30.0f, 20.0f, 10.0f);
pPirate->rotationXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
pPirate->scale = 0.75f;
pPirate->objectColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
pPirate->inverseMass = 0.0f;
pPirate->HACK_AngleAroundYAxis = 0.0f;
pPirate->isVisible = true;
pPirate->HACK_speed = 0.0f;
objectManager.SaveObject(pPirate, objectsLib.GetNode());
	}
// Add a debug renderer to this object
//	pPirate->setDebugRenderer( pDebugRenderer );

//
{
	cObject_Model* pBunny = new cObject_Model("model", "Bugs", "bun_zipper_XYZ_n", NULL);
	pBunny->meshName = "bunny";
	pBunny->friendlyName = "Bugs";	// Famous bunny
	pBunny->positionXYZ = glm::vec3(50.0f, 20.0f, -2.0f);		// -4 on z
	pBunny->rotationXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
	pBunny->scale = 250.0f;
	pBunny->objectColourRGBA = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	pBunny->inverseMass = 0.0f;
	pBunny->isVisible = true;
	objectManager.SaveObject(pBunny, objectsLib.GetNode());
}

// Sphere and cube
{
	cObject_Model* pShpere = new cObject_Model("model", "Sphere#1", "Sphere_Radius_1_XYZ_n", NULL);
	pShpere->meshName = "sphere";
	pShpere->friendlyName = "Sphere#1";	// We use to search 
	pShpere->positionXYZ = glm::vec3(0.0f, 30.0, 0.0f);
	pShpere->rotationXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
	pShpere->scale = 1.0f;
	pShpere->objectColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	// Set the sphere's initial velocity, etc.
	pShpere->velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	pShpere->accel = glm::vec3(0.0f, 0.0f, 0.0f);
	pShpere->physicsShapeType = cObject_Model::eShapeTypes::SPHERE;
	pShpere->SPHERE_radius = 1.0f;
	pShpere->isVisible = true;
	pShpere->inverseMass = 1.0f;
	//	pShpere->inverseMass = 0.0f;			// Sphere won't move
	objectManager.SaveObject(pShpere, objectsLib.GetNode());
}
{
	// Sphere and cube
	cObject_Model* pShpere2 = new cObject_Model("model", "Sphere#2", "Sphere_Radius_1_XYZ_n", NULL);
	pShpere2->meshName = "sphere";
	pShpere2->friendlyName = "Sphere#2";
	//	pShpere2->positionXYZ = glm::vec3(25.0f, 20.0f, 1.0f);
	pShpere2->rotationXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
	pShpere2->scale = 1.0f;
	pShpere2->objectColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	// Set the sphere's initial velocity, etc.
//	pShpere2->velocity = glm::vec3(6.0f, -15.0f, 0.0f);
	pShpere2->accel = glm::vec3(0.0f, 0.0f, 0.0f);
	pShpere2->physicsShapeType = cObject_Model::SPHERE;
	pShpere2->inverseMass = 0.0f;
	pShpere2->isVisible = true;
	//	pShpere->inverseMass = 0.0f;			// Sphere won't move
	objectManager.SaveObject(pShpere2, objectsLib.GetNode());
}
{
	cObject_Model* pCube = new cObject_Model("model", "cube", "Cube_1_Unit_from_origin_XYZ_n", NULL);			// HEAP
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
	pCube->isVisible = false;
	pCube->inverseMass = 0.0f;	// Ignored during update
	objectManager.SaveObject(pCube, objectsLib.GetNode());
}
{
	cObject_Model* pTerrain = new cObject_Model("model", "TheGround", "Terrain_XYZ_n", NULL);			// HEAP
	pTerrain->meshName = "terrain";
	pTerrain->friendlyName = "TheGround";
	pTerrain->positionXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
	pTerrain->rotationXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
	pTerrain->scale = 1.0f;
	pTerrain->objectColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	pTerrain->physicsShapeType = cObject_Model::MESH;
	//	pTerrain->debugColour = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	//	pTerrain->isWireframe = true;
	pTerrain->inverseMass = 0.0f;	// Ignored during update
	pTerrain->isVisible = true;
	objectManager.SaveObject(pTerrain, objectsLib.GetNode());
}
{
	cObject_Model* pLargeBunny = new cObject_Model("model", "largeBunny", "Large_Physics_Bunny_XYZ_n", NULL);			// HEAP
	pLargeBunny->meshName = "large_bunny";
	pLargeBunny->friendlyName = "largeBunny";
	pLargeBunny->positionXYZ = glm::vec3(30.0f, 0.0f, 0.0f);
	pLargeBunny->rotationXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
	pLargeBunny->scale = 1.0f;	//***** SCALE = 1.0f *****/
	pLargeBunny->objectColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	pLargeBunny->physicsShapeType = cObject_Model::MESH;
	//	pTerrain->debugColour = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	//	pTerrain->isWireframe = true;
	pLargeBunny->inverseMass = 0.0f;	// Ignored during update
	pLargeBunny->isVisible = true;
	objectManager.SaveObject(pLargeBunny, objectsLib.GetNode());
}
// Same orientation and position for BOTH the high resolution AND low resultion objects
glm::vec3 cubesPosition = glm::vec3(0.0f, -50.0f, 0.0f);
glm::vec3 cubesRotation = glm::vec3(glm::radians(15.0f), 0.0f, glm::radians(35.0f));

{
	cObject_Model* pHiResCube = new cObject_Model("model", "hi_cube", "cube_Low_Hi_xyz_n", NULL);			// HEAP
	pHiResCube->meshName = "hi_res_cube";
	pHiResCube->friendlyName = "hi_cube";
	pHiResCube->positionXYZ = cubesPosition;
	pHiResCube->rotationXYZ = cubesRotation;
	pHiResCube->scale = 1.0f;	//***** SCALE = 1.0f *****/
	pHiResCube->objectColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	pHiResCube->physicsShapeType = cObject_Model::MESH;
	//pHiResCube->isWireframe = true;
	//pHiResCube->debugColour = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);		// Yellow
	pHiResCube->inverseMass = 0.0f;	// Ignored during update
	pHiResCube->isVisible = false;
	objectManager.SaveObject(pHiResCube, objectsLib.GetNode());
}
{
	cObject_Model* pLowResCube = new cObject_Model("model", "low_cube", "cube_Low_Res_xyz_n", NULL);			// HEAP
	pLowResCube->meshName = "low_res_cube";
	pLowResCube->friendlyName = "low_cube";
	pLowResCube->positionXYZ = cubesPosition;
	pLowResCube->rotationXYZ = cubesRotation;
	pLowResCube->scale = 1.0f;	//***** SCALE = 1.0f *****/
	pLowResCube->objectColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	pLowResCube->physicsShapeType = cObject_Model::MESH;
	pLowResCube->isWireframe = true;
	pLowResCube->debugColour = glm::vec4(1.0f, 1.0f, 0.5f, 1.0f);		// Yellow
	pLowResCube->inverseMass = 0.0f;	// Ignored during update
	pLowResCube->isVisible = false;
	objectManager.SaveObject(pLowResCube, objectsLib.GetNode());
}
{
	cObject_Model* pSpaceStation = new cObject_Model("model", "space station", "Entire_Babbage_Space_Station_xyz_n", NULL);			// HEAP
	pSpaceStation->meshName = "space_station";
	pSpaceStation->friendlyName = "space station";
	pSpaceStation->positionXYZ = glm::vec3(100.0f, 0.0f, 0.0f);
	pSpaceStation->rotationXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
	pSpaceStation->scale = 1.0f;	//***** SCALE = 1.0f *****/
	pSpaceStation->objectColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	//pSpaceStation->physicsShapeType = MESH;
	//pSpaceStation->isWireframe = true;
	pSpaceStation->debugColour = glm::vec4(1.0f, 1.0f, 0.5f, 1.0f);		// Yellow
	pSpaceStation->inverseMass = 0.0f;	// Ignored during update
	pSpaceStation->isVisible = false;
	objectManager.SaveObject(pSpaceStation, objectsLib.GetNode());
}

{
	cObject_Model* pSingleTriangle = new cObject_Model("model", "single triangle", "SingleTriangle", NULL);			// HEAP
	pSingleTriangle->meshName = "single_triangle";
	pSingleTriangle->friendlyName = "single triangle";
	pSingleTriangle->positionXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
	pSingleTriangle->rotationXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
	pSingleTriangle->scale = 1.0f;	//***** SCALE = 1.0f *****/
	pSingleTriangle->objectColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	pSingleTriangle->physicsShapeType = cObject_Model::MESH;
	//pSingleTriangle->isWireframe = true;
	//pSingleTriangle->debugColour = glm::vec4(1.0f, 1.0f, 0.5f, 1.0f);		// Yellow
	pSingleTriangle->inverseMass = 0.0f;	// Ignored during update
	pSingleTriangle->isVisible = true;
	objectManager.SaveObject(pSingleTriangle, objectsLib.GetNode());
}
#endif
