#pragma once
#include "cocos2d.h"
#include"BaseUnitClass.h"

USING_NS_CC;
using namespace std;

class VampireDragon_1 : public BaseUnitClass {
public:
	VampireDragon_1(int line, bool isOwned, int unitId, int playerId);
	~VampireDragon_1();

	void Attack(vector<BaseUnitClass*>& targets) override;
	void Die() override;
	bool isRespawned = false;
	void Respawn();
};