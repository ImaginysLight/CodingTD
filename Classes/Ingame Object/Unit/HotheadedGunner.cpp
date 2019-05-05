#include "HotheadedGunner.h"

HotheadedGunner::HotheadedGunner(int line, bool isOwned, int unitId, int playerId)
{
	name = "Hotheaded Gunner";
	description = "Tanky robot with short range";
	goldCost = 50;
	energyCost = 0;
	levelRequired = 1;
	maxHealth = 350;
	currentHealth = maxHealth;
	baseAttack = 30;
	baseDefense = 150;
	baseMoveSpeed = 6;
	baseAttackSpeed = 40;
	range = 250;
	baseRegeneration = 1;

	upgradeName = "Hotheaded Gunner 2";
	upgradeGoldCost = 250;
	upgradeEnergyCost = 1;
	upgradeLevelRequired = 2;

	animationIndexOnTriggerAttack = 6;

	this->UpdateIngameInfo("Sprites/Hotheaded Gunner/attack/attack (1).png", unitId, playerId, isOwned, "Hotheaded Gunner", line);
}

HotheadedGunner::~HotheadedGunner()
{
}

