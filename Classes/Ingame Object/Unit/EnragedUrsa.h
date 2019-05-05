#pragma once
#include "cocos2d.h"
#include"..\..\Global Class\Tool.h"
#include"BaseUnitClass.h"

USING_NS_CC;
using namespace std;

class EnragedUrsa : public BaseUnitClass {
public:
	EnragedUrsa(int line, bool isOwned, int unitId, int playerId);
	~EnragedUrsa();

	//Demon Heart: increase 2% Attack per 1% Health lose.
	//Lucifer's Indignation: become angry when Health below 50%, improve normal attacks, causing splash damage equal to 
	//35% Attack within 400 range around its target.
	void Attack(vector<BaseUnitClass*>& targets) override;
	
};