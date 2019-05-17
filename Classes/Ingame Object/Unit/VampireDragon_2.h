#pragma once
#include "cocos2d.h"
#include"..\..\Global Class\Tool.h"
#include"BaseUnitClass.h"

USING_NS_CC;
using namespace std;

class VampireDragon_2 : public BaseUnitClass {
public:
	VampireDragon_2(int line, bool isOwned, int unitId, int playerId);
	~VampireDragon_2();

	void Attack(vector<BaseUnitClass*>& targets) override;
	void Die() override;
	bool isRespawned = false;
	void Respawn();
};