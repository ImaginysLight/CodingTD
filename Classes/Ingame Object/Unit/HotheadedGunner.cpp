#include "HotheadedGunner.h"

HotheadedGunner::HotheadedGunner(int line, bool isOwned, int unitId, int playerId)
{
	name = "Hotheaded Gunner";
	description = "A cheap robot with high defense.";
	goldCost = 50;
	levelRequired = 1;
	maxHealth = 500;
	currentHealth = maxHealth;
	baseAttack = 18;
	baseDefense = 75;
	baseMoveSpeed = 45;
	baseAttackSpeed = 40;
	range = 150;
	baseRegeneration = 1;

	upgradeName = "Hotheaded Gunner 2";
	upgradeGoldCost = 300;
	upgradeKnowledgeCost = 1;
	upgradeLevelRequired = 2;

	animationIndexOnTriggerAttack = 6;

	this->UpdateIngameInfo("Sprites/Hotheaded Gunner/attack/attack (1).png", unitId, playerId, isOwned, "Hotheaded Gunner", line);
}

HotheadedGunner::~HotheadedGunner()
{
}

