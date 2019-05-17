#include "HotheadedGunner_3.h"

HotheadedGunner_3::HotheadedGunner_3(int line, bool isOwned, int unitId, int playerId)
{
	name = "Hotheaded Gunner 3";
	description = "A cheap robot with high defense.";
	goldCost = 50;
	levelRequired = 1;
	maxHealth = 350;
	currentHealth = maxHealth;
	baseAttack = 24;
	baseDefense = 150;
	baseMoveSpeed = 60;
	baseAttackSpeed = 45;
	range = 250;
	baseRegeneration = 3;

	animationIndexOnTriggerAttack = 6;

	this->UpdateIngameInfo("Sprites/Hotheaded Gunner/attack/attack (1).png", unitId, playerId, isOwned, "Hotheaded Gunner", line);
}

HotheadedGunner_3::~HotheadedGunner_3()
{
}

