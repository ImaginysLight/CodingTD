#include "UFODriver_2.h"

UFODriver_2::UFODriver_2(int line, bool isOwned, int unitId, int playerId)
{
	name = "UFO Driver 2";
	description = "An absent-minded driver, sometimes pressing the wrong button.";
	goldCost = 60;
	levelRequired = 1;
	maxHealth = 320;
	currentHealth = maxHealth;
	baseAttack = 64;
	baseDefense = 25;
	baseMoveSpeed = 60;
	baseAttackSpeed = 28;
	range = 350;
	baseRegeneration = 2;

	upgradeName = "UFO Driver 3";
	upgradeGoldCost = 400;
	upgradeEnergyCost = 1;
	upgradeLevelRequired = 2;

	animationIndexOnTriggerAttack = 5;

	this->UpdateIngameInfo("Sprites/UFO Driver/attack/attack (1).png", unitId, playerId, isOwned, "UFO Driver", line);
}

UFODriver_2::~UFODriver_2()
{
}

//Wrong Button : each 6 / 5 / 4 / 3th attack, the driver presses the wrong button, causing the next attack
//to increase damage by 1.4 / 2.4 / 3.1 / 4.6, but the UFO runs of energy in 6 / 4 / 2 / 6 second.
void UFODriver_2::Attack(vector<BaseUnitClass*>& targets)
{
	this->numOfAttack++;
	float currentAttack = this->attack;
	if (numOfAttack == 5) {
		numOfAttack = 0;
		this->attack *= 2.4;
		auto label = Tool::CreateLabel("Wrong Button");
		label->runAction(Sequence::create(MoveBy::create(1, Vec2(0, 40)), RemoveSelf::create(), nullptr));
		if (this->isOwned) label->setRotation3D(Vec3(0, 180, 0));
		this->root->addChild(label);
	}

	BaseUnitClass::Attack(targets);

	this->attack = currentAttack;
	if (numOfAttack == 0) {
		this->hardEffect.push_back(HardEffect("Stun", Tool::currentIngameTime, Tool::currentIngameTime + 4));
	}
}
