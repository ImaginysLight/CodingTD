#pragma once
#include "cocos2d.h"
#include"BaseUnitClass.h"

USING_NS_CC;
using namespace std;

class HotheadedGunner_3 : public BaseUnitClass {
public:
	HotheadedGunner_3(int line, bool isOwned, int unitId, int playerId);
	void onDamageReceive(DamageReceive dmg) override;
	~HotheadedGunner_3();

	
	
};