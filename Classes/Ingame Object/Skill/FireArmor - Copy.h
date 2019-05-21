#pragma once
#include"BaseSkillClass.h"
#include "cocos2d.h"
#include"..\..\Global Class\Tool.h"

USING_NS_CC;
using namespace std;

//Fire Armor: buff an ally with Fire Armor, reflect 15 / 20% damage to whoever attacks them. (Duration: 10s, Cooldown: 10s)

class CoolBlooded : public BaseSkillClass {
public:
	CoolBlooded(int targetId, float expiredTime);
	~CoolBlooded();

	int targetId = 0;
	void Update() override;
};