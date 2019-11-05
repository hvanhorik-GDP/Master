#pragma once

#include "iPatterns_MidTerm_2019_Weapon.h"

// INFO6044 - Weapon Common code

class cPatterns_MidTerm_2019_Weapon :
	public iPatterns_MidTerm_2019_Weapon
{
protected:
	friend class cPatterns_MidTerm_2019_World_impl;
	cPatterns_MidTerm_2019_Weapon();
	virtual ~cPatterns_MidTerm_2019_Weapon();

	virtual bool IsBalistic() = 0;
	virtual void Shoot(const glm::vec3& source, const glm::vec3& target) = 0;
	virtual bool CanIShoot() = 0;
	virtual void Step(float deltatime) = 0;
	virtual bool DidWeHit(glm::vec3& where) = 0;

	void StepCommon(float deltatime);
	float GetDamagePerShotPercentage();
	float GetReloadRate();
	bool HasTravelTime();
	float GetDamageRadius();

	void SetReloading();
	bool AmReloading();
private:

	float m_damagePerShotPercentage;
	float m_reloadRate;
	bool m_HasTravelTime;
	float m_DamageRadius;

	float m_CurrentReloadingWait;
};

