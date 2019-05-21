#include "HotheadedGunner_2.h"

HotheadedGunner_2::HotheadedGunner_2(int line, bool isOwned, int unitId, int playerId)
{
	name = "Hotheaded Gunner 2";
	description = "A cheap robot with high defense.";
	goldCost = 50;
	levelRequired = 1;
	maxHealth = 400;
	currentHealth = maxHealth;
	baseAttack = 20;
	baseDefense = 110;
	baseMoveSpeed = 55;
	baseAttackSpeed = 45;
	range = 200;
	baseRegeneration = 2;

	upgradeName = "Hotheaded Gunner 3";
	upgradeGoldCost = 650;
	upgradeKnowledgeCost = 1;
	upgradeLevelRequired = 3;

	animationIndexOnTriggerAttack = 6;

	this->UpdateIngameInfo("Sprites/Hotheaded Gunner/attack/attack (1).png", unitId, playerId, isOwned, "Hotheaded Gunner", line);
}

HotheadedGunner_2::~HotheadedGunner_2()
{
}

