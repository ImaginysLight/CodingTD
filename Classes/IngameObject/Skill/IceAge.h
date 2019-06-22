#pragma once
#include"BaseSkillClass.h"
#include "cocos2d.h"


USING_NS_CC;
using namespace std;

//Description: freeze all enemies in Ice, stun them for 4 seconds and deal damage inversely proportional to their Attack Speed and proportional to their Attack. (required Kingdom level 2)
//Energy cost : 130
//Damage : 200 + (60 – Attack Speed + Attack * 0.15) * 8
//* Note that 200 is minimum damage


class IceAge : public BaseSkillClass {
public:
	IceAge(int userId);
	~IceAge();
	int userId = 0;
};