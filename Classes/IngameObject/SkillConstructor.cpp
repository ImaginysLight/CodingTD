#include "SkillConstructor.h"

BaseSkillClass * SkillConstructor::InitializeSkill(string skillName, int line, bool isOwned, int playerId, int targetId)
{
	if (skillName == "Cool Blooded") return new CoolBlooded(targetId);
	if (skillName == "Ice Age") return new IceAge(playerId);
	if (skillName == "Burning Enthusiasm") return new BurningEnthusiasm(targetId);
	if (skillName == "Hell Fire") return new HellFire(playerId);
	if (skillName == "Natural Wind") return new NaturalWind(targetId);
	if (skillName == "Heaven Bless") return new HeavenBless(playerId);
	
	return nullptr;
}
