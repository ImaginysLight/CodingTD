#include "FrostWyvern_1.h"

FrostWyvern_1::FrostWyvern_1(int line, bool isOwned, int unitId, int playerId)
{
	name = "Frost Wyvern 1";
	description = "It slows enemy on the line, can launch Frost Nova which pierce Defense to counter low defense unit.";
	goldCost = 150;
	levelRequired = 1;
	maxHealth = 300;
	currentHealth = maxHealth;
	baseAttack = 60;
	baseDefense = 50;
	baseMoveSpeed = 60;
	baseAttackSpeed = 20;
	range = 200;
	baseRegeneration = 2;

	upgradeName = "Frost Wyvern 2";
	upgradeGoldCost = 300;
	upgradeKnowledgeCost = 1;
	upgradeLevelRequired = 2;

	animationIndexOnTriggerAttack = 12;

	this->UpdateIngameInfo("Sprites/Frost Wyvern/attack/attack (1).png", unitId, playerId, isOwned, "Frost Wyvern", line);
}

FrostWyvern_1::~FrostWyvern_1()
{
}

void FrostWyvern_1::Attack(vector<BaseUnitClass*>& targets)
{
	if (this->snowballReady <= Tool::currentIngameTime && targets[0]->description != "Kingdom") {
		auto frostNova = new FrostNova(targets[0]->root->getPosition() + targets[0]->sprite->getBoundingBox().size/2, this->line, 60, "Frost Nova 1", Tool::currentIngameTime + 1, this->isOwned);
		this->snowballReady = Tool::currentIngameTime + 7;
	}
	BaseUnitClass::Attack(targets);
}

void FrostWyvern_1::Regeneration()
{
	BaseUnitClass::Regeneration();
	//The Presence of Ice: Slow all enemies on the line, decrease Move Speed by 10 / 15 / 20 and Attack Speed by 10 / 17 / 25%
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
				target->ApplyStatus(StatusReceive("The Presence of Ice - Move Speed", "MoveSpeed", -10, Tool::currentIngameTime + 2, 1));
				target->ApplyStatus(StatusReceive("The Presence of Ice - Attack Speed", "AttackSpeed", 0.9, Tool::currentIngameTime + 2, 2));
			}
		}
	}
}

