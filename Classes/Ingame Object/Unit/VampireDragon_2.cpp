#include "VampireDragon_2.h"

VampireDragon_2::VampireDragon_2(int line, bool isOwned, int unitId, int playerId)
{
	name = "Vampire Dragon 2";
	description = "A vampire with fast Regeneration and can restore Health on attack. Can revive upon death.";
	goldCost = 175;
	levelRequired = 2;
	maxHealth = 560;
	currentHealth = maxHealth;
	baseAttack = 66;
	baseDefense = 75;
	baseMoveSpeed = 85;
	baseAttackSpeed = 50;
	range = 0;
	baseRegeneration = 15;

	animationIndexOnTriggerAttack = 11;

	this->UpdateIngameInfo("Sprites/Vampire Dragon/attack/attack (1).png", unitId, playerId, isOwned, "Vampire Dragon", line);
}
//Vampire Touch: Improve normal attacks, restores Current Health by 20 / 35% of damage dealt,
//and steal 0.3 / 0.5% target's Max Health.


VampireDragon_2::~VampireDragon_2()
{
}

void VampireDragon_2::Attack(vector<BaseUnitClass*>& targets)
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
		if (target->description == "Kingdom") target->damageReceive.push_back(DamageReceive(this->unitId, damage, triggerTime, animateName, ""));
		else target->damageReceive.push_back(DamageReceive(this->unitId, damage, triggerTime, animateName, "Vampire Touch 2"));
	}
}

void VampireDragon_2::Die()
{
	if (!isRespawned) {
		isRespawned = true;
		this->StotpAction("All");
		this->action = "Die";
		auto animate = IngameObject::animate[this->animateName + "_die"]->clone();
		this->sprite->runAction(Sequence::create(
			animate,
			CallFunc::create([&]() {
			Respawn();
			this->action = "Idle";
		}),
			nullptr
			));
	}
	else BaseUnitClass::Die();
}

void VampireDragon_2::Respawn()
{
	float percentPower = (35 + (float)this->maxHealth / (1.8 * 5.6)) / 100.0;
	maxHealth = 560 * percentPower;
	currentHealth = maxHealth;
	baseAttack = 66 * percentPower;
	baseDefense = 75 * percentPower;
	baseMoveSpeed = 85 * percentPower;
	baseAttackSpeed = 50 * percentPower;
	baseRegeneration = 8 * percentPower;
	attack = baseAttack;
	defense = baseDefense;
	moveSpeed = baseMoveSpeed;
	attackSpeed = baseAttackSpeed;
	regeneration = baseRegeneration;
	UpdateHealthBar();
}

//Blessings From Demeter : On death, it will respawn with power proportional to amount of Health stolen,
//this ability only trigger one time. (35 + (float)this->maxHealth / (1.8 * 5.6)) / 100.0; (Level 2)