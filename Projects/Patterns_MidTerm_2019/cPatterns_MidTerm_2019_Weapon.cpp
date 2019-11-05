#include "cPatterns_MidTerm_2019_Weapon.h"

cPatterns_MidTerm_2019_Weapon::cPatterns_MidTerm_2019_Weapon()
	: m_DamageRadius(0.0f)
	, m_reloadRate(0.0f)
	, m_HasTravelTime(false)
	, m_damagePerShotPercentage(0.0f)
	, m_CurrentReloadingWait(0.0f)
{

}

cPatterns_MidTerm_2019_Weapon::~cPatterns_MidTerm_2019_Weapon()
{
}

float cPatterns_MidTerm_2019_Weapon::GetDamagePerShotPercentage()
{
	return m_damagePerShotPercentage;
}
float cPatterns_MidTerm_2019_Weapon::GetReloadRate()
{
	return m_reloadRate;
}

bool cPatterns_MidTerm_2019_Weapon::HasTravelTime()
{
	return m_HasTravelTime;
}

float cPatterns_MidTerm_2019_Weapon::GetDamageRadius()
{
	return m_DamageRadius;
}

void cPatterns_MidTerm_2019_Weapon::SetReloading()
{
	m_CurrentReloadingWait = m_reloadRate;
}

bool cPatterns_MidTerm_2019_Weapon::AmReloading()
{
	return (m_CurrentReloadingWait >= 0.0f);
}

void cPatterns_MidTerm_2019_Weapon::StepCommon(float deltatime)
{
	if (m_CurrentReloadingWait >= 0.0f)
		m_CurrentReloadingWait -= deltatime;
}
