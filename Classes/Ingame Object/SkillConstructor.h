#include"Skill/BaseSkillClass.h"
#include"Skill/FrostNova.h"
class BaseUnitClass;

class SkillConstructor {
public:
	static BaseSkillClass* InitializeSkill(string objectName, int line, bool isOwned, int playerId);

};

