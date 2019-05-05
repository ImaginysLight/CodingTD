#include "PolarBear.h"

PolarBear::PolarBear(int line, bool isOwned, int unitId, int playerId)
{
	name = "Polar Bear";
	description = "Lord of Ice";
	goldCost = 250;
	energyCost = 1;
	levelRequired = 3;
	maxHealth = 1200;
	currentHealth = maxHealth;
	baseAttack = 120;
	baseDefense = 75;
	baseMoveSpeed = 5;
	baseAttackSpeed = 25;
	range = 150;
	baseRegeneration = 3;

	upgradeName = "Polar Bear 2";
	upgradeGoldCost = 900;
	upgradeEnergyCost = 3;
	upgradeLevelRequired = 3;

	animationIndexOnTriggerAttack = 13;

	this->UpdateIngameInfo("Sprites/Polar Bear/attack/attack (1).png", unitId, playerId, isOwned, "Polar Bear", line);
}

PolarBear::~PolarBear()
{
}

void PolarBear::Attack(vector<BaseUnitClass*>& targets)
{
	numOfAttack++;

	this->action = "Attack";
	auto animate = IngameObject::animate[this->animateName + "_attack"]->clone();
	animate->setDuration(60 / this->attackSpeed - 0.15); //Cho nó đánh xong dừng lại 0.15s trước khi đánh phát tiếp theo
	this->sprite->runAction(Sequence::create(
		animate,
		DelayTime::create(0.15),
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
		if (numOfAttack == 4) {
			damage += 100;
			numOfAttack = 0;
			target->hardEffect.push_back(HardEffect("Stun", triggerTime, triggerTime + 2));
		}
		target->damageReceive.push_back(DamageReceive(this->unitId, damage, triggerTime, animateName, ""));
	}
}

void PolarBear::onDamageReceive(DamageReceive dmg)
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
			attacker->ApplyStatus(StatusReceive("Icy Body", "Attack", 0.88, Tool::currentIngameTime + 5, 2));
	}
}
