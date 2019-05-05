#pragma once
#include "cocos2d.h"
#include"..\..\Global Class\Tool.h"
#include"BaseUnitClass.h"

USING_NS_CC;
using namespace std;

class UFODriver : public BaseUnitClass {
public:
	UFODriver(int line, bool isOwned, int unitId, int playerId);
	~UFODriver();

	//Wrong Button: each 5 / 4 / 4 / 3th attack, the driver presses the wrong button, causing the next attack to
	//increase damage by 1.5 / 1.5 / 2.5 / 2.5, but the UFO runs of energy in 1 / 1.25 / 1.5 / 1 second.
	void Attack(vector<BaseUnitClass*>& targets) override;
	int numOfAttack = 0;
	
};