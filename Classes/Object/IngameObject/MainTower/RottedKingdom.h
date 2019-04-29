#pragma once
#include "cocos2d.h"
#include"..\..\Tool.h"
#include"..\BaseObjectClass.h"
USING_NS_CC;
using namespace std;

class RottedKingdom : public BaseObjectClass {
public:
	vector<BaseObjectClass*> FindTargets(vector<BaseObjectClass*>& targets) override;
	RottedKingdom(bool isLeft, int id);
	~RottedKingdom();

	//Rotted Aura: Whoever entered this tower range will be rotted, decrease 8% Health per second.
	//Sử dụng chung method Regeneration, vì hồi máu và đốt máu aura đều xảy ra mỗi giây
	void Regeneration() override;
};