#pragma once
#include "cocos2d.h"
#include"..\..\Global Class\Tool.h"
#include"BaseUnitClass.h"

USING_NS_CC;
using namespace std;

class LiquidAssassin_2 : public BaseUnitClass {
public:
	LiquidAssassin_2(int line, bool isOwned, int unitId, int playerId);
	~LiquidAssassin_2();
	//Death Strike : blink toward an enemy on any line and attack, dealt 100 / 175 / 250 bonus damage on attack.
//This ability has 1 charge and will be restored when an enemy dies within 700 range around Assassin,
//cooldown 5 / 4 / 3 seconds.
	void Update() override;
	bool isDeathStrikeReady = true;
	float cooldownTime = Tool::currentIngameTime;
	void Attack(vector<BaseUnitClass*> &targets) override;
	vector<BaseUnitClass*> FindTargets() override;
};