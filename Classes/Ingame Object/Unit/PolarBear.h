#pragma once
#include "cocos2d.h"
#include"..\..\Global Class\Tool.h"
#include"BaseUnitClass.h"

USING_NS_CC;
using namespace std;

class PolarBear : public BaseUnitClass {
public:
	PolarBear(int line, bool isOwned, int unitId, int playerId);
	~PolarBear();
	//Ice Punch: Each 4th attack will knock the target into the air, dealing 100 bonus damage and stun them for 2 seconds.
	//Th�m action stun v�o target th�ng qua special trong damage receive
	int numOfAttack = 0;
	void Attack(vector<BaseUnitClass*>& targets) override;

	//Icy Body: Whoever attacked this bear will tremble, decrease 12% / 20% Attack for 5 seconds.
	void onDamageReceive(DamageReceive dmg) override;
};