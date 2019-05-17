#include "PoisonousButterfly_2.h"

PoisonousButterfly_2::PoisonousButterfly_2(int line, bool isOwned, int unitId, int playerId)
{
	name = "Poisonous Butterfly 2";
	description = "Increase allies' Regeneration and Attack Speed on the line, counter Tanky unit with Agent Orange on attack.";
	goldCost = 150;
	levelRequired = 1;
	maxHealth = 240;
	currentHealth = maxHealth;
	baseAttack = 40;
	baseDefense = 75;
	baseMoveSpeed = 80;
	baseAttackSpeed = 45;
	range = 500;
	baseRegeneration = 6;


	animationIndexOnTriggerAttack = 11;

	this->UpdateIngameInfo("Sprites/Poisonous Butterfly/attack/attack (1).png", unitId, playerId, isOwned, "Poisonous Butterfly", line);
}

PoisonousButterfly_2::~PoisonousButterfly_2()
{
}
//The Presence of Life: bless all allies on the line, increase Regeneration by 3 / 5 and Attack Speed by 15 / 25%
//Agent Orange : improve normal attacks with Agent Orange, dealing bonus damage equal to 2 / 3 % the target's Max Health
//, and decrease target's Defense percent equal to bonus damage for 1 second.
void PoisonousButterfly_2::Regeneration()
{
	BaseUnitClass::Regeneration();
	for (auto target : BaseUnitClass::AllIngameUnit_Vector) {
		if (target->isOwned == this->isOwned
			&& target->description != "Kingdom"
			&& target->line == this->line) {
			bool isAffected = false;
			for (int i = 0; i < target->statusReceive.size(); i++) {
				if (target->statusReceive[i].statusName.find("The Presence of Life") != std::string::npos) {
					target->statusReceive[i].releaseStatusTime = Tool::currentIngameTime + 2;
					isAffected = true;
				}
			}
			if (!isAffected) {
				target->ApplyStatus(StatusReceive("The Presence of Life - Regeneration", "Regeneration", 5, Tool::currentIngameTime + 2, 1));
				target->ApplyStatus(StatusReceive("The Presence of Life - Attack Speed", "AttackSpeed", 1.25, Tool::currentIngameTime + 2, 2));
			}
		}
	}
}

void PoisonousButterfly_2::Attack(vector<BaseUnitClass*>& targets)
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
		target->damageReceive.push_back(DamageReceive(this->unitId, damage, triggerTime, animateName, "Agent Orange 2"));
	}
}

//Agent Orange : improve normal attacks with Agent Orange, dealing bonus damage equal to 2 / 3 % the target's Max Health
//, and decrease target's Defense percent equal to bonus damage for 1 second.