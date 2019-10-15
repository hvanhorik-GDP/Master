#include "test_Physics.h"
#include "GLCommon.h"

#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <sstream>
#include <climits>
#include <cstdlib>		// c libs
#include <cstdio>		// c libs
#include <iostream>		// C++ IO standard stuff
#include <map>			// Map aka "dictonary" 

#include "Models/cPlyLoader.h"
#include "AssetItems/cItem_Program.h"
#include "AssetItems/cItem_Model.h"
#include "AssetManager/cAssetManager_Models.h"
#include "AssetManager/cAssetManager_Programs.h"
#include "AssetManager/cAssetManager.h"

#include "VAOManager/cVAOManager.h"
#include "ObjectManager/cObjectManager.h"

#include "Physics/PhysicsStuff.h"
#include "Physics/cPhysics_Henky.h"
#include "LowPassFilter/cLowPassFilter.h"
#include "DebugRenderer/cDebugRenderer.h"
#include "LightManager/cLightHelper.h"

// Local stuff pulled out of main by Henry
#include "Common/pFindObjectByFriendlyName.h"
#include "Common/globalStuff.h"
#include "Physics_Callback.h"

// Crap for now
#include "GDP2019/HandleDebugBallPhysics.h"
#include "GDP2019/HandleDebugLights.h"
#include "GDP2019/LightDebugSheres.h"

int test_Physics(gamelibrary::GameLibrary& gameLib)
{
	// set mouse and keyboard callback
	glfwSetKeyCallback(window, Physics_key_callback);
	// Set the mouse button callback
	glfwSetMouseButtonCallback(window, Physics_mouse_button_callback);

	cDebugRenderer* pDebugRenderer = new cDebugRenderer();
	pDebugRenderer->initialize();

	cPlyLoader loader;
	cAssetManager assetManager;
	iAssetManager::iItems_map* items = assetManager.GetItems("models");

	gamelibrary::Objects objectsLib = gameLib.GetObjects();

	// A handy list of everthing we want to load.
	std::map<std::string, cItem_Model*> mapLoaded;
	mapLoaded["Cube_1_Unit_from_origin_XYZ_n"] = NULL;
	mapLoaded["cube_Hi_Res_xyz_n"] = NULL;
	mapLoaded["cube_Low_Res_xyz_n"] = NULL;
	mapLoaded["pyramid"] = NULL;
	mapLoaded["pyramid_3"] = NULL;
	mapLoaded["Sphere_Radius_1_XYZ_n"] = NULL;
	mapLoaded["12953_ChocolateRabbit_v1"] = NULL;
	

	// Load up all of the mesh we need for this run
	for (auto it : mapLoaded)
	{
		// We have already loaded the mesh information
		// We now need to load the actual mesh data
		auto map = (*items)[it.first];
		assert(map);
		auto mesh = dynamic_cast<cItem_Model*>(map);
		assert(mesh);
		if (loader.LoadPlyModel(mesh->GetAssetName(), *mesh))
			mapLoaded[it.first] = mesh;
	}

	// Get all of our model objects (Now loaded from the xml file)
	cObjectManager objectManager;

	iAssetManager::iItems_map* programItems = assetManager.GetItems("programs");

	auto prg = (*programItems)["main"];
	cItem_Program* program = dynamic_cast<cItem_Program*>(prg);
	GLuint shaderProgID = program->GetID();				// Get the ID of the program	
	cVAOManager* pTheVAOManager = new cVAOManager();

	// Load all of the models into the GPU
	for ( auto model : mapLoaded)
	{
		sModelDrawInfo drawInfo;
		pTheVAOManager->LoadModelIntoVAO(*model.second,
			drawInfo,
			shaderProgID);
	}


	iObjectManager::iObject_map& mapObjects = *objectManager.GetObjects("model");

	glEnable(GL_DEPTH);			// Write to the depth buffer
	glEnable(GL_DEPTH_TEST);	// Test with buffer when drawing

	cPhysics_Henky* pPhsyics = new cPhysics_Henky();
	pPhsyics->SetDebugRenderer(pDebugRenderer);
	cLowPassFilter avgDeltaTimeThingy;

	cObject_Model* pDropSphere = pFindObjectByFriendlyName("Drop_Sphere");

	// Get the initial time
	double lastTime = glfwGetTime();

	// Main loop till the window should close
	while (!glfwWindowShouldClose(window))
	{
		// Get the initial time
		double currentTime = glfwGetTime();
		double deltaTime = currentTime - lastTime;
		lastTime = currentTime;
		const double SOME_HUGE_TIME = 0.1;	// 100 ms;
		if (deltaTime > SOME_HUGE_TIME)
			deltaTime = SOME_HUGE_TIME;
		avgDeltaTimeThingy.addValue(deltaTime);

		glUseProgram(shaderProgID);

		// Set up view window
		float ratio;
		int width, height;
		glm::mat4 projection, view;

		::glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;

		// Projection matrix
		projection = glm::perspective(1.0f,		// FOV
							 ratio,			// Aspect ratio
							 0.1f,			// Near clipping plane
							 10000.0f);		// Far clipping plane

		// View matrix
		view = glm::mat4(1.0f);
		view = glm::lookAt(cameraEye,
						cameraTarget,
						upVector);

		glViewport(0, 0, width, height);

		// Clear both the colour buffer (what we see) and the 
		//  depth (or z) buffer.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		::HandleDebugLights(shaderProgID);
		//::HandleDebugPirate(pDebugRenderer);

		GLint matView_UL = glGetUniformLocation(shaderProgID, "matView");
		GLint matProj_UL = glGetUniformLocation(shaderProgID, "matProj");

		glUniformMatrix4fv(matView_UL, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(matProj_UL, 1, GL_FALSE, glm::value_ptr(projection));

		// Loop to draw everything in the scene
		for (auto object: mapObjects)
		{
			glm::mat4 matModel = glm::mat4(1.0f);

			cObject_Model* pCurrentObject = dynamic_cast<cObject_Model*>(object.second);
			assert(pCurrentObject);

			pTheVAOManager->DrawObject( matModel, pCurrentObject,
					   shaderProgID);

		} // for (auto object: mapObjects)

		// Update the physics
		double averageDeltaTime = avgDeltaTimeThingy.getAverage();
		pPhsyics->IntegrationStep(mapObjects, (float)averageDeltaTime);

		::HandleDebugBallPhysics(shaderProgID, pPhsyics, pTheVAOManager, pDebugRenderer,&mapLoaded);

		// A more general 
//		pPhsyics->TestForCollisions(mapObjects);
		::LightDebugSheres(shaderProgID, pTheVAOManager);

		pDebugRenderer->RenderDebugObjects( view, projection, 0.01f );

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();

	return (EXIT_SUCCESS);
}
//
//	{
//	cObject_Model* pShpere = new cObject_Model("model", "Sphere#1", "Sphere_Radius_1_XYZ_n", NULL);
//	pShpere->friendlyName = "Sphere#1";	// We use to search 
//	pShpere->positionXYZ = glm::vec3(15.0f, 30.0, 15.0f);
//	pShpere->rotationXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
//	pShpere->scale = 1.0f;
//	pShpere->objectColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
//	// Set the sphere's initial velocity, etc.
//	pShpere->velocity = glm::vec3(0.0f, 0.0f, 0.0f);
//	pShpere->accel = glm::vec3(0.0f, 0.0f, 0.0f);
//	pShpere->physicsShapeType = cObject_Model::eShapeTypes::SPHERE;
//	pShpere->SPHERE_radius = 1.0f;
//	pShpere->isVisible = true;
//	pShpere->inverseMass = 1.0f;
//	pShpere->inverseMass = 0.0f;			// Sphere won't move
//	objectManager.SaveObject(pShpere, objectsLib.GetNode());
//	}
//	{
//		cObject_Model* pShpere = new cObject_Model("model", "Sphere", "Sphere_Radius_1_XYZ_n", NULL);
//		pShpere->friendlyName = "Sphere";	// We use to search 
//		pShpere->positionXYZ = glm::vec3(0.0f, 30.0, 0.0f);
//		pShpere->rotationXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
//		pShpere->scale = 1.0f;
//		pShpere->objectColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
//		// Set the sphere's initial velocity, etc.
//		pShpere->velocity = glm::vec3(0.0f, 0.0f, 0.0f);
//		pShpere->accel = glm::vec3(0.0f, 0.0f, 0.0f);
//		pShpere->physicsShapeType = cObject_Model::eShapeTypes::SPHERE;
//		pShpere->SPHERE_radius = 1.0f;
//		pShpere->isVisible = true;
//		pShpere->inverseMass = 1.0f;
//		//	pShpere->inverseMass = 0.0f;			// Sphere won't move
//		objectManager.SaveObject(pShpere, objectsLib.GetNode());
//	} {
//		cObject_Model* pPyramid = new cObject_Model("model", "pyramid_1", "pyramid", NULL);
//		pPyramid->friendlyName = "pyramid_1";	// We use to search 
//		pPyramid->positionXYZ = glm::vec3(-20.0f, 20.0, 0.0f);
//		pPyramid->rotationXYZ = glm::vec3(0.0f, -50.0f, 0.0f);// glm::vec3(0.0f, 0.0f, 0.0f);
//		pPyramid->scale = 0.5f;
//		pPyramid->objectColourRGBA = glm::vec4(0.0f, 0.5f, 0.5f, 1.0f);
//		// Set the sphere's initial velocity, etc.
//		pPyramid->velocity = glm::vec3(0.0f, 0.0f, 0.0f);
//		pPyramid->accel = glm::vec3(0.0f, 0.0f, 0.0f);
//		pPyramid->physicsShapeType = cObject_Model::eShapeTypes::MESH;
//		pPyramid->SPHERE_radius = 0.0f;
//		pPyramid->isVisible = true;
//		pPyramid->inverseMass = 0.0f;
//		objectManager.SaveObject(pPyramid, objectsLib.GetNode());
//	} {
//		cObject_Model* pPyramid = new cObject_Model("model", "pyramid_3", "pyramid_3", NULL);
//		pPyramid->friendlyName = "pyramid_3";	// We use to search 
//		pPyramid->positionXYZ = glm::vec3(0.0f, 20.0, 20.0f);
//		pPyramid->rotationXYZ = glm::vec3(50.0f, -50.0f, 0.0f); //glm::vec3(0.0f, 0.0f, 0.0f);
//		pPyramid->scale = 1.0f;
//		pPyramid->objectColourRGBA = glm::vec4(.05f, 0.5f, 1.0f, 1.0f);
//		// Set the sphere's initial velocity, etc.
//		pPyramid->velocity = glm::vec3(0.0f, 0.0f, 0.0f);
//		pPyramid->accel = glm::vec3(0.0f, 0.0f, 0.0f);
//		pPyramid->physicsShapeType = cObject_Model::eShapeTypes::MESH;
//		pPyramid->SPHERE_radius = 0.0f;
//		pPyramid->isVisible = true;
//		pPyramid->inverseMass = 0.0f;
//		objectManager.SaveObject(pPyramid, objectsLib.GetNode());
//	} {
//		cObject_Model* pPyramid = new cObject_Model("model", "chocolatebunny", "12953_ChocolateRabbit_v1", NULL);
//		pPyramid->friendlyName = "chocolatebunny";	// We use to search 
//		pPyramid->positionXYZ = glm::vec3(20.0f, 20.0, 20.0f);
//		pPyramid->rotationXYZ = glm::vec3(0.0f, -50.0f, 0.0f);  // glm::vec3(0.0f, 0.0f, 0.0f);
//		pPyramid->scale = 2.0f;
//		pPyramid->objectColourRGBA = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
//		// Set the sphere's initial velocity, etc.
//		pPyramid->velocity = glm::vec3(0.0f, 0.0f, 0.0f);
//		pPyramid->accel = glm::vec3(0.0f, 0.0f, 0.0f);
//		pPyramid->physicsShapeType = cObject_Model::eShapeTypes::MESH;
//		pPyramid->SPHERE_radius = 0.0f;
//		pPyramid->isVisible = false;
//		pPyramid->inverseMass = 0.0f;
//		objectManager.SaveObject(pPyramid, objectsLib.GetNode());
//	}
//
//
//	// Same orientation and position for BOTH the high resolution AND low resultion objects
////	glm::vec3 cubesPosition = glm::vec3(0.0f, -50.0f, 0.0f);
////	glm::vec3 cubesRotation = glm::vec3(glm::radians(15.0f), 0.0f, glm::radians(35.0f));
//
//	glm::vec3 cubesPosition = glm::vec3(0.0f, 0.0f, 0.0f);
//	glm::vec3 cubesRotation = glm::vec3(0.0f, 0.0f, 0.0f);
//
//	{
//		cObject_Model* pHiResCube = new cObject_Model("model", "hi_cube", "cube_Hi_Res_xyz_n", NULL);			// HEAP
//		pHiResCube->friendlyName = "hi_cube";
//		pHiResCube->positionXYZ = cubesPosition;
//		pHiResCube->rotationXYZ = cubesRotation;
//		pHiResCube->scale = 1.0f;	//***** SCALE = 1.0f *****/
//		pHiResCube->objectColourRGBA = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
//		pHiResCube->physicsShapeType = cObject_Model::MESH;
//		pHiResCube->isWireframe = false;
//		//pHiResCube->debugColour = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);		// Yellow
//		pHiResCube->inverseMass = 0.0f;	// Ignored during update
//		pHiResCube->isVisible = true;
//		objectManager.SaveObject(pHiResCube, objectsLib.GetNode());
//	}
//	{
//		cObject_Model* pLowResCube = new cObject_Model("model", "low_cube", "cube_Low_Res_xyz_n", NULL);			// HEAP
//		pLowResCube->friendlyName = "low_cube";
//		pLowResCube->positionXYZ = cubesPosition;
//		pLowResCube->rotationXYZ = cubesRotation;
//		pLowResCube->scale = 1.0f;	//***** SCALE = 1.0f *****/
//		pLowResCube->objectColourRGBA = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
//		pLowResCube->physicsShapeType = cObject_Model::MESH;
//		pLowResCube->isWireframe = false;
//		pLowResCube->debugColour = glm::vec4(1.0f, 1.0f, 0.5f, 1.0f);		// Yellow
//		pLowResCube->inverseMass = 0.0f;	// Ignored during update
//		pLowResCube->isVisible = false;
//		objectManager.SaveObject(pLowResCube, objectsLib.GetNode());
//	}
