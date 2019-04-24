#pragma once
#include "cocos2d.h"
#include"..\Tool.h"
#include"BaseObjectClass.h"
USING_NS_CC;
using namespace std;

class Robot10 : public BaseObjectClass {
public:
	//Special: Enraged: double amount of recover when health below 50%
	int regeneration1;
	int regeneration2;
	void Regeneration() override;
	Robot10(int line, bool isLeft);
	~Robot10();
};