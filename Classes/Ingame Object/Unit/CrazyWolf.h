#pragma once
#include "cocos2d.h"
#include"..\..\Global Class\Tool.h"
#include"BaseUnitClass.h"

USING_NS_CC;
using namespace std;

class CrazyWolf : public BaseUnitClass {
public:
	CrazyWolf(int line, bool isOwned, int unitId, int playerId);
	~CrazyWolf();
	//Berserker's Blood: double amount of Regeneration when Health below 25 / 35 / 50%.
	//Tripple amount of Regeneration when Health below 0 / 10 / 25%
	void Regeneration() override;
	
};