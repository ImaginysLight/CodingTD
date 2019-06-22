#pragma once
#include"BaseSkillClass.h"
#include "cocos2d.h"


USING_NS_CC;
using namespace std;

//give an ally a power of Ice, halved their Move Speed and Attack but double Health and Defense. (Current Health will scale equal to amount of bonus Health)

class NaturalWind : public BaseSkillClass {
public:
	NaturalWind(int targetId);
	~NaturalWind();
	int targetId = 0;
	int attackSpeedBonus = 0;
	void Update() override;
};