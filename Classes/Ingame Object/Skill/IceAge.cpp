#include "IceAge.h"

IceAge::IceAge(int userId)
{
	this->userId = userId;
	this->name = "Ice Age";
	this->description = "freeze all enemies in Ice, stun them for 4 seconds and deal damage inversely proportional to their Attack Speed and proportional to their Attack. (required Kingdom level 2)";

	for (auto unit : BaseUnitClass::AllIngameUnit_Vector) {
		if (unit->ownerPlayerId != this->userId) {
			float damage = 80 + (60 - unit->attackSpeed + unit->attack * 0.4) * 4;
			if (damage < 80) damage = 80;
			unit->damageReceive.push_back(DamageReceive(0, damage, Tool::currentIngameTime, "Ice Age_ice",""));
			unit->hardEffect.push_back(HardEffect("Stun", Tool::currentIngameTime, Tool::currentIngameTime + 4));
		}
	}
}
//target->hardEffect.push_back(HardEffect("Stun", triggerTime, triggerTime + 1));
IceAge::~IceAge()
{
}
