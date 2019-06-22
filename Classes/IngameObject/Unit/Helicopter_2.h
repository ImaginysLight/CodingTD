#pragma once
#include "cocos2d.h"
#include"BaseUnitClass.h"

USING_NS_CC;
using namespace std;

class Helicopter_2 : public BaseUnitClass {
public:
	Helicopter_2(int line, bool isOwned, int unitId, int playerId);
	~Helicopter_2();
	//Keen Eyes: attack upto 3 targets in all lines.
	vector<BaseUnitClass*> FindTargets() override;
	
};