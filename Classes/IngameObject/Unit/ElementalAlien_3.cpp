#include "ElementalAlien_3.h"

ElementalAlien_3::ElementalAlien_3(int line, bool isOwned, int unitId, int playerId)
{
	name = "Elemental Alien 3";
	description = "Its power depend on your element.";
	goldCost = 175;
	levelRequired = 1;
	maxHealth = 450;
	currentHealth = maxHealth;
	baseAttack = 60;
	baseDefense = 50;
	baseMoveSpeed = 90;
	baseAttackSpeed = 42;
	range = 0;
	baseRegeneration = 3;

	upgradeName = "Elemental Alien 4";
	upgradeGoldCost = 425;
	upgradeKnowledgeCost = 2;
	upgradeLevelRequired = 2;

	animationIndexOnTriggerAttack = 14;

	this->UpdateIngameInfo("Sprites/Elemental Alien/attack/attack (1).png", unitId, playerId, isOwned, "Elemental Alien", line);

	this->element = this->isOwned ? Player::currentPlayer->elementName : Player::opponentPlayer->elementName;
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

ElementalAlien_3::~ElementalAlien_3()
{
}

void ElementalAlien_3::Attack(vector<BaseUnitClass*>& targets)
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
		string animateName = ""; // Không có sprite nên ai bắn cũng nổ như nhau
		float distance = abs(this->root->getPositionX() - target->root->getPositionX());
		float triggerTime = Tool::currentIngameTime + delayShootTime + distance * 0.002;
		if (this->element == "Ice") {
			damage += target->attack * 0.27;
		}
		else if (this->element == "Fire") {
			damage += target->baseRegeneration * 4.5;
			bool isAffected = false;
			for (int i = 0; i < target->statusReceive.size(); i++) {
				if (target->statusReceive[i].statusName == "Unhealable") {
					isAffected = true;
					target->statusReceive[i].releaseStatusTime = Tool::currentIngameTime + 3;
					break;
				}
			}
			if(!isAffected)
				target->ApplyStatus(StatusReceive("Unhealable", "Regeneration", 0, Tool::currentIngameTime + 3, 5));
		}
		else if (this->element == "Nature") {
			this->currentHealth += (target->maxHealth *0.055 * (110 / target->moveSpeed));
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