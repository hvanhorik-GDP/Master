#include "cPatterns_MidTerm_2019_Weapon_LineOfSight.h"
#include "DebugRenderer/cDebugRenderer.h"


extern cDebugRenderer* gDebugRenderer;


cPatterns_MidTerm_2019_Weapon_LineOfSight::cPatterns_MidTerm_2019_Weapon_LineOfSight()
	: m_weHit(false)
	, m_whereWeHit(glm::vec3(0.0f, 0.0f, 0.0f))

{
}

cPatterns_MidTerm_2019_Weapon_LineOfSight::~cPatterns_MidTerm_2019_Weapon_LineOfSight()
{
}

bool cPatterns_MidTerm_2019_Weapon_LineOfSight::IsBalistic()
{
	return false;
}

void cPatterns_MidTerm_2019_Weapon_LineOfSight::Shoot(const glm::vec3& source, const glm::vec3& target)
{
	if (!AmReloading())
	{
		glm::vec3 colour(1.0f, 1.0f, 1.0f);
		if (GetDamagePerShotPercentage() == 0.02f)	// Bullet is different colour
			colour.g = 0.0f;
		glm::vec3 start = source;
		glm::vec3 end = target;
		start.y += 5;
		end.y += 5;
		gDebugRenderer->addLine(start, end, colour, 0.2f);

		m_weHit = true;
		m_whereWeHit = target;
		SetReloading();
	}
}

bool cPatterns_MidTerm_2019_Weapon_LineOfSight::DidWeHit(glm::vec3& where)
{
	where = m_whereWeHit;
	if (m_weHit)
	{
		m_weHit = false;
		return true;
	}
	return m_weHit;
}

void cPatterns_MidTerm_2019_Weapon_LineOfSight::Step(float deltatime)
{
	StepCommon(deltatime);			// Do common step work
}

bool cPatterns_MidTerm_2019_Weapon_LineOfSight::CanIShoot()
{
	return !AmReloading();
}