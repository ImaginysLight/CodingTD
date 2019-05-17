#pragma once
#include "cocos2d.h"
#include"..\..\Global Class\Tool.h"
#include"BaseUnitClass.h"

USING_NS_CC;
using namespace std;

class VampireDragon : public BaseUnitClass {
public:
	VampireDragon(int line, bool isOwned, int unitId, int playerId);
	~VampireDragon();

	void Attack(vector<BaseUnitClass*>& targets) override;
	void Die() override;
	bool isRespawned = false;
	void Respawn();
};