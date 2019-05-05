#include "EnragedUrsa.h"

EnragedUrsa::EnragedUrsa(int line, bool isOwned, int unitId, int playerId)
{
	name = "Enraged Ursa";
	description = "Lord of Fire";
	goldCost = 200;
	energyCost = 1;
	levelRequired = 3;
	maxHealth = 1000;
	currentHealth = maxHealth;
	baseAttack = 140;
	baseDefense = 50;
	baseMoveSpeed = 8;
	baseAttackSpeed = 30;
	range = 150;
	baseRegeneration = 0;

	upgradeName = "Enraged Ursa 2";
	upgradeGoldCost = 600;
	upgradeEnergyCost = 2;
	upgradeLevelRequired = 3;

	animationIndexOnTriggerAttack = 8;

	this->UpdateIngameInfo("Sprites/Enraged Ursa/attack/attack (1).png", unitId, playerId, isOwned, "Enraged Ursa", line);
}

EnragedUrsa::~EnragedUrsa()
{
}


void EnragedUrsa::Attack(vector<BaseUnitClass*>& targets)
{
	//Demon Heart: increase 2% Attack per 1% Health lose.
	float currentAttack = this->attack;
	this->attack *= (1 + (1.0 - ((float)currentHealth / maxHealth)) / 2.0);

	//Normal Attack
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
		target->damageReceive.push_back(DamageReceive(this->unitId, damage, triggerTime, animateName, ""));

		//Lucifer's Indignation: become angry when Health below 50%, improve normal attacks, causing splash damage
		//equal to 35 % Attack within 400 range around its target.
		if (currentHealth < maxHealth / 2) {
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

	

	this->attack = currentAttack;
}

