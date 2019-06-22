#pragma once
#include "cocos2d.h"
#include"BaseUnitClass.h"

USING_NS_CC;
using namespace std;

class CrazyWolf_2 : public BaseUnitClass {
public:
	CrazyWolf_2(int line, bool isOwned, int unitId, int playerId);
	~CrazyWolf_2();
	/*Berserker's Blood:
	Double amount of Regeneration when Health below 35 / 55 / 75 % .
	Tripple amount of Regeneration when Health below 0 / 20 / 50 % .
	Quadruplicate amount of Regeneration when Health below 0 / 10 / 25 % .*/
	void Regeneration() override;
	
};