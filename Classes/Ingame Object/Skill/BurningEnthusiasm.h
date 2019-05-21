#pragma once
#include"BaseSkillClass.h"
#include "cocos2d.h"
#include"..\..\Global Class\Tool.h"

USING_NS_CC;
using namespace std;

//Description: give an ally a power of Fire, double their Attack but receive pure damage equal to 10 % of bonus Attack (from every source) each second.
//Duration : 10
//Energy cost : 15



class BurningEnthusiasm : public BaseSkillClass {
public:
	BurningEnthusiasm(int targetId);
	~BurningEnthusiasm();
	int targetId = 0;
	void Update() override;
};