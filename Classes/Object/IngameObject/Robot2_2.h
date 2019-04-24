#pragma once
#include "cocos2d.h"
#include"..\Tool.h"
#include"BaseObjectClass.h"
USING_NS_CC;
using namespace std;

class Robot2_2 : public BaseObjectClass {
public:
	Robot2_2(int line, bool isLeft);
	~Robot2_2();
	//Special: Lucky Shot: The 5 / 4 / 3th shot will deal x1.5 damage
	int numOfShot = 0;
	void Attack(BaseObjectClass *& target) override;
};