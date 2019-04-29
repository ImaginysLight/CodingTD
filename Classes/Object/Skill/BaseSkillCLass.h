#pragma once
#include "cocos2d.h"
#include"../Tool.h"

USING_NS_CC;
using namespace std;

// Thể hiện skill bất kỳ
class BaseSkillClass {
public:
	string skillName = "";
	string description = "";
	int goldCost = 0;
	int energyCost = 0;
	int levelRequired = 1;
	int areaOfEffect = 0;
	bool isActive = true;
	int cooldown = 0;

	string animateName = "";
	float destinationTime = 0;
	float nextTriggerTime = 0;
	Node* root;
	


	BaseSkillClass();
	~BaseSkillClass();

};