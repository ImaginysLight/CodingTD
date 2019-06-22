#include "EnragedUrsa_2.h"

EnragedUrsa_2::EnragedUrsa_2(int line, bool isOwned, int unitId, int playerId)
{
	name = "Enraged Ursa 2";
	description = "A heavy frenzy warrior will burn everything to hell with aoe attack.";
	goldCost = 250;
	levelRequired = 2;
	maxHealth = 625;
	currentHealth = maxHealth;
	baseAttack = 250;
	baseDefense = 30;
	baseMoveSpeed = 70;
	baseAttackSpeed = 24;
	range = 0;
	baseRegeneration = 3;



	animationIndexOnTriggerAttack = 8;

	this->UpdateIngameInfo("Sprites/Enraged Ursa/attack/attack (1).png", unitId, playerId, isOwned, "Enraged Ursa", line);
	this->ApplyStatus(StatusReceive("Demon Heart", "Attack", 1, Tool::currentIngameTime + 100, 2));
}

EnragedUrsa_2::~EnragedUrsa_2()
{
}

void EnragedUrsa_2::Update() {
	//Demon Heart : increase 1 / 1.5% Attack per 1 % Health lose.
	for (int i = 0; i < this->statusReceive.size(); i++) {
		if (this->statusReceive[i].statusName == "Demon Heart") {
			this->statusReceive.erase(this->statusReceive.begin() + i);
			float value = 1 + (1.5 - (float)currentHealth / maxHealth * 1.5);
			this->ApplyStatus(StatusReceive("Demon Heart", "Attack", value, Tool::currentIngameTime + 100, 2));
			break;
		}
	}
	BaseUnitClass::Update();
}

void EnragedUrsa_2::Attack(vector<BaseUnitClass*>& targets)
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
		string animateName = "_explosion"; // Không có sprite nên ai bắn cũng nổ như nhau
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

