#pragma once
#include "cocos2d.h"
#include"..\..\Tool.h"
#include"..\BaseObjectClass.h"
USING_NS_CC;
using namespace std;

class Robot7 : public BaseObjectClass {
public:
	Robot7(int line, bool isLeft, int id);
	~Robot7();
};