#include "ElementalAlien.h"

ElementalAlien::ElementalAlien(int line, bool isOwned, int unitId, int playerId)
{
	name = "Elemental Alien";
	description = "Its power depend on your element.";
	goldCost = 100;
	levelRequired = 1;
	maxHealth = 400;
	currentHealth = maxHealth;
	baseAttack = 50;
	baseDefense = 50;
	baseMoveSpeed = 70;
	baseAttackSpeed = 30;
	range = 0;
	baseRegeneration = 1;

	upgradeName = "Elemental Alien 2";
	upgradeGoldCost = 200;
	upgradeKnowledgeCost = 1;
	upgradeLevelRequired = 2;

	animationIndexOnTriggerAttack = 14;

	this->UpdateIngameInfo("Sprites/Elemental Alien/attack/attack (1).png", unitId, playerId, isOwned, "Elemental Alien", line);

	this->element = this->isOwned ? Tool::currentPlayer->elementName : Tool::opponentPlayer->elementName;
	if (element == "Ice") {
		this->sprite->setColor(IngameObject::elementColor["Ice"]);
	}
	if (element  == "Fire") {
		this->sprite->setColor(IngameObject::elementColor["Fire"]);
	}
	if (element == "Nature") {
		this->sprite->setColor(IngameObject::elementColor["Nature"]);
	}
	
}

ElementalAlien::~ElementalAlien()
{
}

void ElementalAlien::Attack(vector<BaseUnitClass*>& targets)
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
		if (this->element == "Ice") {
			damage += target->attack * 0.13;
		}
		else if (this->element == "Fire") {
			damage += target->baseRegeneration * 3;
			bool isAffected = false;
			for (int i = 0; i < target->statusReceive.size(); i++) {
				if (target->statusReceive[i].statusName == "Unhealable") {
					isAffected = true;
					target->statusReceive[i].releaseStatusTime = Tool::currentIngameTime + 1;
					break;
				}
			}
			if(!isAffected)
				target->ApplyStatus(StatusReceive("Unhealable", "Regeneration", 0, Tool::currentIngameTime + 1, 5));
		}
		else if (this->element == "Nature") {
			this->currentHealth += (target->maxHealth *0.04 * (90 / target->moveSpeed));
			if (this->currentHealth > this->maxHealth) {
				this->currentHealth = this->maxHealth;
			}
		}
		target->damageReceive.push_back(DamageReceive(this->unitId, damage, triggerTime, animateName, ""));
	}
}

//Icy Claws: dealt bonus damage as 13 / 20 / 27 / 35% target's Attack on attack. 
//Fiery Claws: dealt bonus damage as 3 / 3.8 / 4.5 / 5* target's base Regeneration and make them unhealable for 1 / 2 / 3 / 4 seconds on attack.
//Vitality Claws : lifesteal 4 / 4.8 / 5.5 / 6 % target's Max Health multiply (90 / 100 / 110 / 120 / Move Speed) on attack.