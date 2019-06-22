﻿#pragma once
#include "cocos2d.h"
#include"BaseUnitClass.h"

USING_NS_CC;
using namespace std;

class BlessedKingdom : public BaseUnitClass {
public:
	BlessedKingdom(int line, bool isOwned, int unitId, int playerId);
	~BlessedKingdom();
	void Die() override;
	void Attack(vector<BaseUnitClass*>& targets) override;
	//Special: Blessing Aura: All allies within this tower range will be blessed, restoring 2 / 2.75 / 3.5% hps.
	void Update() override;
	vector<BaseUnitClass*> FindTargets() override;

	int level = 1;
	void Upgrade() override;
};