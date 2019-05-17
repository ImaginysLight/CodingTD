#pragma once
#include "cocos2d.h"
#include"..\..\Global Class\Tool.h"
#include"BaseUnitClass.h"

USING_NS_CC;
using namespace std;

class FlamedKingdom_3 : public BaseUnitClass {
public:
	FlamedKingdom_3(int line, bool isOwned, int unitId, int playerId);
	~FlamedKingdom_3();
	void Die() override;
	void Attack(vector<BaseUnitClass*>& targets) override;
	//Special: Burning Aura: Whoever entered this tower range without permission will be burned, Regeneration decrease to -8 / -14 / -20 hps.
	void Update() override;
	vector<BaseUnitClass*> FindTargets() override;
};