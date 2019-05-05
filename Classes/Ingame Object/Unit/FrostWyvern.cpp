#include "FrostWyvern.h"

FrostWyvern::FrostWyvern(int line, bool isOwned, int unitId, int playerId)
{
	name = "Frost Wyvern";
	description = "Ambassador of Ice";
	goldCost = 75;
	energyCost = 1;
	levelRequired = 1;
	maxHealth = 600;
	currentHealth = maxHealth;
	baseAttack = 90;
	baseDefense = 0;
	baseMoveSpeed = 6;
	baseAttackSpeed = 20;
	range = 300;
	baseRegeneration = 2;

	upgradeName = "Frost Wyvern 2";
	upgradeGoldCost = 275;
	upgradeEnergyCost = 1;
	upgradeLevelRequired = 2;

	animationIndexOnTriggerAttack = 12;

	this->UpdateIngameInfo("Sprites/Frost Wyvern/attack/attack (1).png", unitId, playerId, isOwned, "Frost Wyvern", line);
}

FrostWyvern::~FrostWyvern()
{
}

void FrostWyvern::Attack(vector<BaseUnitClass*>& targets)
{
	if (this->snowballReady <= Tool::currentIngameTime) {
		auto frostNova = new FrostNova(targets[0]->root->getPosition(), this->line, 50, Tool::currentIngameTime + 1, this->isOwned);
		this->snowballReady = Tool::currentIngameTime + 7;
	}
	BaseUnitClass::Attack(targets);
}

void FrostWyvern::Regeneration()
{
	BaseUnitClass::Regeneration();
	//The Presence of Ice: Slow all enemies on the line, decrease Move Speed by 1 and Attack Speed by 10%
	for (auto target : BaseUnitClass::AllIngameUnit_Vector) {
		if (
			target->isOwned != this->isOwned 
			&& target->line == this->line
			&& target->description != "Kingdom"
			) {
			bool isAffected = false;
			for (int i = 0; i < target->statusReceive.size(); i++) {
				if (target->statusReceive[i].statusName.find("The Presence of Ice") != std::string::npos) {
					target->statusReceive[i].releaseStatusTime = Tool::currentIngameTime + 2;
					isAffected = true;
				}
			}
			if (!isAffected) {
				target->ApplyStatus(StatusReceive("The Presence of Ice - Move Speed", "MoveSpeed", -1, Tool::currentIngameTime + 2, 1));
				target->ApplyStatus(StatusReceive("The Presence of Ice - Attack Speed", "AttackSpeed", 0.9, Tool::currentIngameTime + 2, 2));
			}
		}
	}
}

