#include "CoolBlooded.h"

CoolBlooded::CoolBlooded(int targetId)
{
	this->targetId = targetId;
	this->expiredTime = Tool::currentIngameTime + 10;
	this->name = "Cool Blooded";
	this->description = "give an ally a power of Ice, halved their Move Speed and Attack but double Health and Defense. ";
	this->isAddedChild = true;
	BaseSkillClass::AllIngameSkill_Vector.push_back(this);

	auto target = BaseUnitClass::GetUnitById(targetId);
	if (target != nullptr && target->isAlive && target->action != "Die") {
		target->ApplyStatus(StatusReceive("Cool Blooded - Attack", "Attack", 0.5, expiredTime, 2));
		target->ApplyStatus(StatusReceive("Cool Blooded - Move Speed", "MoveSpeed", 0.5, expiredTime, 2));
		target->ApplyStatus(StatusReceive("Cool Blooded - Defense", "Defense", 2, expiredTime, 2));
		target->currentHealth += target->maxHealth;
		target->maxHealth *= 2;
	}
}

CoolBlooded::~CoolBlooded()
{
}

void CoolBlooded::Update()
{
	if (this->expiredTime < Tool::currentIngameTime) {
		auto target = BaseUnitClass::GetUnitById(targetId);
		target->maxHealth /= 2;
		if (target->currentHealth < target->maxHealth) target->currentHealth = 1;
		else target->currentHealth -= target->maxHealth;
		this->isReleased = true;
	}
}

