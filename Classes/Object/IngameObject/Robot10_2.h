#pragma once
#include "cocos2d.h"
#include"..\Tool.h"
#include"BaseObjectClass.h"
USING_NS_CC;
using namespace std;

class Robot10_2 : public BaseObjectClass {
public:
	//Special: Enraged
	int regeneration1;
	int regeneration2;
	int regeneration3;
	void Regeneration() override;
	Robot10_2(int line, bool isLeft);
	~Robot10_2();
};