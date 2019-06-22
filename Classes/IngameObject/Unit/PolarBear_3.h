#pragma once
#include "cocos2d.h"
#include"BaseUnitClass.h"

USING_NS_CC;
using namespace std;

class PolarBear_3 : public BaseUnitClass {
public:
	PolarBear_3(int line, bool isOwned, int unitId, int playerId);
	~PolarBear_3();
	//Ice Punch : Each 3th attack will knock the target into the air, dealing 100 / 200 / 300 bonus damage and stun them for 1 / 2 / 3 seconds.
	//Thêm action stun vào target thông qua special trong damage receive
	int numOfAttack = 0;
	void Attack(vector<BaseUnitClass*>& targets) override;

	//Icy Body : Whoever attacked this bear will tremble, decrease 12 / 16 / 20 % Attack. (Trigger after first hit, last 5 seconds)
	void onDamageReceive(DamageReceive dmg) override;
};