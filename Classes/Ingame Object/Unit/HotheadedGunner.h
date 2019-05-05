#pragma once
#include "cocos2d.h"
#include"..\..\Global Class\Tool.h"
#include"BaseUnitClass.h"

USING_NS_CC;
using namespace std;

class HotheadedGunner : public BaseUnitClass {
public:
	HotheadedGunner(int line, bool isOwned, int unitId, int playerId);
	~HotheadedGunner();

	
	
};