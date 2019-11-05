#include "cPatterns_MidTerm_2019_Robot.h"
#include "cPatterns_MidTerm_2019_World.h"

cPatterns_MidTerm_2019_Robot::cPatterns_MidTerm_2019_Robot()
	: m_Weapon(NULL)
	, m_location(glm::vec3(0.0f, 0.0f, 0.0f))
	, m_Model(NULL)
	, m_Box(NULL)
	, m_life(100)
	, m_TeleportCountdownTimer(0)
{
}

cPatterns_MidTerm_2019_Robot::~cPatterns_MidTerm_2019_Robot()
{
}

glm::vec3 cPatterns_MidTerm_2019_Robot::GetLocation()
{
	return m_location;
}

void cPatterns_MidTerm_2019_Robot::Step(float deltatime)
{
	// We are dead
	if (m_life <= 0)
		return;
	assert(m_Weapon);

	if (m_TeleportCountdownTimer > 0)
	{
		m_TeleportCountdownTimer -= deltatime;
		return;
	}
	m_TeleportCountdownTimer = 0;

	if (m_Weapon->CanIShoot())
	{
		cPatterns_MidTerm_2019_World world;
		bool lineOfSight = !m_Weapon->IsBalistic();
		bool isLineOfSight;
		auto target = world.FindClosetRobot(this, lineOfSight, isLineOfSight);
		// Nothing to see so teleport me
		// hack hack
		if (target)
		{
			m_Weapon->Shoot(this->GetLocation(), target->GetLocation());
		}
		else
		{
			world.TeleportRobot(this);
			// A timer after teleportation to recover
			m_TeleportCountdownTimer = 2.05f;
		}
	}
}
