#pragma once
#include "cocos2d.h"
#include"..\Tool.h"
#include"BaseObjectClass.h"
USING_NS_CC;
using namespace std;

class Robot12 : public BaseObjectClass {
public:
	// Special: Attack 2 targets, can attack all line.
	int numOfTarget = 0;
	vector<BaseObjectClass*> FindTargets(vector<BaseObjectClass*>& targets) override;
	Robot12(int line, bool isLeft);
	~Robot12();
};