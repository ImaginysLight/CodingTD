#pragma once
#include "cocos2d.h"
#include"..\..\Tool.h"
#include"..\BaseObjectClass.h"
USING_NS_CC;
using namespace std;

class FlamedKingdom : public BaseObjectClass {
public:
	vector<BaseObjectClass*> FindTargets(vector<BaseObjectClass*>& targets) override;
	FlamedKingdom(bool isLeft, int id);
	~FlamedKingdom();

	//Flamed Aura: Whoever attacked this tower will be burned, receiving 25% of the attacking tower's damage.
	void ExcuteDamageReceive(DamageReceive dmg) override;
};