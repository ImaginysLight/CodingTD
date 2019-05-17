#pragma once
#include "cocos2d.h"
#include"..\..\Global Class\Tool.h"
#include"BaseUnitClass.h"
#include"../Skill/FrostNova.h"

USING_NS_CC;
using namespace std;

class FrostWyvern_3 : public BaseUnitClass {
public:
	FrostWyvern_3(int line, bool isOwned, int unitId, int playerId);
	~FrostWyvern_3();
	//Frost Nova: Launch a snowball toward enemy, dealing 60 / 75 / 100 splash damage in 100 range,
	//pierce 25 / 35 / 50 Defense (Cooldown 7 / 6 / 4 seconds)
	float snowballReady = Tool::currentIngameTime;
	void Attack(vector<BaseUnitClass*> &targets) override;

	////The Presence of Ice: Slow all enemies on the line, decrease Move Speed by 10 / 15 / 20 and Attack Speed by 10 / 17 / 25%
	void Regeneration() override;
};