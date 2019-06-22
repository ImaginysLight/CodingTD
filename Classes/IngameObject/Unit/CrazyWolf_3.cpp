#include "CrazyWolf_3.h"

CrazyWolf_3::CrazyWolf_3(int line, bool isOwned, int unitId, int playerId)
{
	name = "Crazy Wolf 3";
	description = "A crazy beast with great resillience.";
	goldCost = 150;
	levelRequired = 1;
	maxHealth = 360;
	currentHealth = maxHealth;
	baseAttack = 50;
	baseDefense = 100;
	baseMoveSpeed = 115;
	baseAttackSpeed = 45;
	range = 0;
	baseRegeneration = 10;


	animationIndexOnTriggerAttack = 8;
	delayTimeAfterAttack = 0;

	this->UpdateIngameInfo("Sprites/Crazy Wolf/attack/attack (1).png", unitId, playerId, isOwned, "Crazy Wolf", line);
}

CrazyWolf_3::~CrazyWolf_3()
{
}

void CrazyWolf_3::Regeneration()
{
	/*Berserker's Blood:
	Double amount of Regeneration when Health below 35 / 55 / 75 % .
	Tripple amount of Regeneration when Health below 0 / 20 / 50 % .
	Quadruplicate amount of Regeneration when Health below 0 / 10 / 25 % .*/
	int currentRegeneration = this->regeneration;
	if (currentHealth < maxHealth *0.25) {
		this->regeneration *= 4;
	}
	else if (currentHealth < maxHealth *0.5) {
		this->regeneration *= 3;
	}
	else if (currentHealth < maxHealth *.75) {
		this->regeneration *= 2;
	}
	BaseUnitClass::Regeneration();
	this->regeneration = currentRegeneration;
}

