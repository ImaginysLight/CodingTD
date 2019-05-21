#include"Skill/BaseSkillClass.h"
#include"Skill/CoolBlooded.h"
#include"Skill/IceAge.h"
#include"Skill/BurningEnthusiasm.h"
#include"Skill/HellFire.h"
#include"Skill/HeavenBless.h"
class BaseUnitClass;

class SkillConstructor {
public:
	static BaseSkillClass* InitializeSkill(string skillName, int line, bool isOwned, int playerId, BaseUnitClass* target);

};

