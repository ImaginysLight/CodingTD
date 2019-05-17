#pragma once
#include "cocos2d.h"
#include"..\..\Global Class\Tool.h"
#include"BaseUnitClass.h"

USING_NS_CC;
using namespace std;

class FlamedKingdom : public BaseUnitClass {
public:
	FlamedKingdom(int line, bool isOwned, int unitId, int playerId);
	~FlamedKingdom();
	void Die() override;
	void Attack(vector<BaseUnitClass*>& targets) override;
	//Special: Burning Aura: Whoever entered this tower range without permission will be burned, Regeneration decrease to -8 / -14 / -20 hps.
	void Update() override;
	vector<BaseUnitClass*> FindTargets() override;
};