﻿#include "EnragedUrsa_1.h"

EnragedUrsa_1::EnragedUrsa_1(int line, bool isOwned, int unitId, int playerId)
{
	name = "Enraged Ursa 1";
	description = "A heavy frenzy warrior will burn everything to hell with aoe attack.";
	goldCost = 250;
	levelRequired = 2;
	maxHealth = 650;
	currentHealth = maxHealth;
	baseAttack = 120;
	baseDefense = 50;
	baseMoveSpeed = 60;
	baseAttackSpeed = 30;
	range = 0;
	baseRegeneration = 2;

	upgradeName = "Enraged Ursa 2";
	upgradeGoldCost = 900;
	upgradeKnowledgeCost = 3;
	upgradeLevelRequired = 3;

	animationIndexOnTriggerAttack = 8;

	this->UpdateIngameInfo("Sprites/Enraged Ursa/attack/attack (1).png", unitId, playerId, isOwned, "Enraged Ursa", line);
	this->ApplyStatus(StatusReceive("Demon Heart", "Attack", 1, Tool::currentIngameTime + 100, 2));
}

EnragedUrsa_1::~EnragedUrsa_1()
{
}

void EnragedUrsa_1::Update() {
	//Demon Heart : increase 1 / 1.5% Attack per 1 % Health lose.
	for (int i = 0; i < this->statusReceive.size(); i++) {
		if (this->statusReceive[i].statusName == "Demon Heart") {
			this->statusReceive.erase(this->statusReceive.begin() + i);
			float value = 1 + (1.0 - (float)currentHealth / maxHealth * 1.0);
			this->ApplyStatus(StatusReceive("Demon Heart", "Attack", value, Tool::currentIngameTime + 100, 2));
			break;
		}
	}
	BaseUnitClass::Update();
}

void EnragedUrsa_1::Attack(vector<BaseUnitClass*>& targets)
{
	//Normal Attack
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
		target->damageReceive.push_back(DamageReceive(this->unitId, damage, triggerTime, animateName, ""));

	//Lucifer's Indignation: become angry when Health below 75%, improve normal attacks,
	//causing splash damage equal to 35% Attack within 400 range around its target.
		if (currentHealth < maxHealth *0.75) {
			float splashDamage = this->attack * 0.35;
			for (auto unit : BaseUnitClass::AllIngameUnit_Vector) {
				if (
					unit->unitId != target->unitId					//Không lan vào thằng đang bị đánh
					&& (this->isOwned != unit->isOwned)								// Xem có phải đối thủ không
					&& (unit->isAlive && unit->action != "Die")						//Xem còn sống không
					&& (target->line == unit->line)									//Xem cùng hàng không
					&& (abs(unit->root->getPositionX() - target->root->getPositionX()) < 400)// Xem trong range không
					) {
					unit->damageReceive.push_back(DamageReceive(this->unitId, splashDamage, triggerTime, animateName, ""));
				}
			}
		}
	}


}

