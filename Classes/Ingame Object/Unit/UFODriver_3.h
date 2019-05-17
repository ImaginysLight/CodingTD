#pragma once
#include "cocos2d.h"
#include"..\..\Global Class\Tool.h"
#include"BaseUnitClass.h"

USING_NS_CC;
using namespace std;

class UFODriver_3 : public BaseUnitClass {
public:
	UFODriver_3(int line, bool isOwned, int unitId, int playerId);
	~UFODriver_3();

	void Attack(vector<BaseUnitClass*>& targets) override;
	int numOfAttack = 0;
	
};