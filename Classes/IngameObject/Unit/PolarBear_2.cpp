#include "PolarBear_2.h"

PolarBear_2::PolarBear_2(int line, bool isOwned, int unitId, int playerId)
{
	name = "Polar Bear 2";
	description = "A diehard unit who can slow down attackers and stun on attack.";
	goldCost = 300;
	levelRequired = 2;
	maxHealth = 1400;
	currentHealth = maxHealth;
	baseAttack = 40;
	baseDefense = 100;
	baseMoveSpeed = 40;
	baseAttackSpeed = 30;
	range = 0;
	baseRegeneration = 4;

	upgradeName = "Polar Bear 3";
	upgradeGoldCost = 900;
	upgradeKnowledgeCost = 3;
	upgradeLevelRequired = 3;

	animationIndexOnTriggerAttack = 13;

	this->UpdateIngameInfo("Sprites/Polar Bear/attack/attack (1).png", unitId, playerId, isOwned, "Polar Bear", line);
}

PolarBear_2::~PolarBear_2()
{
}

void PolarBear_2::Attack(vector<BaseUnitClass*>& targets)
{
	numOfAttack++;

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
		if (numOfAttack == 3) {
			damage += 100;
			numOfAttack = 0;
			target->sprite->runAction(Sequence::create(DelayTime::create(0.4), MoveBy::create(0.4, Vec2(0, 150)), MoveBy::create(0.4, Vec2(0, -150)), nullptr));
			target->hardEffect.push_back(HardEffect("Stun", triggerTime, triggerTime + 2));
		}
		target->damageReceive.push_back(DamageReceive(this->unitId, damage, triggerTime, animateName, ""));
	}
}

void PolarBear_2::onDamageReceive(DamageReceive dmg)
{
	BaseUnitClass::onDamageReceive(dmg);
	auto attacker = BaseUnitClass::GetUnitById(dmg.attackerId);
	if (attacker == NULL) return;
	if (attacker->description != "Kingdom") {
		bool isAffected = false;
		for (int i = 0; i < attacker->statusReceive.size(); i++) {
			if (attacker->statusReceive[i].statusName == "Icy Body") {
				isAffected = true;
				attacker->statusReceive[i].releaseStatusTime = Tool::currentIngameTime + 5;
				break;
			}
		}
		if(!isAffected)
			attacker->ApplyStatus(StatusReceive("Icy Body", "Attack", 0.84, Tool::currentIngameTime + 5, 2));
	}
}
