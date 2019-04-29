#pragma once
#include "cocos2d.h"
#include"..\..\Tool.h"
#include"..\BaseObjectClass.h"
USING_NS_CC;
using namespace std;

class CursedKingdom : public BaseObjectClass {
public:
	vector<BaseObjectClass*> FindTargets(vector<BaseObjectClass*>& targets) override;
	CursedKingdom(bool isLeft, int id);
	~CursedKingdom();
};