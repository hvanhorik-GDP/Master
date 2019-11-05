#include "Graphics_MidTerm_2019_test.h"
#include "gl/GLCommon.h"

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
#include <cstdlib>
#include <time.h>

#include "Models/cPlyLoader.h"
#include "AssetItems/cItem_Program.h"
#include "AssetItems/cItem_Model.h"
#include "AssetManager/cAssetManager.h"
#include "ObjectItems/cObject_World.h"

#include "VAOManager/cVAOManager.h"
#include "ObjectManager/cObjectManager.h"

#include "LowPassFilter/cLowPassFilter.h"
#include "DebugRenderer/cDebugRenderer.h"
#include "LightManager/cLightManager.h"

// Local stuff pulled out of main by Henry

#include "Graphics_MidTerm_2019_Callback.h"
#include "Graphics_MidTerm_2019_ToObject.h"

extern GLFWwindow* window;

int Graphics_MidTerm_2019_test(gamelibrary::GameLibrary& gameLib)
{
	cObjectManager manager;
	//TODO - for now only a single world
	auto object = manager.FindObjectByName("world");
	assert(object);
	cObject_World* world = dynamic_cast<cObject_World*>(object);

	glfwSetWindowSize(window, world->windowWidth, world->windowHeight);

	// set mouse and keyboard callback
	glfwSetKeyCallback(window, Graphics_MidTerm_2019_key_callback);
	// Set the mouse button callback
	glfwSetMouseButtonCallback(window, Graphics_MidTerm_2019_mouse_button_callback);

	cDebugRenderer* pDebugRenderer = new cDebugRenderer();
	pDebugRenderer->initialize();

	cPlyLoader loader;
	cAssetManager assetManager;
	iAssetManager::iItems_map* items = assetManager.GetItems("models");

	gamelibrary::Objects objectsLib = gameLib.GetObjects();

	// A handy list of everthing we want to load.
	// We don't want to load everything into the VAO
	// TODO - This should be read from the database XML file

	// auto mapLoaded = manager.GetObjects("model");

	// Load up all of the mesh we need for this run
	for (auto it : *items)
	{
		// We have already loaded the mesh information
		// We now need to load the actual mesh data
		auto mesh = dynamic_cast<cItem_Model*>(it.second);
		assert(mesh);
		if (!loader.LoadPlyModel(mesh->GetAssetName(), *mesh))
			std::cout << "Ply model load failed " << mesh->GetAssetName();
	}

	// Handy information for sizing
//	::Graphics_MidTerm_2019_CalculateBounds(objectsLib.GetNode());
//	::Graphics_MidTerm_2019_ShiftAllObjects(objectsLib.GetNode());

	// Get all of our model objects (Now loaded from the xml file)
	cObjectManager objectManager;

	iAssetManager::iItems_map* programItems = assetManager.GetItems("programs");

	auto prg = (*programItems)["main"];
	cItem_Program* program = dynamic_cast<cItem_Program*>(prg);
	GLuint shaderProgID = program->GetID();				// Get the ID of the program	
	cVAOManager* pTheVAOManager = new cVAOManager(shaderProgID);

	// Load all of the models into the GPU
	for ( auto it : *items)
	{
		sModelDrawInfo drawInfo;
		auto mesh = dynamic_cast<cItem_Model*>(it.second);
		assert(mesh);		
		pTheVAOManager->LoadModelIntoVAO(*(mesh), drawInfo);
	}

	iObjectManager::iObject_map& mapObjects = *objectManager.GetObjects("model");

	glEnable(GL_DEPTH);			// Write to the depth buffer
	glEnable(GL_DEPTH_TEST);	// Test with buffer when drawing

	cLowPassFilter avgDeltaTimeThingy;

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
							 ratio,				// Aspect ratio
							 0.1f,				// Near clipping plane
							 10000.0f);		// Far clipping plane

		// View matrix
		view = glm::mat4(1.0f);
		view = glm::lookAt(world->cameraEye,
			world->cameraTarget,
			world->upVector);


		glViewport(0, 0, width, height);

		// Clear both the colour buffer (what we see) and the 
		//  depth (or z) buffer.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

//		::HandleDebugLights(shaderProgID);
		//::HandleDebugPirate(pDebugRenderer);

		::Graphics_MidTerm_2019_Flicker();
		::Graphics_MidTerm_2019_FlyCamera();

		// Lightmanager handles all lighting
		cLightManager lightManager(shaderProgID);
		lightManager.ApplyLights();

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

			pTheVAOManager->DrawObject( matModel, pCurrentObject);

		} // for (auto object: mapObjects)

		// Update the physics
		double averageDeltaTime = avgDeltaTimeThingy.getAverage();
		//pPhsyics->IntegrationStep(mapObjects, (float)averageDeltaTime);
				

//		::HandleDebugBallPhysics(shaderProgID, pPhsyics, pTheVAOManager, pDebugRenderer,&mapLoaded);

		// A more general 
//		pPhsyics->TestForCollisions(mapObjects);
//		::LightDebugSheres(shaderProgID, pTheVAOManager);

		pDebugRenderer->RenderDebugObjects( view, projection, 0.01f );

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();

	return (EXIT_SUCCESS);
}
