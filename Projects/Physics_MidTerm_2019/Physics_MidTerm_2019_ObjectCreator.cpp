#include "Physics_MidTerm_2019_ObjectCreator.h"

#include "AssetItems/cItem_Model.h"
#include "Physics/cPhysics_Henky.h"
#include "ObjectItems/cObject_Group.h"

#include <cstdlib>
#include <ostream>
#include <iostream>
#include <time.h>
#include <map>

static glm::vec3 g_whole_min;
static glm::vec3 g_whole_max;
static glm::vec3 g_whole_length;
static float g_whole_length_float;

template <class T>
static T randInRange(T min, T max)
{
	double value =
		min + static_cast <double> (rand())
		/ (static_cast <double> (RAND_MAX / (static_cast<double>(max - min))));
	return static_cast<T>(value);
};

static void highPointOfbox(glm::vec3& min, glm::vec3& max)
{
	auto temp = cObjectManager().FindObjectByName("low_cube");
	cObject_Model* cubeObject = dynamic_cast<cObject_Model*>(temp);
	assert(cubeObject);
	cPhysics_Henky::boundsOfObject(*cubeObject, min, max);
}

const int g_arraySize = 1000;
bool g_vectorMap[g_arraySize][g_arraySize];
const int g_divisor = 100;

void Create2Dmatrix(cObject_Model* pObject)
{
//	const int minCube = 10;
	double size_y = g_whole_max.y - g_whole_min.y;
	double size_z = g_whole_max.z - g_whole_min.z;
	double size_max = (size_y > size_z) ? size_y : size_z;
	int dimentions = (int(size_max)) / g_divisor;
	assert(dimentions < g_arraySize);

	for (int i = 0; i < g_arraySize; i++)
		for (int j = 0; j < g_arraySize; j++)
			g_vectorMap[i][j] = false;

	auto mesh = pObject->GetItem();
	assert(mesh);
	cItem_Model* objectItem = dynamic_cast<cItem_Model*>(mesh);
	assert(objectItem);

	for (auto vertice : objectItem->m_vecVertices)
	{
		// zero offset
		float positionY = vertice.y - g_whole_min.y;
		float positionZ = vertice.z - g_whole_min.z;

		int intPosY = int(positionY) / g_divisor;
		assert(intPosY < g_arraySize);
		int intPosZ = int(positionZ) / g_divisor;
		assert(intPosZ < g_arraySize);

//		std::cout << intPosY << ", " << intPosZ << ", ";

		g_vectorMap[intPosY][intPosZ] = true;
	}
}

void Physics_MidTerm_2019_CalculateBounds(rapidxml::xml_node<>* parent)
{
	cObjectManager manager;

	glm::vec3 exposed_min;
	glm::vec3 exposed_max;

	auto temp = manager.FindObjectByName("Parts_Exposed");
	cObject_Model* exposed = dynamic_cast<cObject_Model*>(temp);
	assert(exposed);
	cPhysics_Henky::boundsOfObject(*exposed, exposed_min, exposed_max);
	
	exposed->AABB_min = exposed_min;
	exposed->AABB_max = exposed_max;

	manager.SaveObject(exposed, parent);

	glm::vec3 safe_min;
	glm::vec3 safe_max;

	temp = manager.FindObjectByName("Parts_Safe");
	cObject_Model* safe = dynamic_cast<cObject_Model*>(temp);
	assert(safe);
	cPhysics_Henky::boundsOfObject(*safe, safe_min, safe_max);

	safe->AABB_min = safe_min;
	safe->AABB_max = safe_max;
	manager.SaveObject(safe, parent);

	glm::vec3 safe_length = safe_max - safe_min;
	glm::vec3 exposed_length = exposed_max - exposed_min;

	g_whole_min = exposed_min;
	g_whole_max = exposed_max;

	if (safe_min.x < g_whole_min.x)
		g_whole_min.x = safe_min.x;
	if (safe_min.y < g_whole_min.y)
		g_whole_min.y = safe_min.y;
	if (safe_min.z < g_whole_min.z)
		g_whole_min.z = safe_min.z;

	if (safe_max.x > g_whole_max.x)
		g_whole_max.x = safe_max.x;
	if (safe_max.y > g_whole_max.y)
		g_whole_max.y = safe_max.y;
	if (safe_max.z > g_whole_max.z)
		g_whole_max.z = safe_max.z;

	g_whole_length = g_whole_max - g_whole_min;

	g_whole_length_float = g_whole_max.x - g_whole_min.x;

	glm::vec3 Asteroid_011_min;
	glm::vec3 Asteroid_011_max;

	temp = manager.FindObjectByName("Asteroid_011");
	cObject_Model* Asteroid_011 = dynamic_cast<cObject_Model*>(temp);
	assert(Asteroid_011);
	cPhysics_Henky::boundsOfObject(*Asteroid_011, Asteroid_011_min, Asteroid_011_max);

	auto Asteroid_011_length = glm::length(Asteroid_011_max - Asteroid_011_min);

	Asteroid_011->SPHERE_radius = Asteroid_011_length / 2;
	manager.SaveObject(Asteroid_011, parent);

	glm::vec3 Asteroid_014_min;
	glm::vec3 Asteroid_014_max;

	temp = manager.FindObjectByName("Asteroid_014");
	cObject_Model* Asteroid_014 = dynamic_cast<cObject_Model*>(temp);
	assert(Asteroid_014);
	cPhysics_Henky::boundsOfObject(*Asteroid_014, Asteroid_014_min, Asteroid_014_max);

	auto Asteroid_014_length = glm::length(Asteroid_014_max - Asteroid_014_min);

	Asteroid_014->SPHERE_radius = Asteroid_014_length / 2;
	manager.SaveObject(Asteroid_014, parent);

	glm::vec3 Asteroid_015_min;
	glm::vec3 Asteroid_015_max;

	temp = manager.FindObjectByName("Asteroid_015");
	cObject_Model* Asteroid_015 = dynamic_cast<cObject_Model*>(temp);
	assert(Asteroid_015);
	cPhysics_Henky::boundsOfObject(*Asteroid_015, Asteroid_015_min, Asteroid_015_max);

	auto Asteroid_015_length = glm::length(Asteroid_015_max - Asteroid_015_min);

	Asteroid_015->SPHERE_radius = Asteroid_015_length / 2;
	manager.SaveObject(Asteroid_015, parent);

	Create2Dmatrix(exposed);
}

static time_t g_lastCreated = 0;

static int g_lastName = 0;
static const char* g_astroids[3] = { "Asteroid_011", "Asteroid_014", "Asteroid_015" };
static std::vector<cObject_Model*> g_AsteroidObjects;

// INFO6019 - Creates a new asteroid every second

void Physics_MidTerm_2019_CreateNewAstroid(float deltatime, rapidxml::xml_node<>* parent)
{
	time_t currentTime = time(NULL);

//	std::cout << "CurrentTime: " << g_lastCreated << " : " << currentTime << std::endl;

	if ((currentTime - g_lastCreated) > 0)
	{
	
		time_t currentTime = time(NULL);
		
		std::cout << "Creating a new astroid at time: " << currentTime << std::endl;

		g_lastCreated = currentTime;

		cObjectManager manager;
		int astroidIndex = randInRange(0, 2);
		std::string astroidName = g_astroids[astroidIndex];

		auto temp = manager.FindObjectByName(astroidName);
		cObject_Model* asteroid = dynamic_cast<cObject_Model*>(temp);
		assert(asteroid);

		std::string newName = astroidName + "_" + std::to_string(g_lastName);
		g_lastName++;
		temp = asteroid->Clone(newName);
		assert(temp);
		cObject_Model* newAstroid = dynamic_cast<cObject_Model*>(temp);
		assert(newAstroid);

		glm::vec3 startPosition;
		startPosition.x = randInRange(g_whole_length.x, g_whole_length.x + 200);
		// More hits this way for testing
		//startPosition.y = randInRange(g_whole_min.y, g_whole_max.y);
		//startPosition.z = randInRange(g_whole_min.z, g_whole_max.z );
		startPosition.y = randInRange(g_whole_min.y * 1.5f, g_whole_max.y * 1.5f);
		startPosition.z = randInRange(g_whole_min.z * 1.5f, g_whole_max.z * 1.5f);

		newAstroid->positionXYZ = startPosition;

		glm::vec3 startVelocity;

		startVelocity.x = randInRange(-600.0f, -1000.0f);
		startVelocity.y = 0.0f;
		startVelocity.z = 0.0f;

		newAstroid->physicsShapeType = cObject_Physics::SPHERE;
		newAstroid->velocity = startVelocity;
		newAstroid->SetVisable(true);
		newAstroid->acceleration = glm::vec3(0.0f, 0.0f, 0.0f);

		newAstroid->inverseMass = 1.0f;
		newAstroid->HACK_Exploding_Simulation = true;
		// Save the object to the object array
		manager.SaveObject(newAstroid, parent);
		g_AsteroidObjects.push_back(newAstroid);
	}
}

std::vector< cObject_Model* > g_laserBalls;
bool g_lazerOn;
bool g_lazerSimulationOn;
float g_lazerScale = 0;

// INFO6019 - Preallocates all of the balls for the laser shots

void Physics_MidTerm_2019_LaserBalls(int number, cObjectManager& objectManager, rapidxml::xml_node<>* parent)
{
	g_lazerOn = false;
	g_lazerSimulationOn = false;
	// Make a bunch of balls
	std::string name = "Drop_Sphere";
	auto dropBall = objectManager.FindObjectByName(name);
	assert(dropBall);

	for (int i = 0; i < number; ++i)
	{
		std::string newName = name + "_" + std::to_string(i);
		auto temp = dropBall->Clone(newName);
		assert(temp);
		cObject_Model* newBall = dynamic_cast<cObject_Model*>(temp);
		assert(newBall);
		
		glm::vec4 rgb = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
		newBall->objectColourRGBA = rgb;
		newBall->scale = 20.0;
		newBall->SPHERE_radius = 20.0;// = float(newscale);
		newBall->m_isVisable = false;
		newBall->inverseMass = 0;
		objectManager.SaveObject(newBall, parent);
		g_laserBalls.push_back(newBall);
	}
}

// INFO6019 - Checks to see if an asteroid is in range or will hit the space station

static bool inRange( cObject_Model* pModel)
{
	auto current_x = pModel->positionXYZ.x;
	auto min_x = g_whole_max.x + 200;
	auto max_x = g_whole_length.x / 2;
	// Close enough
	if (current_x < min_x || current_x > max_x)
		return false;

	// Check y/z bounds of the space station
	if (pModel->positionXYZ.y > g_whole_max.y)
		return false;
	if (pModel->positionXYZ.y < g_whole_min.y)
		return false;
	if (pModel->positionXYZ.z > g_whole_max.z)
		return false;
	if (pModel->positionXYZ.z < g_whole_min.z)
		return false;

	// zero offset
	float positionY = pModel->positionXYZ.y - g_whole_min.y;
	float positionZ = pModel->positionXYZ.z - g_whole_min.z;

	int intPosY = int(positionY) / g_divisor;
	assert(intPosY < g_arraySize);
	int intPosZ = int(positionZ) / g_divisor;
	assert(intPosZ < g_arraySize);

	if (g_vectorMap[intPosY][intPosZ])
	{
		std::cout << "We have a potential hit: y: " << intPosY << " z: " << intPosZ << std::endl;
	}
	// INFO6019 - failed attempt at detecting bounds of object
	//    just use the bounding box

//	return g_vectorMap[intPosY][intPosZ];
	return true;
}

// INFO6019 - shoots the laser and runs the simulation of the laser blinking out

void Physics_MidTerm_2019_Shoot_Laser(float deltatime)
{
	if (g_lazerSimulationOn)
	{
		const float scale = 0.40f;
		g_lazerScale -= scale;

		// INFO6019 - slowly scale the laser balls till they vanish
		for (auto balls : g_laserBalls)
		{
			balls->scale = g_lazerScale;
			if (g_lazerScale <= 1.0)
			{
				balls->m_isVisable = false;
				g_lazerSimulationOn = false;
			}
		}
		return;
	}

	if (!g_lazerOn)
		return;
	// Find an asteroid within range
	for (auto model : g_AsteroidObjects)
	{
		if (model->IsVisable() && model->velocity != glm::vec3(0.0f, 0.0f, 0.0f))
		{
			if (inRange(model))
			{
				auto temp = cObjectManager().FindObjectByName("Sphere#1");
				assert(temp);
				cObject_Model* newBall = dynamic_cast<cObject_Model*>(temp);
				assert(newBall);

				model->inverseMass = 0;
				model->velocity = glm::vec3(0.0f, 0.0f, 0.0f);
				model->m_assetID = newBall->GetAssetID();
				model->m_Item = newBall->m_Item;				// Chnage the item to a ball
				model->scale = 120.0;							// scale it
				glm::vec4 rgb = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
				model->objectColourRGBA = rgb;		// Red
				model->debugColour = rgb;
				model->isWireframe = true;
				model->HACK_Physics_DebugBall_Damage = true;
				model->HACK_Physics_Time_Of_Simulation = time(NULL);
				model->HACK_Physics_DebugBall_Vanishes = true;
				model->physicsShapeType = cObject_Physics::UNKNOWN;
				model->SPHERE_radius = 120.0;
				model->m_isVisable = true;
				std::cout << "We are lazering an asteroid - time: " << " Time: "
					<< model->HACK_Physics_Time_Of_Simulation
					<< " Item: " << model->m_Item->GetAssetID() << std::endl;

				// Now draw the line of balls to the object

				glm::vec3 startPosition = glm::vec3(g_whole_max.x + 30, 0.0f, 0.0f);
				glm::vec3 endPositon = model->positionXYZ;

				glm::vec3 laserLength = endPositon - startPosition;

				// INFO6019 - 500 balls per laser shot
				int totalBalls = 500;
				glm::vec3 incrementVector = float(1.0f/ totalBalls)*laserLength;	// 500 balls
				for (int i = 0; i < totalBalls; i++)
				{
					cObject_Model* item = g_laserBalls[i];
					item->isWireframe = true;
					item->m_isVisable = true;
					item->debugColour = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);	// blue
					item->positionXYZ = startPosition;
					startPosition += incrementVector;
					item->objectColourRGBA = item->debugColour;
					item->inverseMass = 0.0f;
					item->velocity = glm::vec3(0.0f);
					item->scale = 5.0f;
					g_lazerScale = item->scale;
				}
				g_lazerSimulationOn = true;
				// One at a time
				break;
			}
		}
	}
}

void Physics_MidTerm_2019_CloneObject(int number, const std::string& name, rapidxml::xml_node<>* parent)
{
	srand(unsigned int(time(NULL)));
	cObjectManager objectManager;

	auto object = objectManager.FindObjectByName(name);
	for (int i = 0; i < number; ++i)
	{
		std::string newName = name + "_" + std::to_string(i);
		auto temp = object->Clone(newName);
		assert(temp);
		objectManager.SaveObject(temp, parent);
	}
}
