#include "BurningEnthusiasm.h"

BurningEnthusiasm::BurningEnthusiasm(int targetId)
{
	this->name = "Burning Enthusiasm";
	this->description = "give an ally a power of Fire, double their Attack but receive pure damage equal to 10% of bonus Attack (from every source) each second.";
	this->expiredTime = Tool::currentIngameTime + 10;
	this->nextTriggerTime = Tool::currentIngameTime + 0.96;
	this->targetId = targetId;
	auto target = BaseUnitClass::GetUnitById(targetId);
	if (target != nullptr && target->isAlive && target->action != "Die") {
		target->ApplyStatus(StatusReceive("Burning Enthusiasm", "Attack", 2, this->expiredTime, 0));
	}
	this->isAddedChild = true;
	BaseSkillClass::AllIngameSkill_Vector.push_back(this);
	
	
}
//target->hardEffect.push_back(HardEffect("Stun", triggerTime, triggerTime + 1));
BurningEnthusiasm::~BurningEnthusiasm()
{
}

void BurningEnthusiasm::Update()
{
	if (this->expiredTime < Tool::currentIngameTime) {
		this->isReleased = true;
		return;
	}
	if (this->nextTriggerTime < Tool::currentIngameTime) {
		this->nextTriggerTime = Tool::currentIngameTime + 0.96;
		auto target = BaseUnitClass::GetUnitById(targetId);
		if (target != nullptr && target->isAlive && target->action != "Die") {
			this->damage = (target->attack - target->baseAttack) *0.1;
			target->damageReceive.push_back(DamageReceive(0, damage, Tool::currentIngameTime, animateName, ""));
		}
		else {
			this->expiredTime = Tool::currentIngameTime;
		}
	}
}
