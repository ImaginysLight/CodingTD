#pragma once
#include "cocos2d.h"
#include"BaseUnitClass.h"

USING_NS_CC;
using namespace std;

class HotheadedGunner_2 : public BaseUnitClass {
public:
	HotheadedGunner_2(int line, bool isOwned, int unitId, int playerId);
	void onDamageReceive(DamageReceive dmg) override;
	~HotheadedGunner_2();

	
	
};