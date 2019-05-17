#include "WingedOrc_3.h"

WingedOrc_3::WingedOrc_3(int line, bool isOwned, int unitId, int playerId)
{
	name = "Winged Orc 3";
	description = "A short-ranged bird, useful for 'rat' Kingdom in early game, and become fucking annoyed for melee unit in late game.";
	goldCost = 125;
	levelRequired = 1;
	maxHealth = 400;
	currentHealth = maxHealth;
	baseAttack = 75;
	baseDefense = 75;
	baseMoveSpeed = 120;
	baseAttackSpeed = 32;
	range = 275;
	baseRegeneration = 5;


	delayTimeAfterAttack = 0.08;
	animationIndexOnTriggerAttack = 7;

	this->UpdateIngameInfo("Sprites/Winged Orc/attack/attack (1).png", unitId, playerId, isOwned, "Winged Orc", line);
}



WingedOrc_3::~WingedOrc_3()
{
}

//Deathwing: blows away everything on attack, knockback both itself and the enemy by 25 / 50 / 100 range
//if the enemy is a unit, bonus 75 damage if the enemy is a building.
void WingedOrc_3::Attack(vector<BaseUnitClass*>& targets)
{
	this->action = "Attack";
	auto animate = IngameObject::animate[this->animateName + "_attack"]->clone();
	animate->setDuration(60 / this->attackSpeed * (1 - this->delayTimeAfterAttack));
	this->sprite->runAction(Sequence::create(
		animate,
		DelayTime::create(delayTimeAfterAttack),
		CallFunc::create([&]() {	this->action = "Idle"; }),
		nullptr
	))->setFlags(1);

	auto delayShootTime = animate->getDuration() *((float)this->animationIndexOnTriggerAttack / animate->getAnimation()->getFrames().size());
	for (auto target : targets) {
		float damage = this->attack;
		//string animateName = this->animateName + "_explosion";
		string animateName = "_explosion"; // Không có sprite nên ai bắn cũng nổ như nhau
		float distance = abs(this->root->getPositionX() - target->root->getPositionX());
		float triggerTime = Tool::currentIngameTime + delayShootTime + distance * 0.002;
		if (target->description == "Kingdom") {
			target->damageReceive.push_back(DamageReceive(this->unitId, damage + 75, triggerTime, animateName, ""));
		}
		else {
			target->damageReceive.push_back(DamageReceive(this->unitId, damage, triggerTime, animateName, ""));
			if (target->isOwned) {
				this->root->runAction(MoveBy::create(0.25, Vec2(100, 0)));
				target->root->runAction(MoveBy::create(0.25, Vec2(-100, 0)));
			}
			else {
				this->root->runAction(MoveBy::create(0.25, Vec2(-100, 0)));
				target->root->runAction(MoveBy::create(0.25, Vec2(100, 0)));
			}
		}
	}
}

