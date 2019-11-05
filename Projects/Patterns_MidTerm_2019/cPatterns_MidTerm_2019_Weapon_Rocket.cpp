#include "cPatterns_MidTerm_2019_Weapon_Rocket.h"
#include "DebugRenderer/cDebugRenderer.h"


extern cDebugRenderer* gDebugRenderer;


cPatterns_MidTerm_2019_Weapon_Rocket::cPatterns_MidTerm_2019_Weapon_Rocket()
{

}

cPatterns_MidTerm_2019_Weapon_Rocket::~cPatterns_MidTerm_2019_Weapon_Rocket()
{
}

bool cPatterns_MidTerm_2019_Weapon_Rocket::IsBalistic()
{
	return false;
}

template <class T>
static T randInRange(T min, T max)
{
	double value =
		min + static_cast <double> (rand())
		/ (static_cast <double> (RAND_MAX / (static_cast<double>(max - min))));
	return static_cast<T>(value);
};


static bool RobotInSight(const glm::vec3& me, const glm::vec3& them)
{
	// Hack for robot on sight. Just do a random number
	return (randInRange(0, 2) == 0);
}

void cPatterns_MidTerm_2019_Weapon_Rocket::Shoot(const glm::vec3& source, const glm::vec3& target)
{
	if (!AmReloading())
	{
		glm::vec3 colour(0.0f, 1.0f, 1.0f);
		glm::vec3 start = source;
		glm::vec3 end = target;
		start.y += 5;
		end.y += 5;
		gDebugRenderer->addLine(start, end, colour, 1.5f);

		SetReloading();
		// It's instant
		m_weHit = true;

		// If it's in sight we hit it
		//   INFO6028 - Hack the balistics
		m_whereWeHit = target;
		if (!RobotInSight(source, target))
		{
			float radius = GetDamageRadius() + 3.0f;
			float randomx = randInRange(-radius, radius);
			float randomz = randInRange(-radius, +radius);
			m_whereWeHit.x += randomx;
			m_whereWeHit.z += randomz;
		}
	}
}

bool cPatterns_MidTerm_2019_Weapon_Rocket::DidWeHit(glm::vec3& where)
{
	where = m_whereWeHit;
	if (m_weHit)
	{
		m_weHit = false;
		return true;
	}
	return false;
}

void cPatterns_MidTerm_2019_Weapon_Rocket::Step(float deltatime)
{
	StepCommon(deltatime);			// Do common step work
}

bool cPatterns_MidTerm_2019_Weapon_Rocket::CanIShoot()
{
	return (!AmReloading());
}

