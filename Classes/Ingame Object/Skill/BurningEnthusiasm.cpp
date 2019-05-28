#include "BurningEnthusiasm.h"

BurningEnthusiasm::BurningEnthusiasm(int targetId)
{
	this->name = "Burning Enthusiasm";
	this->description = "give an ally a power of Fire, double their Attack but receive pure damage equal to 10% of that bonus each second.";
	this->nextTriggerTime = Tool::currentIngameTime + 1;
	this->targetId = targetId;
	auto target = BaseUnitClass::GetUnitById(targetId);
	if (target != nullptr && target->isAlive && target->action != "Die") {
		this->damage = target->baseAttack*0.1;
		target->baseAttack *= 2;
		target->ReprocessAllStatus("Attack");
	}
	else return;
	this->isAddedChild = true;
	BaseSkillClass::AllIngameSkill_Vector.push_back(this);
}
BurningEnthusiasm::~BurningEnthusiasm()
{
}

void BurningEnthusiasm::Update()
{
	if (this->nextTriggerTime < Tool::currentIngameTime) {
		this->nextTriggerTime = Tool::currentIngameTime + 1;
		auto target = BaseUnitClass::GetUnitById(targetId);
		if (target != nullptr && target->isAlive && target->action != "Die")
			target->currentHealth -= this->damage;
		else 
			this->isReleased = true;
	}
}
