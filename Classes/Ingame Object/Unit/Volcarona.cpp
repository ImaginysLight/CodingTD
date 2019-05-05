#include "Volcarona.h"

Volcarona::Volcarona(int line, bool isOwned, int unitId, int playerId)
{
	name = "Volcarona";
	description = "Ambassador of Fire";
	goldCost = 100;
	energyCost = 1;
	levelRequired = 2;
	maxHealth = 1000;
	currentHealth = maxHealth;
	baseAttack = 120;
	baseDefense = 0;
	baseMoveSpeed = 10;
	baseAttackSpeed = 30;
	range = 300;
	baseRegeneration = 4;

	upgradeName = "Volcarona 2";
	upgradeGoldCost = 350;
	upgradeEnergyCost = 1;
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
	//Fire Armor: buff an ally with Fire Armor, reflect 15 / 20% damage to whoever attacks them. (Duration: 10s, Cooldown: 10s)
	if (this->fireArmorReady < Tool::currentIngameTime) {
		for (auto target : BaseUnitClass::AllIngameUnit_Vector) {
			if (
				target->isOwned == this->isOwned
				&& target->description != "Kingdom"
				&& abs(target->root->getPositionX() - this->root->getPositionX()) < this->range
				) {
				auto sp = Sprite::create("Sprites/Fire Armor.png");
				Tool::setNodeSize(sp, 75, 75);
				sp->setRotation3D(Vec3(90, 0, 0));
				sp->setPosition(this->sprite->getBoundingBox().size / 2);
				sp->runAction(RepeatForever::create(RotateBy::create(1, Vec3(0,180,0))));
				sp->setName("FireArmor");
				target->sprite->addChild(sp,1);
				new FireArmor(target->unitId, 15, Tool::currentIngameTime + 10);
				this->fireArmorReady = Tool::currentIngameTime + 10;
				break;
			}
		}
		
	}

	//The Presence of Fire: burn all non-Fire-Special unit on the line, dealing 2 dps and decrease Regeneration by 20%
	for (auto target : BaseUnitClass::AllIngameUnit_Vector) {
		if (
			target->isOwned != this->isOwned
			&& target->line == this->line
			&& target->description != "Kingdom"
			) {
			//dealing 2 dps to non-Fire-Special unit
			if (target->name.find("Volcarona") == std::string::npos && target->name.find("Enraged Ursa") == std::string::npos) {
				target->currentHealth -= 2;
			}

			//decrease Regeneration by 20%
			bool isAffected = false;
			for (int i = 0; i < target->statusReceive.size(); i++) {
				if (target->statusReceive[i].statusName == "The Presence of Fire") {
					target->statusReceive[i].releaseStatusTime = Tool::currentIngameTime + 2;
					isAffected = true;
				}
			}
			if (!isAffected) {
				target->ApplyStatus(StatusReceive("The Presence of Fire", "Regeneration", 0.8, Tool::currentIngameTime + 2, 2));
				
			}
		}
	}
}

