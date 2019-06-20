#pragma once
#include "cocos2d.h"
#include"BaseSkillClass.h"
#include"..\..\Global Class\Tool.h"

USING_NS_CC;
using namespace std;

//This class contain 3 passive skill of each element.

class PassiveSkill{
public:
	static float Bonus_Attack;
	static float Bonus_Defense;
	static float Bonus_Health;
	static float Bonus_Regeneration;
	static float Bonus_AttackSpeed;
	static int fireLevel;
	static int iceLevel;
	static int natureLevel;

	static void IcySoul(BaseUnitClass*& unit);
	static void FierySprit(BaseUnitClass*& unit);
	static void PureHeart(BaseUnitClass*& unit);

	static void ApplyPassive(int unitId, string elementName);
	static void Improve(string elementName);
};