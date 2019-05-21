#pragma once
#include"BaseSkillClass.h"
#include "cocos2d.h"
#include"..\..\Global Class\Tool.h"

USING_NS_CC;
using namespace std;

//Description: burn down all enemies with hell fire, dealt damage proportional to your army's Attack each second. (required Kingdom level 3)
//	Duration : 5
//	Energy cost : 115
//	Damage : (average all Attack of your army * 0.8) per second



class HellFire : public BaseSkillClass {
public:
	HellFire(int playerId);
	~HellFire();
	int playerId = 0;
	void Update() override;
};