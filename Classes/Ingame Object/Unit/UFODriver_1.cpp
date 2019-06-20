#include "UFODriver_1.h"

UFODriver_1::UFODriver_1(int line, bool isOwned, int unitId, int playerId)
{
	name = "UFO Driver 1";
	description = "An absent-minded driver, sometimes pressing the wrong button.";
	goldCost = 100;
	levelRequired = 1;
	maxHealth = 160;
	currentHealth = maxHealth;
	baseAttack = 45;
	baseDefense = 25;
	baseMoveSpeed = 55;
	baseAttackSpeed = 28;
	range = 300;
	baseRegeneration = 1;

	upgradeName = "UFO Driver 2";
	upgradeGoldCost = 200;
	upgradeKnowledgeCost = 1;
	upgradeLevelRequired = 1;

	animationIndexOnTriggerAttack = 5;

	this->UpdateIngameInfo("Sprites/UFO Driver/attack/attack (1).png", unitId, playerId, isOwned, "UFO Driver", line);
}

UFODriver_1::~UFODriver_1()
{
}

//each 5 / 4 / 4 / 3th attack, the driver presses the wrong button, 
//causing the next attack to increase damage by 2 / 2.4 / 2.8 / 3, but the UFO runs of energy in 3.5 / 2.5 / 2 / 2 second.
void UFODriver_1::Attack(vector<BaseUnitClass*>& targets)
{
	this->numOfAttack++;
	float currentAttack = this->attack;
	if (numOfAttack == 5) {
		numOfAttack = 0;
		this->attack *= 2;
		auto label = Tool::CreateLabel("Wrong Button");
		label->runAction(Sequence::create(MoveBy::create(1, Vec2(0, 40)), RemoveSelf::create(), nullptr));
		if (this->isOwned) label->setRotation3D(Vec3(0, 180, 0));
		this->root->addChild(label);
	}

	BaseUnitClass::Attack(targets);

	this->attack = currentAttack;
	if (numOfAttack == 0) {
		this->hardEffect.push_back(HardEffect("Stun", Tool::currentIngameTime, Tool::currentIngameTime + 3.5));
	}
}
