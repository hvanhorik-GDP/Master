#include "cPatterns_MidTerm_2019_Weapon_Balistic.h"
#include "DebugRenderer/cDebugRenderer.h"

extern cDebugRenderer* gDebugRenderer;


template <class T>
static T randInRange(T min, T max)
{
	double value =
		min + static_cast <double> (rand())
		/ (static_cast <double> (RAND_MAX / (static_cast<double>(max - min))));
	return static_cast<T>(value);
};

cPatterns_MidTerm_2019_Weapon_Balistic::cPatterns_MidTerm_2019_Weapon_Balistic()
	: m_weHit(false)
	, m_whereWeHit(glm::vec3(0.0f, 0.0f, 0.0f))
	, m_flightTime(0.0f)
{

}

cPatterns_MidTerm_2019_Weapon_Balistic::~cPatterns_MidTerm_2019_Weapon_Balistic()
{
}

bool cPatterns_MidTerm_2019_Weapon_Balistic::IsBalistic()
{
	return true;
}


void cPatterns_MidTerm_2019_Weapon_Balistic::Shoot(const glm::vec3& source, const glm::vec3& target)
{
	if (!AmReloading() && (m_flightTime == 0))
	{
		//   INFO6028 - Hack the flight of balistics
		glm::vec3 colour(1.0f, 1.0f, 0.0f);
		glm::vec3 start = source;
		glm::vec3 end = target;
		start.y += 5;
		end.y += 5;
		gDebugRenderer->addLine(start, end, colour, 1.5f);

		m_flightTime = 1.0f;
		m_weHit = false;
		m_whereWeHit = target;
		SetReloading();
	}
}

bool cPatterns_MidTerm_2019_Weapon_Balistic::DidWeHit(glm::vec3& where)
{
	if (m_flightTime >= 0)
	{
		where = m_whereWeHit;
		if (m_weHit)
		{
			m_weHit = false;
			return true;
		}
		return m_weHit;
	}
	return false;
}

//   INFO6028 - Hack the balistics

 glm::vec3 aHitter(const glm::vec3 target, float damageRadius)
{
	 float farRadius = damageRadius + 1;
	 float randomx = randInRange(-farRadius, +farRadius);
	 float randomz = randInRange(-farRadius, +farRadius);
	 glm::vec3 where = target;
	 where.x += randomx;
	 where.z += randomz;
	 return where;
 }

void cPatterns_MidTerm_2019_Weapon_Balistic::Step(float deltatime)
{
	StepCommon(deltatime);			// Do common step work
	if (m_flightTime)
	{
		m_flightTime -= deltatime;
		if (m_flightTime < 0)
		{
			m_flightTime = 0;
			m_whereWeHit = aHitter(m_whereWeHit, GetDamageRadius());
			m_weHit = true;
		}
	}
}

bool cPatterns_MidTerm_2019_Weapon_Balistic::CanIShoot()
{
	return (!AmReloading() && (m_flightTime == 0));
}

