#include "CoolBlooded.h"





CoolBlooded::CoolBlooded(int targetId, float expiredTime)
{
	this->targetId = targetId;
	this->expiredTime = expiredTime;
	//halved their Move Speed and Attack but double Health and Defense. (Current Health will scale equal to amount of bonus Health)
	auto target = BaseUnitClass::GetUnitById(targetId);
	if (target != nullptr && target->isAlive && target->action != "Die") {
		target->ApplyStatus(StatusReceive("Cool Blooded - Attack", "Attack", 0.5, Tool::currentIngameTime + 10, 2));
		target->ApplyStatus(StatusReceive("Cool Blooded - Move Speed", "MoveSpeed", 0.5, Tool::currentIngameTime + 10, 2));
		target->ApplyStatus(StatusReceive("Cool Blooded - Defense", "Defense", 2, Tool::currentIngameTime + 10, 2));
		target->currentHealth += target->maxHealth;
		target->maxHealth *= 2;
	}
	this->isAddedChild = true;
	BaseSkillClass::AllIngameSkill_Vector.push_back(this);
}

CoolBlooded::~CoolBlooded()
{
}

void CoolBlooded::Update()
{
	if (this->expiredTime < Tool::currentIngameTime) {
		auto target = BaseUnitClass::GetUnitById(targetId);
		if (target != nullptr && target->isAlive && target->action != "Die") {
			target->maxHealth /= 2;
			if (target->currentHealth > target->maxHealth) target->currentHealth -= target->maxHealth;
			else target->currentHealth = 1;
		}
		this->isReleased = true;
	}
}

