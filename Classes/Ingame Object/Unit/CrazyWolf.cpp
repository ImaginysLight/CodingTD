#include "CrazyWolf.h"

CrazyWolf::CrazyWolf(int line, bool isOwned, int unitId, int playerId)
{
	name = "Crazy Wolf";
	description = "A beast with great recover ability";
	goldCost = 75;
	energyCost = 0;
	levelRequired = 2;
	maxHealth = 350;
	currentHealth = maxHealth;
	baseAttack = 80;
	baseDefense = 50;
	baseMoveSpeed = 9;
	baseAttackSpeed = 30;
	range = 100;
	baseRegeneration = 3;

	upgradeName = "Crazy Wolf 2";
	upgradeGoldCost = 200;
	upgradeEnergyCost = 1;
	upgradeLevelRequired = 2;

	animationIndexOnTriggerAttack = 8;

	this->UpdateIngameInfo("Sprites/Crazy Wolf/attack/attack (1).png", unitId, playerId, isOwned, "Crazy Wolf", line);
}

CrazyWolf::~CrazyWolf()
{
}

void CrazyWolf::Regeneration()
{
	int currentRegeneration = this->regeneration;
	if (currentHealth < maxHealth / 4) {
		this->regeneration *= 2;
	}
	BaseUnitClass::Regeneration();
	this->regeneration = currentRegeneration;
}

