#pragma once
#include "cocos2d.h"
#include"..\..\Global Class\Tool.h"
#include"BaseUnitClass.h"

USING_NS_CC;
using namespace std;

class Helicopter : public BaseUnitClass {
public:
	Helicopter(int line, bool isOwned, int unitId, int playerId);
	~Helicopter();
	//Keen Eyes: attack upto 2 targets in all lines.
	vector<BaseUnitClass*> FindTargets() override;
	
};