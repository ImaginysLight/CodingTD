#include "UFODriver.h"

UFODriver::UFODriver(int line, bool isOwned, int unitId, int playerId)
{
	name = "UFO Driver";
	description = "An absent-minded driver, sometimes pressing the wrong button.";
	goldCost = 60;
	levelRequired = 1;
	maxHealth = 200;
	currentHealth = maxHealth;
	baseAttack = 81;
	baseDefense = 50;
	baseMoveSpeed = 55;
	baseAttackSpeed = 20;
	range = 300;
	baseRegeneration = 1;

	upgradeName = "UFO Driver 2";
	upgradeGoldCost = 200;
	upgradeEnergyCost = 1;
	upgradeLevelRequired = 1;

	animationIndexOnTriggerAttack = 5;

	this->UpdateIngameInfo("Sprites/UFO Driver/attack/attack (1).png", unitId, playerId, isOwned, "UFO Driver", line);
}

UFODriver::~UFODriver()
{
}

//Wrong Button : each 6 / 5 / 4 / 3th attack, the driver presses the wrong button, causing the next attack
//to increase damage by 1.4 / 2.4 / 3.1 / 4.6, but the UFO runs of energy in 6 / 4 / 2 / 6 second.
void UFODriver::Attack(vector<BaseUnitClass*>& targets)
{
	this->numOfAttack++;
	float currentAttack = this->attack;
	if (numOfAttack == 6) {
		numOfAttack = 0;
		this->attack *= 1.4;
		auto label = Tool::CreateLabel("Wrong Button");
		label->runAction(Sequence::create(MoveBy::create(1, Vec2(0, 40)), RemoveSelf::create(), nullptr));
		if (this->isOwned) label->setRotation3D(Vec3(0, 180, 0));
		this->root->addChild(label);
	}

	BaseUnitClass::Attack(targets);

	this->attack = currentAttack;
	if (numOfAttack == 0) {
		this->hardEffect.push_back(HardEffect("Stun", Tool::currentIngameTime, Tool::currentIngameTime + 6));
	}
}
