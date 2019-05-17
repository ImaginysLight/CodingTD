#pragma once
#include "cocos2d.h"
#include"..\..\Global Class\Tool.h"
#include"BaseUnitClass.h"

USING_NS_CC;
using namespace std;

class FrozenKingdom_3 : public BaseUnitClass {
public:
	FrozenKingdom_3(int line, bool isOwned, int unitId, int playerId);
	~FrozenKingdom_3();
	void Die() override;
	void Attack(vector<BaseUnitClass*>& targets) override;
	// Special: Frozen Aura : Whoever entered this tower range without permission will be cold, decrease Attack Speed by 10 / 15 / 20 % .
	void Update() override;
	vector<BaseUnitClass*> FindTargets() override;
};