#include"PassiveSkill.h"
float PassiveSkill::Bonus_Attack = 0.17;
float PassiveSkill::Bonus_Defense = 0.05;
float PassiveSkill::Bonus_Health = 0.05;
float PassiveSkill::Bonus_Regeneration = 2;
float PassiveSkill::Bonus_AttackSpeed = 8;
int PassiveSkill::fireLevel = 0;
int PassiveSkill::iceLevel = 0;
int PassiveSkill::natureLevel = 0;


void PassiveSkill::IcySoul(BaseUnitClass*& unit)
{
	unit->baseDefense += (unit->baseDefense*PassiveSkill::Bonus_Defense);
	unit->ReprocessAllStatus("Defense");
	unit->currentHealth += (unit->maxHealth*PassiveSkill::Bonus_Health);
	unit->maxHealth += (unit->maxHealth*PassiveSkill::Bonus_Health);
}

void PassiveSkill::FierySprit(BaseUnitClass*& unit)
{
	unit->baseAttack += (unit->baseAttack*PassiveSkill::Bonus_Attack);
	unit->ReprocessAllStatus("Attack");
}

void PassiveSkill::PureHeart(BaseUnitClass*& unit)
{
	unit->baseRegeneration += PassiveSkill::Bonus_Regeneration;
	unit->ReprocessAllStatus("Regeneration");
	unit->baseAttackSpeed += PassiveSkill::Bonus_AttackSpeed;
	unit->ReprocessAllStatus("AttackSpeed");
}

void PassiveSkill::ApplyPassive(int unitId, string elementName)
{
	auto unit = BaseUnitClass::GetUnitById(unitId);
	if (unit->isAlive && unit->action != "Die" && unit->description != "Kingdom") {
		if (elementName == "Fire") PassiveSkill::FierySprit(unit);
		else if (elementName == "Ice") PassiveSkill::IcySoul(unit);
		else if (elementName == "Nature") PassiveSkill::PureHeart(unit);
	}
}

void PassiveSkill::Improve(string elementName)
{
	if (elementName == "Fire") {
		PassiveSkill::Bonus_Attack += 0.008;
		PassiveSkill::fireLevel++;
	}
	else if (elementName == "Ice") {
		PassiveSkill::Bonus_Defense += 0.005;
		PassiveSkill::Bonus_Health += 0.005;
		PassiveSkill::iceLevel++;
	}
	else if (elementName == "Nature") {
		PassiveSkill::Bonus_Regeneration += 0.2;
		PassiveSkill::Bonus_AttackSpeed += 0.4;
		PassiveSkill::natureLevel++;
	}
}
