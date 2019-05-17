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


	void Attack(vector<BaseUnitClass*>& targets) override;
	int numOfAttack = 0;
	
};