#include "CrazyWolf_2.h"

CrazyWolf_2::CrazyWolf_2(int line, bool isOwned, int unitId, int playerId)
{
	name = "Crazy Wolf 2";
	description = "A crazy beast with great resillience.";
	goldCost = 150;
	levelRequired = 1;
	maxHealth = 400;
	currentHealth = maxHealth;
	baseAttack = 50;
	baseDefense = 70;
	baseMoveSpeed = 100;
	baseAttackSpeed = 40;
	range = 0;
	baseRegeneration = 7;

	upgradeName = "Crazy Wolf 3";
	upgradeGoldCost = 650;
	upgradeKnowledgeCost = 2;
	upgradeLevelRequired = 3;

	animationIndexOnTriggerAttack = 8;
	delayTimeAfterAttack = 0;

	this->UpdateIngameInfo("Sprites/Crazy Wolf/attack/attack (1).png", unitId, playerId, isOwned, "Crazy Wolf", line);
}

CrazyWolf_2::~CrazyWolf_2()
{
}

void CrazyWolf_2::Regeneration()
{
	/*Berserker's Blood:
	Double amount of Regeneration when Health below 35 / 55 / 75 % .
	Tripple amount of Regeneration when Health below 0 / 20 / 50 % .
	Quadruplicate amount of Regeneration when Health below 0 / 10 / 25 % .*/
	int currentRegeneration = this->regeneration;
	if (currentHealth < maxHealth*0.1) {
		this->regeneration *= 4;
	}
	else if (currentHealth < maxHealth* 0.2) {
		this->regeneration *= 3;
	}
	else if (currentHealth < maxHealth *0.55) {
		this->regeneration *= 2;
	}
	BaseUnitClass::Regeneration();
	this->regeneration = currentRegeneration;
}

