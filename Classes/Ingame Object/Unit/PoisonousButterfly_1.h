#pragma once
#include "cocos2d.h"
#include"..\..\Global Class\Tool.h"
#include"BaseUnitClass.h"

USING_NS_CC;
using namespace std;

class PoisonousButterfly_1 : public BaseUnitClass {
public:
	PoisonousButterfly_1(int line, bool isOwned, int unitId, int playerId);
	~PoisonousButterfly_1();
	//The Presence of Life: bless all allies on the line, increase Regeneration by 3 / 5 and Attack Speed by 15 / 25%
	void Regeneration() override;
	//Agent Orange : improve normal attacks with Agent Orange, dealing pure damage equal to 2 / 3 % the target's Max Health, , and pierce  20 / 35% Defense.
	void Attack(vector<BaseUnitClass*>& targets) override;
	
	
};