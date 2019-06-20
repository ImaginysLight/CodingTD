#pragma once
#include "cocos2d.h"
#include"..\..\Global Class\Tool.h"
#include"BaseUnitClass.h"

USING_NS_CC;
using namespace std;

class WingedOrc_1 : public BaseUnitClass {
public:
	WingedOrc_1(int line, bool isOwned, int unitId, int playerId);
	~WingedOrc_1();

	//Deathwing: blows away everything on attack, knockback both itself and the enemy by 25 / 25 / 100 range
//if the enemy is a unit, bonus 75 damage if the enemy is a building.
	void Attack(vector<BaseUnitClass*>& targets) override;
	
};