
#include "cPatterns_MidTerm_2019_World_impl.h"
#include "cPatterns_MidTerm_2019_Robot.h"
#include "cPatterns_MidTerm_2019_Weapon.h"
#include "cPatterns_MidTerm_2019_Weapon_Balistic.h"
#include "cPatterns_MidTerm_2019_Weapon_LineOfSight.h"
#include "cPatterns_MidTerm_2019_Weapon_Rocket.h"

#include "ObjectManager/cObjectManager.h"
#include "ObjectItems/cObject_Model.h"
#include "Physics/cPhysics_Henky.h"
#include "DebugRenderer/cDebugRenderer.h"

#include "gl/GLCommon.h"

#include <sstream>
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <iostream>
#include <stdio.h> 


// INFO6044 - world class (imple singletone)
// INFO0644 - Main mediator and builder
// INFO6044 - Most of the logic is here

extern cDebugRenderer* gDebugRenderer;

static glm::vec3 GetRandomLocation();

template <class T>
static T randInRange(T min, T max)
{
	double value =
		min + static_cast <double> (rand())
		/ (static_cast <double> (RAND_MAX / (static_cast<double>(max - min))));
	return static_cast<T>(value);
};

cPatterns_MidTerm_2019_World_impl::cPatterns_MidTerm_2019_World_impl()
{
}

cPatterns_MidTerm_2019_World_impl::~cPatterns_MidTerm_2019_World_impl()
{
	for (auto robot : m_robots)
	{
		delete robot;
	}
	for (auto weapon : m_wepons)
	{
		delete weapon;
	}
}

static bool RobotInSight(const glm::vec3& me, const glm::vec3& them)
{
	// Hack for robot on sight. Just do a random number
	return (randInRange(0, 5) == 0);
}

iPatterns_MidTerm_2019_Robot* cPatterns_MidTerm_2019_World_impl::FindClosetRobot(iPatterns_MidTerm_2019_Robot* me, bool insight, bool & isLineOfSight)
{
	assert(me);
	glm::vec3 myLocation = me->GetLocation();
	iPatterns_MidTerm_2019_Robot* retRobot = NULL;
	float minDistance = 1000000000;

	for (auto robot : m_robots)
	{
		if (robot != me && (robot->m_life > 0))
		{
			glm::vec3 location = robot->GetLocation();
			float distance = glm::length(myLocation - location);
			isLineOfSight = RobotInSight(myLocation, location);
			bool robotHittable = (insight) ? isLineOfSight : true;
			if (distance < minDistance && robotHittable)
			{
				minDistance = distance;
				retRobot = robot;
			}
		}
	}

	return retRobot;
}

// INFO6044 - mediator

void cPatterns_MidTerm_2019_World_impl::TeleportRobot(iPatterns_MidTerm_2019_Robot* me)
{
	assert(me);
	cPatterns_MidTerm_2019_Robot* robot = dynamic_cast<cPatterns_MidTerm_2019_Robot*>(me);
	assert(robot);
	cPhysics_Henky::Point newVec = GetRandomLocation();
	robot->m_location = newVec;
	robot->m_Model->positionXYZ = newVec;
	robot->m_Box->positionXYZ = newVec;
	robot->m_Box->positionXYZ.y += 20;
}

static glm::vec3 GetRandomLocation()
{
	cObjectManager objectManager;

	auto ter = objectManager.FindObjectByName("terrain");
	assert(ter);
	cObject_Model* terrain = dynamic_cast<cObject_Model*>(ter);
	assert(terrain);

	auto AABBMin = terrain->GetAABB_min();
	auto AABBMax = terrain->GetAABB_max();
	float newX = randInRange(AABBMin.x, AABBMax.x);
	float newZ = randInRange(AABBMin.z, AABBMax.z);
	float newY = AABBMax.y;

	cPhysics_Henky::Point newVec(glm::vec3(newX, newY, newZ));

	float previousY = newY;
	const float step = 5.0f;
	cPhysics_Henky physics;

	while (step > 0)
	{
		cPhysics_Henky::Point closest;

		cPhysics_Henky::sPhysicsTriangle triangle;
		physics.GetClosestTriangleToPoint(newVec, *terrain, closest, triangle);

		if (closest.y >= newVec.y)
		{
			newVec.y = previousY;
			break;
		}
		previousY = newVec.y;
		newVec.y -= step;
	}
	return newVec;
}



// INFO6044 - builder

void cPatterns_MidTerm_2019_World_impl::CreateRobots(int number, rapidxml::xml_node<>* parent)
{
	assert(number);
	assert(parent);
	cObjectManager objectManager;

	srand(unsigned int(time(NULL)));

	// Make a bunch of bunnies with cubes above them
	auto cube = objectManager.FindObjectByName("cube");
	assert(cube);
	std::string name = "bunny";
	auto bunny = objectManager.FindObjectByName(name);
	assert(bunny);



	for (int i = 0; i < number; ++i)
	{
		std::string newName = name + "_" + std::to_string(i);
		auto temp = bunny->Clone(newName);
		assert(temp);
		cObject_Model* newBunny = dynamic_cast<cObject_Model*>(temp);
		assert(newBunny);

		cPhysics_Henky::Point newVec = GetRandomLocation();

		float minRGB = 50;
		float maxRGB = 255;
		float r = randInRange(minRGB, maxRGB);
		float g = randInRange(minRGB, maxRGB);
		float b = randInRange(minRGB, maxRGB);
		glm::vec4 rgb = glm::vec4(r/maxRGB, g/maxRGB, b/maxRGB, 1);

		newBunny->objectColourRGBA = rgb;

		newBunny->positionXYZ = newVec;
		newBunny->scale = 0.2f;				// float(newscale);
		newBunny->SPHERE_radius = 1.0;		// = float(newscale);
		newBunny->m_isVisable = true;
		objectManager.SaveObject(newBunny, parent);

		int weapon_type = randInRange(1, 4);
		int rocket = randInRange(0, 9);
	
		if (rocket == 0)
			weapon_type = 0;

		std::stringstream ss1;
		ss1 << "cube_" + std::to_string(i);

		cObject_Model* newCube = dynamic_cast<cObject_Model*>(cube->Clone(ss1.str()));
		newCube->positionXYZ = newVec;
		newCube->positionXYZ.y += 20;
		newCube->scale = 0.4f;
		newCube->m_isVisable = true;
		cPatterns_MidTerm_2019_Weapon* weaponItem;

		std::stringstream ss;
		ss << " Creating bunny: " << newBunny->GetName(); 

		/// hack
//		weapon_type = 3;
		switch (weapon_type)
		{
		case 0:
		{
			ss << " with a Rocket" << std::endl;
			// Rocket
			weaponItem = new cPatterns_MidTerm_2019_Weapon_Rocket();
			weaponItem->m_damagePerShotPercentage = 0.30f;
			weaponItem->m_HasTravelTime = false;
			weaponItem->m_reloadRate = 10;
			weaponItem->m_DamageRadius = 7.5f;
			newCube->objectColourRGBA = glm::vec4(.05f, 0.5f, 0.5f, 1.0f);
			break;
		}
		case 1:
		{
			ss << " with a Laser" << std::endl;
			// Laser
			weaponItem = new cPatterns_MidTerm_2019_Weapon_LineOfSight();
			weaponItem->m_damagePerShotPercentage = 0.04f;
			weaponItem->m_HasTravelTime = false;
			weaponItem->m_reloadRate = 1;
			weaponItem->m_DamageRadius = 1.0f;
			newCube->objectColourRGBA = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
			break;
		}
		case 2:
		{
			ss << " with a Bomb" << std::endl;
			// Bomb
			weaponItem = new cPatterns_MidTerm_2019_Weapon_Balistic();
			weaponItem->m_damagePerShotPercentage = 0.25f;
			weaponItem->m_HasTravelTime = true;
			weaponItem->m_reloadRate = 5;
			weaponItem->m_DamageRadius = 5.0f;
			newCube->objectColourRGBA = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
			break;
		}
		case 3:
		{
			ss << " with a Bullet" << std::endl;
			// Bullet
			weaponItem = new cPatterns_MidTerm_2019_Weapon_LineOfSight();
			weaponItem->m_damagePerShotPercentage = 0.02f;
			weaponItem->m_HasTravelTime = false;
			weaponItem->m_reloadRate = 0.05;
			weaponItem->m_DamageRadius = 1.0f;
			newCube->objectColourRGBA = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
			break;
		}
		default:
			assert(false);
		}

		std::cout << ss.str();

		objectManager.SaveObject(newCube, parent);

		cPatterns_MidTerm_2019_Robot* robot = new cPatterns_MidTerm_2019_Robot();

		m_robots.push_back(robot);
		m_wepons.push_back(weaponItem);
		robot->m_Weapon = weaponItem;
		robot->m_location = newBunny->positionXYZ;
		robot->m_Model = newBunny;
		robot->m_Box = newCube;
	}
}

static bool InDamageRange(const glm::vec3 hitPosition, const glm::vec3& robotPosition, float radius)
{
	float length = glm::length(robotPosition - hitPosition);
	return length < radius;
}

void cPatterns_MidTerm_2019_World_impl::Step(float deltatime)
{
	for (auto weapon : m_wepons)
	{
		weapon->Step(deltatime);
	}
	for (auto robot : m_robots)
	{
		robot->Step(deltatime);
	}
	for (auto weapon : m_wepons)
	{
		glm::vec3 where;
		if (weapon->DidWeHit(where))
		{
			for (auto robot : m_robots)
			{
				if (InDamageRange(where, robot->GetLocation(), weapon->GetDamageRadius()))
				{
					int damage = 100 * (weapon->GetDamagePerShotPercentage());
					robot->m_life -= damage;
					if (damage > 4)
						std::cout << "Hit Robot: " << robot->m_Model->GetName() << " Damage: " << damage << std::endl;
					if (robot->m_life <= 0)
					{
						robot->m_life = 0;
						robot->m_Model->objectColourRGBA = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
						robot->m_Box->m_isVisable = false;
						std::cout << "Killed off robot : " << robot->m_Model->GetName() << std::endl;
					}
				}
			}
		}
	}
}

int cPatterns_MidTerm_2019_World_impl::NumberOfRobotsLeft()
{
	int count = 0;
	for (auto robot : m_robots)
	{
		if (robot->m_life > 0)
			count++;
	}
	return count;
}

std::string cPatterns_MidTerm_2019_World_impl::Winner()
{
	if (NumberOfRobotsLeft() > 1)
		return "";
	for (auto robot : m_robots)
	{
		if (robot->m_life > 0)
		{
			std::stringstream ss;
			ss << robot->m_Model->GetName() << " Health: " << robot->m_life;
			return ss.str();
		}
	}
	return "Error - all dead";
}
