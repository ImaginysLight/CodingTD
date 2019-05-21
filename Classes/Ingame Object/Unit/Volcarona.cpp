﻿#include "Volcarona.h"

Volcarona::Volcarona(int line, bool isOwned, int unitId, int playerId)
{
	name = "Volcarona";
	description = "Squishy ranger but high output damage and Fire Armor buff.";
	goldCost = 120;
	levelRequired = 2;
	maxHealth = 448;
	currentHealth = maxHealth;
	baseAttack = 100;
	baseDefense = 25;
	baseMoveSpeed = 65;
	baseAttackSpeed = 30;
	range = 300;
	baseRegeneration = 3;

	upgradeName = "Volcarona 2";
	upgradeGoldCost = 700;
	upgradeKnowledgeCost = 1;
	upgradeLevelRequired = 3;

	animationIndexOnTriggerAttack = 5;

	this->UpdateIngameInfo("Sprites/Volcarona/attack/attack (1).png", unitId, playerId, isOwned, "Volcarona", line);
}

Volcarona::~Volcarona()
{
}

void Volcarona::Regeneration()
{
	BaseUnitClass::Regeneration();
	//Fire Armor: buff an ally with Fire Armor, reflect 15 / 20% damage to whoever attacks them. (Duration: 9s, Cooldown: 10s)
	if (this->fireArmorReady < Tool::currentIngameTime) {
		//Tạo sprite
		auto sp = Sprite::create("Sprites/Fire Armor.png");
		Tool::setNodeSize(sp, 75, 75);
		sp->setRotation3D(Vec3(90, 0, 0));
		sp->setPosition(this->sprite->getBoundingBox().size / 2);
		sp->runAction(RepeatForever::create(RotateBy::create(1, Vec3(0, 180, 0))));
		sp->setName("FireArmor");
		//Kiểm tra xem có ai ngoài bản thân nó để buff ko
		for (auto target : BaseUnitClass::AllIngameUnit_Vector) {
			if (
				target->unitId != this->unitId
				&& target->isOwned == this->isOwned
				&& target->description != "Kingdom"
				&& abs(target->root->getPositionX() - this->root->getPositionX()) < this->range
				) {
				target->sprite->addChild(sp, 1);
				new FireArmor(target->unitId, 15, Tool::currentIngameTime + 9);
				this->fireArmorReady = Tool::currentIngameTime + 10;
				break;
			}
		}
		//Nếu ko thì tự buff cho mình
		if (this->fireArmorReady < Tool::currentIngameTime) {
			this->sprite->addChild(sp, 1);
			new FireArmor(this->unitId, 20, Tool::currentIngameTime + 9);
			this->fireArmorReady = Tool::currentIngameTime + 10;
		}
	}

	//The Presence of Fire : burn all enemies on the line, dealing 5 / 7 pure dps and decrease Regeneration by 30 / 35 % .
	for (auto target : BaseUnitClass::AllIngameUnit_Vector) {
		if (
			target->isOwned != this->isOwned
			&& target->line == this->line
			&& target->description != "Kingdom"
			) {
			target->currentHealth -= 5;

			bool isAffected = false;
			for (int i = 0; i < target->statusReceive.size(); i++) {
				if (target->statusReceive[i].statusName == "The Presence of Fire") {
					target->statusReceive[i].releaseStatusTime = Tool::currentIngameTime + 2;
					isAffected = true;
				}
			}
			if (!isAffected) {
				target->ApplyStatus(StatusReceive("The Presence of Fire", "Regeneration", 0.7, Tool::currentIngameTime + 2, 2));
			}
		}
	}
}

