#include "CrazyWolf.h"

CrazyWolf::CrazyWolf(int line, bool isOwned, int unitId, int playerId)
{
	name = "Crazy Wolf";
	description = "A crazy beast with great resillience.";
	goldCost = 100;
	levelRequired = 2;
	maxHealth = 300;
	currentHealth = maxHealth;
	baseAttack = 60;
	baseDefense = 50;
	baseMoveSpeed = 90;
	baseAttackSpeed = 30;
	range = 0;
	baseRegeneration = 5;

	upgradeName = "Crazy Wolf 2";
	upgradeGoldCost = 300;
	upgradeEnergyCost = 1;
	upgradeLevelRequired = 2;

	animationIndexOnTriggerAttack = 8;
	delayTimeAfterAttack = 0;

	this->UpdateIngameInfo("Sprites/Crazy Wolf/attack/attack (1).png", unitId, playerId, isOwned, "Crazy Wolf", line);
}

CrazyWolf::~CrazyWolf()
{
}

void CrazyWolf::Regeneration()
{
	/*Berserker's Blood: 
	Double amount of Regeneration when Health below 35 / 55 / 75 % .
	Tripple amount of Regeneration when Health below 0 / 20 / 50 % .
	Quadruplicate amount of Regeneration when Health below 0 / 10 / 25 % .*/

	int currentRegeneration = this->regeneration;
	if (currentHealth < maxHealth *0.35) {
		this->regeneration *= 2;
	}
	BaseUnitClass::Regeneration();
	this->regeneration = currentRegeneration;
}

