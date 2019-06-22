#pragma once
#include "cocos2d.h"
#include"BaseUnitClass.h"

USING_NS_CC;
using namespace std;

class ElementalAlien_1 : public BaseUnitClass {
public:
	ElementalAlien_1(int line, bool isOwned, int unitId, int playerId);
	~ElementalAlien_1();
//Icy Claws: dealt bonus damage as 13 / 20 / 27 / 35% target's Attack on attack. 
//Fiery Claws : dealt bonus damage as 2.5 / 3 / 3.5 / 4 * target's Regeneration and make them unhealable for 1 / 2 / 3 / 4 seconds on attack.
//Vitality Claws : lifesteal 5 / 6 / 7 / 8 % target's Max Health multiply (10 / Move Speed) on attack.
	string element = "";
	void Attack(vector<BaseUnitClass*> &targets) override;
	
	
};