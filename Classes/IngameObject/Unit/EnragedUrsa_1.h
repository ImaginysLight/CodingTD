#pragma once
#include "cocos2d.h"
#include"BaseUnitClass.h"

USING_NS_CC;
using namespace std;

class EnragedUrsa_1 : public BaseUnitClass {
public:
	EnragedUrsa_1(int line, bool isOwned, int unitId, int playerId);
	~EnragedUrsa_1();
	
	//Demon Heart : increase 1 / 1.5% Attack per 1 % Health lose.
	void Update() override;

	//Lucifer's Indignation: become angry when Health below 75%, improve normal attacks,
	//causing splash damage equal to 35% Attack within 400 range around its target.

	void Attack(vector<BaseUnitClass*>& targets) override;
	
};