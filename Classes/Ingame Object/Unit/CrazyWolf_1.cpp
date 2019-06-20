#include "CrazyWolf_1.h"

CrazyWolf_1::CrazyWolf_1(int line, bool isOwned, int unitId, int playerId)
{
	name = "Crazy Wolf 1";
	description = "A crazy beast with great resillience.";
	goldCost = 150;
	levelRequired = 1;
	maxHealth = 500;
	currentHealth = maxHealth;
	baseAttack = 45;
	baseDefense = 25;
	baseMoveSpeed = 90;
	baseAttackSpeed = 36;
	range = 0;
	baseRegeneration = 5;

	upgradeName = "Crazy Wolf 2";
	upgradeGoldCost = 450;
	upgradeKnowledgeCost = 2;
	upgradeLevelRequired = 2;

	animationIndexOnTriggerAttack = 8;
	delayTimeAfterAttack = 0;

	this->UpdateIngameInfo("Sprites/Crazy Wolf/attack/attack (1).png", unitId, playerId, isOwned, "Crazy Wolf", line);
}

CrazyWolf_1::~CrazyWolf_1()
{
}

void CrazyWolf_1::Regeneration()
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

