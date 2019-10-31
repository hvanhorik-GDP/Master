#include "GLCommon.h"
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>

#include "globalStuff.h"

//#include "linmath.h"
#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp>
// glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <stdlib.h>		// c libs
#include <stdio.h>		// c libs

#include <iostream>		// C++ IO standard stuff
#include <map>			// Map aka "dictonary" 

#include "cModelLoader.h"			
#include "cVAOManager.h"		// NEW
#include "cGameObject.h"

#include "cShaderManager.h"

#include <sstream>

#include <limits.h>
#include <float.h>

// The Physics function
#include "PhysicsStuff.h"
#include "cPhysics.h"

#include "cLowPassFilter.h"

#include "DebugRenderer/cDebugRenderer.h"

// Used to visualize the attenuation of the lights...
#include "LightManager/cLightHelper.h"

#include "cParticleEmitter.h"

#include "cFlyCamera.h"

#include "cAABB.h"

#include "cBasicTextureManager.h"

// Keyboard, error, mouse, etc. are now here
#include "GFLW_callbacks.h"

// Is needed inside the DrawObject() call
cBasicTextureManager* g_pTextureManager = NULL;


void DrawObject(glm::mat4 m,
				cGameObject* pCurrentObject,
				GLint shaderProgID,
				cVAOManager* pVAOManager);

// This is JUST the transformation lines from the DrawObject call
glm::mat4 calculateWorldMatrix( cGameObject* pCurrentObject );

void LoadModelsIntoScene(cVAOManager* pTheVAOManager, cModelLoader* pTheModelLoader,
						 GLuint shaderProgID, iDebugRenderer* pDebugRenderer,
						 std::vector<cGameObject*>& vec_pGameObjects);

void CalcAABBsForMeshModel( cMesh &theMesh );

// This is in the PhysicsAABBStuff.cpp file
extern std::map<unsigned long long /*ID*/, cAABB*> g_mapAABBs_World;



//glm::vec3 cameraEye = glm::vec3(0.0, 80.0, -80.0);
//glm::vec3 cameraTarget = glm::vec3(0.0f, 10.0, 0.0f);
//glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);

glm::vec3 sexyLightPosition = glm::vec3(-25.0f, 300.0f, -52.0f);
float sexyLightConstAtten = 0.0000001f;			// not really used (can turn off and on the light)
float sexyLightLinearAtten = 0.00534943538;
float sexyLightQuadraticAtten = 1.00000001e-07;

float sexyLightSpotInnerAngle = 5.0f;
float sexyLightSpotOuterAngle = 7.5f;
// This is a "normalized" direction
// (i.e. the length is 1.0f)
glm::vec3 sexyLightSpotDirection = glm::vec3(0.0f, -1.0f, 0.0f);

bool bLightDebugSheresOn = true;


// Load up my "scene"  (now global)
std::vector<cGameObject*> g_vec_pGameObjects;
std::map<std::string /*FriendlyName*/, cGameObject*> g_map_GameObjectsByFriendlyName;

cFlyCamera* g_pFlyCamera = NULL;


// HACK 
extern std::map<unsigned long long /*ID*/, cAABB*> g_vecAABBs_World;


//bool g_BallCollided = false;



//void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
//{
//	// Move the sphere to where the camera is and shoot the ball from there...
//
////	cGameObject* pTheBall = pFindObjectByFriendlyName("Sphere#1");
////
////	// What's the velocity
////	// Target - eye = direction
////	glm::vec3 direction = glm::normalize( cameraTarget - cameraEye ); 
////
////	float speed = 5.0f; 
////
////	pTheBall->velocity = direction * speed;
////	pTheBall->positionXYZ = cameraEye;
//
//	return;
//}

// Make a class with a vector of doubles. 
// Set this vector to all zeros. 
// Add a method: addTime();
// Add a method: getAgerage();


int main(void)
{
	//int myArray[15];		// Integers stores integers

	//std::vector<int> myVector;
	//myVector.push_back( 25 );		// 0
	//myVector.push_back(  8 );		// 1
	//myVector.push_back( 17 );		// 2
	//myVector.push_back(  1 );
	//myVector.push_back( 11 );		// Ball
	//myVector.push_back(  6 );
	//myVector.push_back( 15 );
	//myVector.push_back( 25 );		// Pirate
	//myVector.push_back( 22 );
	//myVector.push_back( 27 );
	//myVector.push_back( 13 );
	//std::cout << myVector[3];
//
	//std::map<int, int> myMap;
	//myMap[0] = 25;		// 0
	//myMap[1] =  8;		// 1
	//myMap[2] = 17;		// 2
	//myMap[3] =  1;
	//myMap[4] = 11;		
	//myMap[5] =  6;
	//myMap[6] = 15;
	//myMap[7] = 25;	
	//myMap[8] = 22;
	//myMap[9] = 27;
	//myMap[10] = 13;		// I WANT THIS ONE
	//myMap.find( 13 );

	//std::map<std::string, cGameObject> myMap;
	//myMap["PirateShip"]


	// A map for favorite foods
	std::map< std::string /*index*/, std::string > mapNameToFood;

	// 11 -> 2.3
	// 111 -> 4.7
	// 1000 -> 6.7
	// 10000 -> 9
	// 100,000 -> 11
	mapNameToFood["Felipe"] = "Hay";
	mapNameToFood["Hamza"] = "Pancake";
	mapNameToFood["Dylan"] = "Fish Food";
	mapNameToFood["Ethan"] = "Fish";
	mapNameToFood["Brandon"] = "Pizza";
	mapNameToFood["Brian"] = "Dog food";
	mapNameToFood["Caleb"] = "Eggs";
	mapNameToFood["Christopher"] = "Pie";
	mapNameToFood["David"] = "Cat food";
	mapNameToFood["Dhilip"] = "Noodles";
	mapNameToFood["Harshil"] = "Chocolate";

	std::string favFood = mapNameToFood["Dhilip"];
	std::cout << favFood << std::endl;



	GLFWwindow* window;
	//GLuint vertex_buffer, vertex_shader, fragment_shader, program;
	//GLint mvp_location; /*, vpos_location, vcol_location;*/

	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}



	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(window, key_callback);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);

	// Mouse callbacks
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorEnterCallback(window, cursor_enter_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	void ProcessAsyncMouse(GLFWwindow * window);
	void ProcessAsyncKeys(GLFWwindow * window);



	//glfwSetJoystickCallback(joystick_callback);

	cDebugRenderer* pDebugRenderer = new cDebugRenderer();
	pDebugRenderer->initialize();


//	pDebugRenderer->RenderDebugObjects(glm::mat4(1.0f), glm::mat4(1.0f), 0.0f);

	// OpenGL and GLFW are good to go, so load the model
	//cModelLoader theModelLoader;   // Stack
	//theModelLoader.LoadPlyModel();


	cModelLoader* pTheModelLoader = new cModelLoader();	// Heap



	cShaderManager* pTheShaderManager = new cShaderManager();

	cShaderManager::cShader vertexShad;
	vertexShad.fileName = "assets/shaders/vertexShader01.glsl";

	cShaderManager::cShader fragShader;
	fragShader.fileName = "assets/shaders/fragmentShader01.glsl";

	if (!pTheShaderManager->createProgramFromFile("SimpleShader", vertexShad, fragShader))
	{
		std::cout << "Error: didn't compile the shader" << std::endl;
		std::cout << pTheShaderManager->getLastError();
		return -1;
	}

	GLuint shaderProgID = pTheShaderManager->getIDFromFriendlyName("SimpleShader");

	// Create a VAO Manager...
	// #include "cVAOManager.h"  (at the top of your file)
	cVAOManager* pTheVAOManager = new cVAOManager();

	LoadModelsIntoScene(pTheVAOManager, pTheModelLoader, shaderProgID, pDebugRenderer, 
						::g_vec_pGameObjects);


	// Texture stuff
	::g_pTextureManager = new cBasicTextureManager();
	::g_pTextureManager->SetBasePath("assets/textures");

	if (!::g_pTextureManager->Create2DTextureFromBMPFile("AlienBluray_512x512.bmp", true))
	{
		std::cout << "Didn't load texture" << std::endl;
	}

	GLint ID = ::g_pTextureManager->getTextureIDFromName("AlienBluray_512x512.bmp");


	::g_pTextureManager->Create2DTextureFromBMPFile("Pizza.bmp", true);


	cParticleEmitter* pMyPartcles = new cParticleEmitter();
	pMyPartcles->location = glm::vec3(0.0f, 3.0f, 0.0f);
	// TODO:
	pMyPartcles->acceleration = glm::vec3(5.0f, 0.0f, 0.0f);

	pMyPartcles->Initialize( glm::vec3( -10.0f, -10.0f, -10.0f),	// Min Vel
							 glm::vec3(  10.0f,  10.0f,  10.0f), // Max Vel
							 glm::vec3(0.0f,0.0f,0.0f),		// Min Delta Position
							 glm::vec3(0.0f,0.0f,0.0f),		// Max delta Position
							 5.0f, // Min life
							 10.0f, // Max life
							 10,		// Min # of particles per frame
							 60 );	// Max # of particles per frame



	//vecGameObjects.push_back(pirate);			// vecGameObjects[0]
	//vecGameObjects.push_back(bunny);		
	//vecGameObjects.push_back(bunny2);
//	vecGameObjects.push_back(terrain);

	//mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);


	::g_pFlyCamera = new cFlyCamera();
	::g_pFlyCamera->eye = glm::vec3( 0.0f, 80.0, -80.0 );
	


	glEnable(GL_DEPTH);			// Write to the depth buffer
	glEnable(GL_DEPTH_TEST);	// Test with buffer when drawing

	//float shipVelocityZ = 1.0f;
	//float shipAccelz = 1000.0f;

	
	cPhysics* pPhsyics = new cPhysics();

	cLowPassFilter avgDeltaTimeThingy;


	cLightHelper* pLightHelper = new cLightHelper();

	// Get the initial time
	double lastTime = glfwGetTime();


	while (!glfwWindowShouldClose(window))
	{

		// Get the initial time
		double currentTime = glfwGetTime();

		// Frame time... (how many seconds since last frame)
		double deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		const double SOME_HUGE_TIME = 0.1;	// 100 ms;
		if (deltaTime > SOME_HUGE_TIME)
		{
			deltaTime = SOME_HUGE_TIME;
		}

		avgDeltaTimeThingy.addValue(deltaTime);


		ProcessAsyncKeys(window);
		ProcessAsyncMouse(window);


		glUseProgram(shaderProgID);

		float ratio;
		int width, height;
		//       mat4x4 m, p, mvp;
		//glm::mat4 m, p, v, mvp;
		glm::mat4 p, v;

		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;

		// Projection matrix
		p = glm::perspective(0.6f,		// FOV
							 ratio,			// Aspect ratio
							 0.1f,			// Near clipping plane
							 10000.0f);		// Far clipping plane

		// View matrix
		v = glm::mat4(1.0f);

		//glm::vec3 cameraEye = glm::vec3(0.0, 0.0, -4.0);
		//glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
		//glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);

//		v = glm::lookAt(cameraEye,
//						cameraTarget,
//						upVector);
		v = glm::lookAt( ::g_pFlyCamera->eye, 
						 ::g_pFlyCamera->getAtInWorldSpace(), 
						 ::g_pFlyCamera->getUpVector() );
		 

		glViewport(0, 0, width, height);

		// Clear both the colour buffer (what we see) and the 
		//  depth (or z) buffer.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


		// Set the lighting values for the shader. There is only 1 light right now.
		// uniform vec4 theLights[0].position
		// uniform vec4 theLights[0].diffuse
		// uniform vec4 theLights[0].specular
		// uniform vec4 theLights[0].atten
		// uniform vec4 theLights[0].direction
		// uniform vec4 theLights[0].param1
		// uniform vec4 theLights[0].param2		
		GLint L_0_position = glGetUniformLocation( shaderProgID, "theLights[0].position");
		GLint L_0_diffuse = glGetUniformLocation( shaderProgID, "theLights[0].diffuse");
		GLint L_0_specular = glGetUniformLocation( shaderProgID, "theLights[0].specular");
		GLint L_0_atten = glGetUniformLocation( shaderProgID, "theLights[0].atten");
		GLint L_0_direction = glGetUniformLocation( shaderProgID, "theLights[0].direction");
		GLint L_0_param1 = glGetUniformLocation( shaderProgID, "theLights[0].param1");
		GLint L_0_param2 = glGetUniformLocation( shaderProgID, "theLights[0].param2");

		glUniform4f(L_0_position, 
					sexyLightPosition.x,
					sexyLightPosition.y,
					sexyLightPosition.z,
					1.0f);
		glUniform4f(L_0_diffuse, 1.0f, 1.0f, 1.0f, 1.0f );	// White
		glUniform4f(L_0_specular, 1.0f, 1.0f, 1.0f, 1.0f );	// White
		glUniform4f(L_0_atten, 0.0f,  // constant attenuation
					           sexyLightLinearAtten,  // Linear 
					           sexyLightQuadraticAtten,	// Quadratic 
					           1000000.0f );	// Distance cut off

		// Point light:
		glUniform4f(L_0_param1, 0.0f /*POINT light*/, 0.0f, 0.0f, 1.0f );


		// ********************************************************
		// Move the pirate in the direction it's pointing in...
		
		// Vec4 = mat4x4 * vec4				vertFinal = matModel * vertStart;
		
		cGameObject* pPirate = pFindObjectByFriendlyName("PirateShip");

		glm::mat4 matRotY = glm::rotate(glm::mat4(1.0f),
										pPirate->HACK_AngleAroundYAxis,	//(float)glfwGetTime(),					// Angle 
										glm::vec3(0.0f, 1.0f, 0.0f));
	
		// Assume the ship is at 0,0,0
		glm::vec4 frontOfShip = glm::vec4(0.0f, 0.0f, -1.0f, 1.0f);	// pointing to the "front" of the ship
		
		// Vec4 = mat4x4 * vec4				vertFinal = matModel * vertStart;
		glm::vec4 frontOfShipInWorld = matRotY * frontOfShip;

		// this value would be the velocity, ifyou wanted the phsyics update do to it
		glm::vec3 newSpeedOfShipIN_THE_DIRECTION_WE_WANT_TO_GO
			= frontOfShipInWorld * pPirate->HACK_speed;

		// Draw a line showing where we are going...
		pDebugRenderer->addLine( pPirate->positionXYZ, 
								 pPirate->positionXYZ + (glm::vec3(frontOfShipInWorld) * pPirate->HACK_speed * 5.0f), 
								 glm::vec3( 1.0f, 0.0f, 0.0f), 0.5f );

		// Draw a line showing how fast we are going...

		// Update the pirate ship
		pPirate->positionXYZ += newSpeedOfShipIN_THE_DIRECTION_WE_WANT_TO_GO;

		
		// See which AABB the pirate ship is inside of... 
		unsigned long long pID = cAABB::get_ID_of_AABB_I_Might_Be_In(pPirate->positionXYZ);

		std::cout << "The pirate ship is at: "
			<< pPirate->positionXYZ.x << ", "
			<< pPirate->positionXYZ.y << ", " 
			<< pPirate->positionXYZ.z 
			<< "   and is inside AABB: " << pID 
			<< " which has " << ::g_mapAABBs_World[pID]->vecTriangles.size() << std::endl;



		//pDebugRenderer->addTriangle( pPirate->positionXYZ, 
		//							 glm::vec3(0.0f,0.0f,0.0f), 
		//							 glm::vec3(0.0f, 10.0f, 0.0f), 
		//							 glm::vec3(0.0f,1.0f,0.0f) );

		//pDebugRenderer->addLine( pPirate->positionXYZ, 
		//						 glm::vec3(0.0f, 10.0f, 0.0f), 
		//						 glm::vec3(0.0f,1.0f,0.0f),
		//						 2.0f );
		// ********************************************************


//	// Point the spot light at the bunny
//	cGameObject* pBunny = pFindObjectByFriendlyName("Bugs");
//	cGameObject* pPirate = pFindObjectByFriendlyName("PirateShip");
//
//	sexyLightPosition = pPirate->positionXYZ;
//
//	// Vector from the bunny to the ship is:
//	// Bunny_Position - ShipPosition;
//	glm::vec3 bunnyToShip = pBunny->positionXYZ - pPirate->positionXYZ;
//	// Normalize the vector (unit or 1.0f length)
//	sexyLightSpotDirection = glm::normalize(bunnyToShip);


		//// Spot light
		//glUniform4f(L_0_direction, 
		//			sexyLightSpotDirection.x,		// 0
		//			sexyLightSpotDirection.y,		// -1
		//			sexyLightSpotDirection.z,		// 0
		//			1.0f );	

		//glUniform4f(L_0_param1,
		//			1.0f /*SPOT light*/, 
		//			sexyLightSpotInnerAngle,		// 15
		//			sexyLightSpotOuterAngle,		// 30
		//			1.0f );


		//glUniform4f(L_0_param1,
		//			2.0f /*DIRECTIONAL light*/, 
		//			sexyLightSpotInnerAngle,		// 15
		//			sexyLightSpotOuterAngle,		// 30
		//			1.0f );


		glUniform4f(L_0_param2, 1.0f /*Light is on*/, 0.0f, 0.0f, 1.0f );

		// Also set the position of my "eye" (the camera)
		//uniform vec4 eyeLocation;
		GLint eyeLocation_UL = glGetUniformLocation( shaderProgID, "eyeLocation");

		//glUniform4f( eyeLocation_UL, 
		//			 cameraEye.x, cameraEye.y, cameraEye.z, 1.0f );
		glUniform4f( eyeLocation_UL, 
					 ::g_pFlyCamera->eye.x, 
					 ::g_pFlyCamera->eye.y, 
					 ::g_pFlyCamera->eye.z, 1.0f );


		std::stringstream ssTitle;
		ssTitle 
			<< sexyLightPosition.x << ", " 
			<< sexyLightPosition.y << ", " 
			<< sexyLightPosition.z 
			<< "Atten: "
			<< sexyLightConstAtten << " : "
			<< sexyLightLinearAtten << " : "
			<< sexyLightQuadraticAtten;
		glfwSetWindowTitle( window, ssTitle.str().c_str() );


		GLint matView_UL = glGetUniformLocation(shaderProgID, "matView");
		GLint matProj_UL = glGetUniformLocation(shaderProgID, "matProj");

		glUniformMatrix4fv(matView_UL, 1, GL_FALSE, glm::value_ptr(v));
		glUniformMatrix4fv(matProj_UL, 1, GL_FALSE, glm::value_ptr(p));


		// **************************************************
		// **************************************************
		// Loop to draw everything in the scene


		for (int index = 0; index != ::g_vec_pGameObjects.size(); index++)
		{
			glm::mat4 matModel = glm::mat4(1.0f);

			cGameObject* pCurrentObject = ::g_vec_pGameObjects[index];

			DrawObject( matModel, pCurrentObject, 
					   shaderProgID, pTheVAOManager);

		}//for (int index...


		// Update the objects through physics
//		PhysicsUpdate( vec_pGameObjects, 0.01f );



//		pPhsyics->IntegrationStep(::g_vec_pGameObjects, 0.01f);
//		pPhsyics->IntegrationStep(::g_vec_pGameObjects, (float)deltaTime);
		double averageDeltaTime = avgDeltaTimeThingy.getAverage();
		pPhsyics->IntegrationStep(::g_vec_pGameObjects, (float)averageDeltaTime);

		// Let's draw all the closest points to the sphere
		// on the terrain mesh....
		// 
		// For each triangle in the terrain mesh:
		// - Run ClosestPointToTriangle
		// - Place the debug sphere "there"
		// - Draw it.

		//**********************************************************
		//**********************************************************
		glm::vec3 closestPoint = glm::vec3(0.0f,0.0f,0.0f);
		cPhysics::sPhysicsTriangle closestTriangle;

		// HACK: These are in the LoadModelsIntoScene.cpp file
		extern cGameObject* pHiResCube;
		extern cMesh lowrescubeMesh;
		extern cMesh singleTriangleMesh;
		extern cGameObject* pShpere;


		// Update the mesh to match it's world position
		// 
		// NOTE: I'm DRAWING the high resultion mesh, so I'm taking the transformation 
		//       from the mesh that I'm DRAWING, and transforming the LOW RESOLUTION mesh
		//       into the same orientation (position in world space). 
		glm::mat4 matWorld = calculateWorldMatrix(pHiResCube);

		cMesh lowResCubeMesh_TRANSFORMED_WorldSpace;
		pPhsyics->CalculateTransformedMesh(lowrescubeMesh, matWorld, lowResCubeMesh_TRANSFORMED_WorldSpace);
//		pPhsyics->CalculateTransformedMesh(hirescubeMesh, matWorld, lowResCubeMesh_TRANSFORMED_WorldSpace);

		//glm::mat4 matSpaceStation = glm::mat4(1.0f);
		//pPhsyics->CalculateTransformedMesh(spaceStationMesh, matSpaceStation, lowResCubeMesh_TRANSFORMED_WorldSpace);

		// NOTE that I'm using the LOW RESOLUTION "cube" mesh, but DRAWING the high resolution mesh
//		pPhsyics->GetClosestTriangleToPoint(pShpere->positionXYZ, largeBunnyMesh, closestPoint, closestTriangle);
//		pPhsyics->GetClosestTriangleToPoint(pShpere->positionXYZ, lowrescubeMesh, closestPoint, closestTriangle);
//		pPhsyics->GetClosestTriangleToPoint(pShpere->positionXYZ, lowResCubeMesh_TRANSFORMED_WorldSpace, closestPoint, closestTriangle);
		pPhsyics->GetClosestTriangleToPoint(pShpere->positionXYZ, singleTriangleMesh, closestPoint, closestTriangle);


		// Highlight the triangle that I'm closest to
		pDebugRenderer->addTriangle(closestTriangle.verts[0], 
									closestTriangle.verts[1], 
									closestTriangle.verts[2],
									glm::vec3(1.0f, 0.0f, 0.0f) );

		// Highlight the triangle that I'm closest to
		// To draw the normal, calculate the average of the 3 vertices, 
		// then draw that average + the normal (the normal starts at the 0,0,0 OF THE TRIANGLE)
		glm::vec3 centreOfTriangle = ( closestTriangle.verts[0] + 
									   closestTriangle.verts[1] + 
									   closestTriangle.verts[2] ) / 3.0f;		// Average

		glm::vec3 normalInWorld = centreOfTriangle + (closestTriangle.normal * 20.0f);	// Normal x 10 length

		pDebugRenderer->addLine(centreOfTriangle, 
								normalInWorld,
								glm::vec3(1.0f, 1.0f, 0.0f) );

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
			float centreToContractDistance = glm::length( vecSphereToClosestPoint );

			// 3. Create a vector from closest point to radius
			float lengthPositionAdjustment = pShpere->SPHERE_radius - centreToContractDistance;

			// 4. Sphere is moving in the direction of the velocity, so 
			//    we want to move the sphere BACK along this velocity vector
			glm::vec3 vecDirection = glm::normalize( pShpere->velocity );

			glm::vec3 vecPositionAdjust = (-vecDirection) * lengthPositionAdjustment;

			// 5. Reposition sphere 
			pShpere->positionXYZ += (vecPositionAdjust);
//			pShpere->inverseMass = 0.0f;

			// ************************************************************************


			// Is in contact with the triangle... 
			// Calculate the response vector off the triangle. 
			glm::vec3 velocityVector = glm::normalize(pShpere->velocity);

			// closestTriangle.normal
			glm::vec3 reflectionVec = glm::reflect( velocityVector, closestTriangle.normal);
			reflectionVec = glm::normalize(reflectionVec);

			// Stop the sphere and draw the two vectors...
//			pShpere->inverseMass = 0.0f;	// Stopped

			glm::vec3 velVecX20 = velocityVector * 10.0f;
			pDebugRenderer->addLine( closestPoint, velVecX20, 
									 glm::vec3(1.0f, 0.0f, 0.0f),  30.0f /*seconds*/);

			glm::vec3 reflectionVecX20 = reflectionVec * 10.0f;
			pDebugRenderer->addLine( closestPoint, reflectionVecX20,
									 glm::vec3(0.0f, 1.0f, 1.0f),  30.0f /*seconds*/);

			// Change the direction of the ball (the bounce off the triangle)

			// Get lenght of the velocity vector
			float speed = glm::length(pShpere->velocity);

			pShpere->velocity = reflectionVec * speed;

		}




		//bool DidBallCollideWithGround = false;
		//HACK_BounceOffSomePlanes(pShpere, DidBallCollideWithGround );

		// A more general 
		pPhsyics->TestForCollisions(::g_vec_pGameObjects);





		//**********************************************************
		//**********************************************************




//		float closestDistanceSoFar = FLT_MAX;
//		glm::vec3 closetPoint = glm::vec3(0.0f,0.0f,0.0f);
//		sPlyTriangle closetTriangle;
//
//		for (unsigned int triIndex = 0;
//			 triIndex != terrainMesh.vecTriangles.size();
//			 triIndex++)
//		{
//			sPlyTriangle& curTriangle = terrainMesh.vecTriangles[triIndex];
//
//			// Get the vertices of the triangle
//			sPlyVertexXYZ_N triVert1 = terrainMesh.vecVertices[curTriangle.vert_index_1];
//			sPlyVertexXYZ_N triVert2 = terrainMesh.vecVertices[curTriangle.vert_index_2];
//			sPlyVertexXYZ_N triVert3 = terrainMesh.vecVertices[curTriangle.vert_index_3];
//
//			Point triVertPoint1;
//			triVertPoint1.x = triVert1.x;
//			triVertPoint1.y = triVert1.y;
//			triVertPoint1.z = triVert1.z;
//
//			Point triVertPoint2;
//			triVertPoint2.x = triVert2.x;
//			triVertPoint2.y = triVert2.y;
//			triVertPoint2.z = triVert2.z;
//
//			Point triVertPoint3;
//			triVertPoint3.x = triVert3.x;
//			triVertPoint3.y = triVert3.y;
//			triVertPoint3.z = triVert3.z;
//
//			glm::vec3 curClosetPoint = ClosestPtPointTriangle( 
//				pShpere->positionXYZ, 
//				triVertPoint1, triVertPoint2, triVertPoint3 );
//			
//			// Is this the closest so far?
//			float distanceNow = glm::distance(curClosetPoint, pShpere->positionXYZ);
//
//			// is this closer than the closest distance
//			if ( distanceNow <= closestDistanceSoFar )
//			{
//				closestDistanceSoFar = distanceNow;
//				closetPoint = curClosetPoint;
//			}
//
//			//glm::mat4 matModel = glm::mat4(1.0f);
//			//pDebugSphere->positionXYZ = closetPoint;
//			//DrawObject(matModel, pDebugSphere, 
//			//			   shaderProgID, pTheVAOManager);
//
//
//		}//for (unsigned int triIndex = 0;

		{// Draw closest point
			glm::mat4 matModel = glm::mat4(1.0f);
			::g_pDebugSphere->positionXYZ = closestPoint;
			::g_pDebugSphere->scale = 1.0f;
			::g_pDebugSphere->debugColour = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);
			::g_pDebugSphere->isWireframe = true;
			DrawObject(matModel, ::g_pDebugSphere,
					   shaderProgID, pTheVAOManager);
		}


		// How far did we penetrate the surface?
		glm::vec3 CentreToClosestPoint = pShpere->positionXYZ - closestPoint;

		// Direction that ball is going is normalized velocity
		glm::vec3 directionBall = glm::normalize(pShpere->velocity);	// 1.0f

		// Calcualte direction to move it back the way it came from
		glm::vec3 oppositeDirection = -directionBall;				// 1.0f

		float distanceToClosestPoint = glm::length(CentreToClosestPoint);

		pDebugRenderer->addLine( pShpere->positionXYZ, 
								 closestPoint, 
								 glm::vec3(0.0f, 1.0f, 0.0f), 
								 1.0f );




//		// HACK
//		if (DidBallCollideWithGround)
//		{ 
//			float sphereRadius = 1.0f;
//			float distanceToMoveBack = sphereRadius - distanceToClosestPoint;
//
//			glm::vec3 adjustmentVector = oppositeDirection * distanceToMoveBack;
//
//			// Let's move the sphere that amount...
//			pShpere->positionXYZ += adjustmentVector;
//
//
//			// NOW, I can calculate the correct response vector... 
//
////			pShpere->velocity = glm::reflect(pShpere->velocity, triangleNormal)
//		}


		//std::cout 
		//	<< pShpere->velocity.x << ", "
		//	<< pShpere->velocity.y << ", "
		//	<< pShpere->velocity.z << "   dist = "
		//	<< distanceToClosestPoint << std::endl;

		//howMuchToMoveItBack = 1.0 - lenthOfThatVector




		if (bLightDebugSheresOn) 
		{
			{// Draw where the light is at
				glm::mat4 matModel = glm::mat4(1.0f);
				::g_pDebugSphere->positionXYZ = sexyLightPosition;
				::g_pDebugSphere->scale = 0.5f;
				::g_pDebugSphere->debugColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
				::g_pDebugSphere->isWireframe = true;
				DrawObject(matModel, ::g_pDebugSphere,
						   shaderProgID, pTheVAOManager);
			}

			// Draw spheres to represent the attenuation...
			{   // Draw a sphere at 1% brightness
				glm::mat4 matModel = glm::mat4(1.0f);
				::g_pDebugSphere->positionXYZ = sexyLightPosition;
				float sphereSize = pLightHelper->calcApproxDistFromAtten( 
													   0.01f,		// 1% brightness (essentially black)
													   0.001f,		// Within 0.1%  
													   100000.0f,	// Will quit when it's at this distance
													   sexyLightConstAtten,
													   sexyLightLinearAtten,
													   sexyLightQuadraticAtten );
				::g_pDebugSphere->scale = sphereSize;
				::g_pDebugSphere->debugColour = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
				::g_pDebugSphere->isWireframe = true;
				DrawObject(matModel, ::g_pDebugSphere,
						   shaderProgID, pTheVAOManager);
			}
			{   // Draw a sphere at 25% brightness
				glm::mat4 matModel = glm::mat4(1.0f);
				::g_pDebugSphere->positionXYZ = sexyLightPosition;
				float sphereSize = pLightHelper->calcApproxDistFromAtten( 
													   0.25f,		// 1% brightness (essentially black)
													   0.001f,		// Within 0.1%  
													   100000.0f,	// Will quit when it's at this distance
													   sexyLightConstAtten,
													   sexyLightLinearAtten,
													   sexyLightQuadraticAtten );
				::g_pDebugSphere->scale = sphereSize;
				::g_pDebugSphere->debugColour = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
				::g_pDebugSphere->isWireframe = true;
				DrawObject(matModel, ::g_pDebugSphere,
						   shaderProgID, pTheVAOManager);
			}
			{   // Draw a sphere at 50% brightness
				glm::mat4 matModel = glm::mat4(1.0f);
				::g_pDebugSphere->positionXYZ = sexyLightPosition;
				float sphereSize = pLightHelper->calcApproxDistFromAtten( 
													   0.50f,		// 1% brightness (essentially black)
													   0.001f,		// Within 0.1%  
													   100000.0f,	// Will quit when it's at this distance
													   sexyLightConstAtten,
													   sexyLightLinearAtten,
													   sexyLightQuadraticAtten );
				::g_pDebugSphere->scale = sphereSize;
				::g_pDebugSphere->debugColour = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);
				::g_pDebugSphere->isWireframe = true;
				DrawObject(matModel, ::g_pDebugSphere,
						   shaderProgID, pTheVAOManager);
			}
			{   // Draw a sphere at 75% brightness
				glm::mat4 matModel = glm::mat4(1.0f);
				::g_pDebugSphere->positionXYZ = sexyLightPosition;
				float sphereSize = pLightHelper->calcApproxDistFromAtten( 
													   0.75f,		// 1% brightness (essentially black)
													   0.001f,		// Within 0.1%  
													   100000.0f,	// Will quit when it's at this distance
													   sexyLightConstAtten,
													   sexyLightLinearAtten,
													   sexyLightQuadraticAtten );
				::g_pDebugSphere->scale = sphereSize;
				::g_pDebugSphere->debugColour = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
				::g_pDebugSphere->isWireframe = true;
				DrawObject(matModel, ::g_pDebugSphere,
						   shaderProgID, pTheVAOManager);
			}
			{   // Draw a sphere at 95% brightness
				glm::mat4 matModel = glm::mat4(1.0f);
				::g_pDebugSphere->positionXYZ = sexyLightPosition;
				float sphereSize = pLightHelper->calcApproxDistFromAtten( 
													   0.95f,		// 1% brightness (essentially black)
													   0.001f,		// Within 0.1%  
													   100000.0f,	// Will quit when it's at this distance
													   sexyLightConstAtten,
													   sexyLightLinearAtten,
													   sexyLightQuadraticAtten );
				::g_pDebugSphere->scale = sphereSize;
				::g_pDebugSphere->debugColour = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
				::g_pDebugSphere->isWireframe = true;
				DrawObject(matModel, ::g_pDebugSphere,
						   shaderProgID, pTheVAOManager);
			}
		}// if (bLightDebugSheresOn) 

		 // **************************************************
		// **************************************************

		

		// ************************************************************
		::g_pDebugSphere->scale = 0.05f;
		::g_pDebugSphere->debugColour = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
		::g_pDebugSphere->isWireframe = true;
		glm::mat4 matModel = glm::mat4(1.0f);

		// Move emitter to where the pirate ship is...
		cGameObject* pPirateShip = pFindObjectByFriendlyName("PirateShip");

		cGameObject* pBunny =  pFindObjectByFriendlyName("Bugs");
		pBunny->scale = 5.0f;
//		pPirate->isVisible = false;

		pMyPartcles->location = pPirateShip->positionXYZ;

		pMyPartcles->Step( static_cast<float>(deltaTime) );

		// Draw objects at the location of the particles...
		std::vector<cParticle*> vecParticles;
		pMyPartcles->getParticles( vecParticles );
		for (std::vector<cParticle*>::iterator itPart = vecParticles.begin();
			 itPart != vecParticles.end(); itPart++)
		{
			// This is a little odd, because of the iterator syntax
			//pDebugSphere->positionXYZ = (*itPart)->location;
			//DrawObject(matModel, pDebugSphere,
			//		   shaderProgID, pTheVAOManager);

			pBunny->positionXYZ = (*itPart)->location;
			DrawObject(matModel, pBunny,
					   shaderProgID, pTheVAOManager);
		}
		// ************************************************************




		pDebugRenderer->RenderDebugObjects(v, p, 0.01f);



		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();


	// Delete everything
	delete pTheModelLoader;
//	delete pTheVAOManager;
	delete ::g_pFlyCamera;

	// Watch out!!
	// sVertex* pVertices = new sVertex[numberOfVertsOnGPU];
//	delete [] pVertices;		// If it's an array, also use [] bracket

	exit(EXIT_SUCCESS);
}


void DrawObject(glm::mat4 m, 
				cGameObject* pCurrentObject, 
				GLint shaderProgID,
				cVAOManager* pVAOManager)
{
	// 
				//         mat4x4_identity(m);

	if ( pCurrentObject->isVisible == false )
	{
		return;
	}

	// This block of code, where I generate the world matrix from the 
	// position, scale, and rotation (orientation) of the object
	// has been placed into calculateWorldMatrix()


	// ************ 
	// Set the texture bindings and samplers

	// Tie the texture to the texture unit
	GLuint alienTexID =	::g_pTextureManager->getTextureIDFromName("AlienBluray_512x512.bmp");
	glActiveTexture(GL_TEXTURE0);				// Texture Unit 0
	glBindTexture(GL_TEXTURE_2D, alienTexID);	// Texture now assoc with texture unit 0

	GLuint PizzaTexID =	::g_pTextureManager->getTextureIDFromName("Pizza.bmp");
	glActiveTexture(GL_TEXTURE5);				// Texture Unit 5
	glBindTexture(GL_TEXTURE_2D, PizzaTexID);	// Texture now assoc with texture unit 0


	// Tie the texture units to the samplers in the shader
	GLint textSamp01_UL = glGetUniformLocation( shaderProgID, "textSamp01" );
	glUniform1i(textSamp01_UL, 0);	// Texture unit 0

	GLint textSamp02_UL = glGetUniformLocation( shaderProgID, "textSamp02" );
	glUniform1i(textSamp02_UL, 5);	// Texture unit 5
	// ************




	m = calculateWorldMatrix( pCurrentObject );



	//uniform mat4 matModel;		// Model or World 
	//uniform mat4 matView; 		// View or camera
	//uniform mat4 matProj;
	GLint matModel_UL = glGetUniformLocation(shaderProgID, "matModel");

	glUniformMatrix4fv(matModel_UL, 1, GL_FALSE, glm::value_ptr(m));
	//glUniformMatrix4fv(matView_UL, 1, GL_FALSE, glm::value_ptr(v));
	//glUniformMatrix4fv(matProj_UL, 1, GL_FALSE, glm::value_ptr(p));

	// Calcualte the inverse transpose of the model matrix and pass that...
	// Stripping away scaling and translation, leaving only rotation
	// Because the normal is only a direction, really
	GLint matModelIT_UL = glGetUniformLocation(shaderProgID, "matModelInverseTranspose");
	glm::mat4 matModelInverseTranspose = glm::inverse(glm::transpose(m));
	glUniformMatrix4fv(matModelIT_UL, 1, GL_FALSE, glm::value_ptr(matModelInverseTranspose));




	// Find the location of the uniform variable newColour
	GLint newColour_location = glGetUniformLocation(shaderProgID, "newColour");

	glUniform3f(newColour_location,
				pCurrentObject->objectColourRGBA.r,
				pCurrentObject->objectColourRGBA.g,
				pCurrentObject->objectColourRGBA.b);

	//uniform float newColourRed;
	//uniform float newColourGreen;
	//uniform float newColourBlue;
	//GLint newColourRed_UL = glGetUniformLocation(shaderProgID, "newColourRed");
	//GLint newColourGreen_UL = glGetUniformLocation(shaderProgID, "newColourGreen");
	//GLint newColourBlue_UL = glGetUniformLocation(shaderProgID, "newColourBlue");

	//glUniform1f(newColourRed_UL, pCurrentObject->objectColourRGBA.r);
	//glUniform1f(newColourGreen_UL, pCurrentObject->objectColourRGBA.g);
	//glUniform1f(newColourBlue_UL, pCurrentObject->objectColourRGBA.b);
	//GLint lighPosition_UL = glGetUniformLocation(shaderProgID, "lightPosition");
	//glUniform3f(lighPosition_UL, sexyLightLocation.x,
	//			sexyLightLocation.y, sexyLightLocation.z);

	GLint diffuseColour_UL = glGetUniformLocation(shaderProgID, "diffuseColour");
	glUniform4f(diffuseColour_UL, 
				pCurrentObject->objectColourRGBA.r,
				pCurrentObject->objectColourRGBA.g,
				pCurrentObject->objectColourRGBA.b,
				pCurrentObject->objectColourRGBA.a);	// 

	GLint specularColour_UL = glGetUniformLocation(shaderProgID, "specularColour");
	glUniform4f(specularColour_UL,
				1.0f,	// R
				1.0f,	// G
				1.0f,	// B
				1000.0f);	// Specular "power" (how shinny the object is)
	                        // 1.0 to really big (10000.0f)


	//uniform vec4 debugColour;
	//uniform bool bDoNotLight;
	GLint debugColour_UL = glGetUniformLocation(shaderProgID, "debugColour");
	GLint bDoNotLight_UL = glGetUniformLocation(shaderProgID, "bDoNotLight");

	if ( pCurrentObject->isWireframe )
	{ 
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);		// LINES
		glUniform4f( debugColour_UL, 
					pCurrentObject->debugColour.r,
					pCurrentObject->debugColour.g,
					pCurrentObject->debugColour.b,
					pCurrentObject->debugColour.a);
		glUniform1f(bDoNotLight_UL, (float)GL_TRUE);
	}
	else
	{	// Regular object (lit and not wireframe)
		glUniform1f(bDoNotLight_UL, (float)GL_FALSE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);		// SOLID
	}
	//glPointSize(15.0f);

	if (pCurrentObject->disableDepthBufferTest)
	{
		glDisable(GL_DEPTH_TEST);					// DEPTH Test OFF
	}
	else
	{
		glEnable(GL_DEPTH_TEST);						// Turn ON depth test
	}

	if (pCurrentObject->disableDepthBufferWrite)
	{
		glDisable(GL_DEPTH);						// DON'T Write to depth buffer
	}
	else
	{
		glEnable(GL_DEPTH);								// Write to depth buffer
	}


	//		glDrawArrays(GL_TRIANGLES, 0, 2844);
	//		glDrawArrays(GL_TRIANGLES, 0, numberOfVertsOnGPU);

	sModelDrawInfo drawInfo;
	//if (pTheVAOManager->FindDrawInfoByModelName("bunny", drawInfo))
	if (pVAOManager->FindDrawInfoByModelName(pCurrentObject->meshName, drawInfo))
	{
		glBindVertexArray(drawInfo.VAO_ID);
		glDrawElements(GL_TRIANGLES,
					   drawInfo.numberOfIndices,
					   GL_UNSIGNED_INT,
					   0);
		glBindVertexArray(0);
	}
	
	return;
} // DrawObject;
// 

// returns NULL (0) if we didn't find it.
cGameObject* pFindObjectByFriendlyName(std::string name)
{
	// Do a linear search 
	for (unsigned int index = 0;
		 index != g_vec_pGameObjects.size(); index++)
	{
		if (::g_vec_pGameObjects[index]->friendlyName == name)
		{
			// Found it!!
			return ::g_vec_pGameObjects[index];
		}
	}
	// Didn't find it
	return NULL;
}

// returns NULL (0) if we didn't find it.
cGameObject* pFindObjectByFriendlyNameMap(std::string name)
{
	//std::map<std::string, cGameObject*> g_map_GameObjectsByFriendlyName;
	return ::g_map_GameObjectsByFriendlyName[name];
}


// This is JUST the transformation lines from the DrawObject call
glm::mat4 calculateWorldMatrix(cGameObject* pCurrentObject)
{

	glm::mat4 matWorld = glm::mat4(1.0f);


	// ******* TRANSLATION TRANSFORM *********
	glm::mat4 matTrans
		= glm::translate(glm::mat4(1.0f),
						 glm::vec3(pCurrentObject->positionXYZ.x,
								   pCurrentObject->positionXYZ.y,
								   pCurrentObject->positionXYZ.z));
	matWorld = matWorld * matTrans;
	// ******* TRANSLATION TRANSFORM *********



	// ******* ROTATION TRANSFORM *********
	//mat4x4_rotate_Z(m, m, (float) glfwGetTime());
	glm::mat4 rotateZ = glm::rotate(glm::mat4(1.0f),
									pCurrentObject->rotationXYZ.z,					// Angle 
									glm::vec3(0.0f, 0.0f, 1.0f));
	matWorld = matWorld * rotateZ;

	glm::mat4 rotateY = glm::rotate(glm::mat4(1.0f),
									pCurrentObject->rotationXYZ.y,	//(float)glfwGetTime(),					// Angle 
									glm::vec3(0.0f, 1.0f, 0.0f));
	matWorld = matWorld * rotateY;

	glm::mat4 rotateX = glm::rotate(glm::mat4(1.0f),
									pCurrentObject->rotationXYZ.x,	// (float)glfwGetTime(),					// Angle 
									glm::vec3(1.0f, 0.0f, 0.0f));
	matWorld = matWorld * rotateX;
	// ******* ROTATION TRANSFORM *********



	// ******* SCALE TRANSFORM *********
	glm::mat4 scale = glm::scale(glm::mat4(1.0f),
								 glm::vec3(pCurrentObject->scale,
										   pCurrentObject->scale,
										   pCurrentObject->scale));
	matWorld = matWorld * scale;
	// ******* SCALE TRANSFORM *********


	return matWorld;
}
