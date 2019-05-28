#include"BaseSkillClass.h"

vector<BaseSkillClass*> BaseSkillClass::AllIngameSkill_Vector;
unordered_map<string, SkillRequired> BaseSkillClass::SkillRequirement;

void BaseSkillClass::LoadSkillRequirement()
{
	BaseSkillClass::SkillRequirement.insert({ "Cool Blooded",SkillRequired(20,1,true) });
	BaseSkillClass::SkillRequirement.insert({ "Ice Age",SkillRequired(130,2,false) });
	BaseSkillClass::SkillRequirement.insert({ "Burning Enthusiasm",SkillRequired(15,1,true) });
	BaseSkillClass::SkillRequirement.insert({ "Hell Fire",SkillRequired(115,2,false) });
	BaseSkillClass::SkillRequirement.insert({ "Natural Wind",SkillRequired(15,1,true) });
	BaseSkillClass::SkillRequirement.insert({ "Heaven Bless",SkillRequired(95,2,false) });
}

void BaseSkillClass::Update()
{
}

void BaseSkillClass::onTrigger()
{
}

BaseSkillClass::BaseSkillClass()
{
}

BaseSkillClass::~BaseSkillClass()
{
}

SkillRequired::SkillRequired(int energy, int level, bool needToSelect)
{
	this->energy = energy;
	this->level = level;
	this->needToSelect = needToSelect;
}

SkillRequired::SkillRequired()
{
}
