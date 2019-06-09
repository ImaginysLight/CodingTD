#include "VampireDragon.h"

VampireDragon::VampireDragon(int line, bool isOwned, int unitId, int playerId)
{
	name = "Vampire Dragon";
	description = "A vampire with fast Regeneration and can restore Health on attack. Can revive upon death.";
	goldCost = 200;
	levelRequired = 2;
	maxHealth = 520;
	currentHealth = maxHealth;
	baseAttack = 75;
	baseDefense = 50;
	baseMoveSpeed = 80;
	baseAttackSpeed = 40;
	range = 0;
	baseRegeneration = 7;

	upgradeName = "Vampire Dragon 2";
	upgradeGoldCost = 1200;
	upgradeKnowledgeCost = 3;
	upgradeLevelRequired = 3;

	animationIndexOnTriggerAttack = 11;

	this->UpdateIngameInfo("Sprites/Vampire Dragon/attack/attack (1).png", unitId, playerId, isOwned, "Vampire Dragon", line);
}
//Vampire Touch: Improve normal attacks, restores Current Health by 20 / 35% of damage dealt,
//and steal 0.3 / 0.5% target's Max Health.


VampireDragon::~VampireDragon()
{
}

void VampireDragon::Attack(vector<BaseUnitClass*>& targets)
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
		if(target->description == "Kingdom") target->damageReceive.push_back(DamageReceive(this->unitId, damage, triggerTime, animateName, ""));
		else target->damageReceive.push_back(DamageReceive(this->unitId, damage, triggerTime, animateName, "Vampire Touch 1"));
	}
}

void VampireDragon::Die()
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

void VampireDragon::Respawn()
{
	float percentPower = (40 + this->maxHealth * 0.1) / 100.0;
	maxHealth = 500 * percentPower;
	currentHealth = maxHealth;
	baseAttack = 60 * percentPower;
	baseDefense = 50 * percentPower;
	baseMoveSpeed = 85 * percentPower;
	baseAttackSpeed = 35 * percentPower;
	baseRegeneration = 5 * percentPower;
	attack = baseAttack;
	defense = baseDefense;
	moveSpeed = baseMoveSpeed;
	attackSpeed = baseAttackSpeed;
	regeneration = baseRegeneration;
	UpdateHealthBar();
}

//Blessings From Demeter : On death, it will respawn with power proportional to amount of Health stolen,
//this ability only trigger one time.
//( 40 + 0.1*maxHealth ) % power in Level 1
//( 30 + 0.25*maxHealth ) % power in Level 2
