#pragma once
#include "cocos2d.h"
#include"..\..\Global Class\Tool.h"
#include"BaseUnitClass.h"
#include"..\Skill\FireArmor.h"

USING_NS_CC;
using namespace std;

class Volcarona : public BaseUnitClass {
public:
	Volcarona(int line, bool isOwned, int unitId, int playerId);
	~Volcarona();

	//The Presence of Fire: burn all non-Fire-Special unit on the line, dealing 2 dps and decrease Regeneration by 20%
	void Regeneration() override;

	//Fire Armor : buff an ally with Fire Armor, reflect 15 / 20 % damage to whoever attacks them. (Duration : 10s, Cooldown : 10s)
	float fireArmorReady = Tool::currentIngameTime;
	
};