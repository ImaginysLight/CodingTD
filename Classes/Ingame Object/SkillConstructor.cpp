#include "SkillConstructor.h"

BaseSkillClass * SkillConstructor::InitializeSkill(string skillName, int line, bool isOwned, int playerId, BaseUnitClass* target)
{
	if (skillName == "Cool Blooded") return new CoolBlooded(target->unitId);
	if (skillName == "Ice Age") return new IceAge(playerId);
	if (skillName == "Burning Enthusiasm") return new BurningEnthusiasm(target->unitId);
	if (skillName == "Hell Fire") return new HellFire(playerId);
	if (skillName == "Heaven Bless") return new HeavenBless(playerId);
	
	return nullptr;
}
