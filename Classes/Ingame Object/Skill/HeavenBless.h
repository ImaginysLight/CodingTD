#pragma once
#include"BaseSkillClass.h"
#include "cocos2d.h"
#include"..\..\Global Class\Tool.h"

USING_NS_CC;
using namespace std;

//give an ally a power of Ice, halved their Move Speed and Attack but double Health and Defense. (Current Health will scale equal to amount of bonus Health)

class HeavenBless : public BaseSkillClass {
public:
	HeavenBless(int playerId);
	~HeavenBless();
	int playerId = 0;
};