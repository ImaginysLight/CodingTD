#pragma once
#include"BaseSkillClass.h"
#include "cocos2d.h"
#include"..\..\Global Class\Tool.h"

USING_NS_CC;
using namespace std;

//encourage all allies with a bless from heaven, increase current Health and max Health by 300.

class HeavenBless : public BaseSkillClass {
public:
	HeavenBless(int playerId);
	~HeavenBless();
	int playerId = 0;
};