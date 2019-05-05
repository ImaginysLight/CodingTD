#include "UFODriver.h"

UFODriver::UFODriver(int line, bool isOwned, int unitId, int playerId)
{
	name = "UFO Driver";
	description = "An absent-minded driver, sometimes pressing the wrong button";
	goldCost = 50;
	energyCost = 0;
	levelRequired = 1;
	maxHealth = 600;
	currentHealth = maxHealth;
	baseAttack = 84;
	baseDefense = 0;
	baseMoveSpeed = 7;
	baseAttackSpeed = 25;
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

//Wrong Button: each 5 / 4 / 4 / 3th attack, the driver presses the wrong button, causing the next attack to
//increase damage by 1.5 / 1.5 / 2.5 / 2.5, but the UFO runs of energy in 1 / 1.25 / 1.5 / 1 second.
void UFODriver::Attack(vector<BaseUnitClass*>& targets)
{
	this->numOfAttack++;
	float currentAttack = this->attack;
	if (numOfAttack == 5) {
		numOfAttack = 0;
		this->attack *= 1.5;
		auto label = Tool::CreateLabel("Wrong Button");
		label->runAction(Sequence::create(MoveBy::create(1, Vec2(0, 40)), RemoveSelf::create(), nullptr));
		if (this->isOwned) label->setRotation3D(Vec3(0, 180, 0));
		this->root->addChild(label);
	}

	BaseUnitClass::Attack(targets);

	this->attack = currentAttack;
	if (numOfAttack == 0) {
		this->hardEffect.push_back(HardEffect("Stun", Tool::currentIngameTime, Tool::currentIngameTime + 1));
	}
}
