#include "NaturalWind.h"

NaturalWind::NaturalWind(int targetId)
{
	this->targetId = targetId;
	this->name = "Natural Wind";
	this->description = "give an ally a power of Nature, immediately increase Attack Speed by 10, then increase by 1 each second for 20 seconds.";
	this->nextTriggerTime = Tool::currentIngameTime + 1;

	auto target = BaseUnitClass::GetUnitById(targetId);
	if (target != nullptr && target->isAlive && target->action != "Die") {
		target->baseAttackSpeed += 10;
		target->ReprocessAllStatus("AttackSpeed");
		auto sp_Icon = Sprite::create("Skill/Natural Wind.png");
		Tool::setNodeSize(sp_Icon, 32, 32);
		sp_Icon->setPosition(target->sprite->getBoundingBox().size / 2);
		target->sprite->addChild(sp_Icon);
	}
	else return;

	this->isAddedChild = true;
	BaseSkillClass::AllIngameSkill_Vector.push_back(this);
}

NaturalWind::~NaturalWind()
{
}

void NaturalWind::Update()
{
	if (this->nextTriggerTime < Tool::currentIngameTime) {
		this->nextTriggerTime = Tool::currentIngameTime + 1;
		
		auto target = BaseUnitClass::GetUnitById(targetId);
		if (target != nullptr && target->isAlive && target->action != "Die") {
			target->baseAttackSpeed += 1;
			target->ReprocessAllStatus("AttackSpeed");
			if (++this->attackSpeedBonus == 20) this->isReleased = true;
		}
		else this->isReleased = true;
	}
}

