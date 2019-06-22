#pragma once
#include "cocos2d.h"
#include"BaseUnitClass.h"

USING_NS_CC;
using namespace std;

class Helicopter_1 : public BaseUnitClass {
public:
	Helicopter_1(int line, bool isOwned, int unitId, int playerId);
	~Helicopter_1();
	//Keen Eyes: attack upto 2 targets in all lines.
	vector<BaseUnitClass*> FindTargets() override;
	
};