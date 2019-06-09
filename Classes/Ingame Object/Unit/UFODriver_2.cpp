#include "UFODriver_2.h"

UFODriver_2::UFODriver_2(int line, bool isOwned, int unitId, int playerId)
{
	name = "UFO Driver 2";
	description = "An absent-minded driver, sometimes pressing the wrong button.";
	goldCost = 75;
	levelRequired = 1;
	maxHealth = 180;
	currentHealth = maxHealth;
	baseAttack = 45;
	baseDefense = 25;
	baseMoveSpeed = 60;
	baseAttackSpeed = 30;
	range = 350;
	baseRegeneration = 2;

	upgradeName = "UFO Driver 3";
	upgradeGoldCost = 300;
	upgradeKnowledgeCost = 1;
	upgradeLevelRequired = 2;

	animationIndexOnTriggerAttack = 5;

	this->UpdateIngameInfo("Sprites/UFO Driver/attack/attack (1).png", unitId, playerId, isOwned, "UFO Driver", line);
}

UFODriver_2::~UFODriver_2()
{
}

//each 5 / 4 / 4 / 3th attack, the driver presses the wrong button, 
//causing the next attack to increase damage by 2 / 2.4 / 2.8 / 3, but the UFO runs of energy in 3.5 / 2.5 / 2 / 2 second.
void UFODriver_2::Attack(vector<BaseUnitClass*>& targets)
{
	this->numOfAttack++;
	float currentAttack = this->attack;
	if (numOfAttack == 4) {
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
		this->hardEffect.push_back(HardEffect("Stun", Tool::currentIngameTime, Tool::currentIngameTime + 2.5));
	}
}
