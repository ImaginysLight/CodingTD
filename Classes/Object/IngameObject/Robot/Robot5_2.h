#pragma once
#include "cocos2d.h"
#include"..\..\Tool.h"
#include"..\BaseObjectClass.h"
USING_NS_CC;
using namespace std;

class Robot5_2 : public BaseObjectClass {
public:
	Robot5_2(int line, bool isLeft, int id);
	~Robot5_2();
};