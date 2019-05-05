#pragma once
#include"BaseSkillClass.h"
#include "cocos2d.h"
#include"..\..\Global Class\Tool.h"

USING_NS_CC;
using namespace std;

class FrostNova : public BaseSkillClass {
public:
	FrostNova(Vec2 position, int line, float damage, float triggerTime, bool isOwned);
	~FrostNova();

	void Update() override;
	void onTrigger() override;
};