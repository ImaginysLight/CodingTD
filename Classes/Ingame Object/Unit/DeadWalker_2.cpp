﻿#include "DeadWalker_2.h"

DeadWalker_2::DeadWalker_2(int line, bool isOwned, int unitId, int playerId)
{
	name = "Dead Walker 2";
	description = "A pretty zombie with decay aura.";
	goldCost = 120;
	levelRequired = 1;
	maxHealth = 640;
	currentHealth = maxHealth;
	baseAttack = 60;
	baseDefense = 50;
	baseMoveSpeed = 65;
	baseAttackSpeed = 30;
	range = 0;
	baseRegeneration = 3;

	upgradeName = "Dead Walker 3";
	upgradeGoldCost = 600;
	upgradeKnowledgeCost = 2;
	upgradeLevelRequired = 2;

	animationIndexOnTriggerAttack = 6;

	this->UpdateIngameInfo("Sprites/Dead Walker/attack/attack (1).png", unitId, playerId, isOwned, "Dead Walker", line);
}

DeadWalker_2::~DeadWalker_2()
{
}
//Rotten Aura: Decrease enemies Attack and Defense by 5 / 7.5 / 10% in 500 range around in all line. (last 5 seconds)
void DeadWalker_2::Regeneration()
{
	BaseUnitClass::Regeneration();

	//Tìm đối thủ quanh 500 range
	vector<BaseUnitClass*> targetList;
	for (auto target : BaseUnitClass::AllIngameUnit_Vector) {
		if (
			(this->isOwned != target->isOwned)						
			&& (target->isAlive && target->action != "Die")							
			&& (abs(target->root->getPositionX() - this->root->getPositionX()) < 500)
			)
			targetList.push_back(target);
	}
	//Add status
	for (auto target : targetList) {
		bool isAffected = false;
		for (int i = 0; i < target->statusReceive.size(); i++) {
			if (target->statusReceive[i].statusName.find("Rotten Aura") != std::string::npos) {
				isAffected = true;
				target->statusReceive[i].releaseStatusTime = Tool::currentIngameTime + 5;
			}
		}
		if (!isAffected) {
			target->ApplyStatus(StatusReceive("Rotten Aura - Defense", "Defense", 0.925, Tool::currentIngameTime + 5, 2));
			target->ApplyStatus(StatusReceive("Rotten Aura - Attack", "Attack", 0.925, Tool::currentIngameTime + 5, 2));
		}
	}
}

