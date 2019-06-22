#include "FireArmor.h"




FireArmor::FireArmor(int targetId, int reflectPercent, float expiredTime)
{
	this->name = "Fire Armor";
	this->description = "reflect % pure damage to whoever attacks them.";
	this->targetId = targetId;
	this->reflectPercent = reflectPercent;
	this->expiredTime = expiredTime;
	this->isAddedChild = true;
	BaseSkillClass::AllIngameSkill_Vector.push_back(this);
}

FireArmor::~FireArmor()
{
}
void FireArmor::AddNewDamageReflect(DamageReceive dmg)
{
	this->damageReflected.push_back(dmg);
	auto victim = BaseUnitClass::GetUnitById(dmg.attackerId);
	if (victim == NULL) return;
	victim->damageReceive.push_back(DamageReceive(0, dmg.damage*this->reflectPercent / 100.0, dmg.triggerTime, "", ""));
}
//Fire Armor: buff an ally with Fire Armor, reflect 15 / 20% damage to whoever attacks them. (Duration: 10s, Cooldown: 10s)
void FireArmor::Update()
{
	if (this->expiredTime < Tool::currentIngameTime) {
		this->isReleased = true;
		auto armorOwner = BaseUnitClass::GetUnitById(this->targetId);
		if (armorOwner != NULL) {
			armorOwner->sprite->removeChildByName("FireArmor", true);
		}
		delete this;
		return;
	}

	auto armorOwner = BaseUnitClass::GetUnitById(this->targetId);
	if (armorOwner == NULL) return;
	for (auto dmg : armorOwner->damageReceive) {
		//Xem dmg này đã được reflect chưa
		bool isReflected = false;
		for (auto reflect : this->damageReflected) {
			if (dmg.attackerId == reflect.attackerId && dmg.triggerTime == reflect.triggerTime) {
				isReflected = true;
				break;
			}
		}
		if (!isReflected) this->AddNewDamageReflect(dmg);
	}
}

