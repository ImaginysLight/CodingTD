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
	
		

	//The Presence of Fire : burn all enemies on the line, dealing 5 / 7 pure dps and decrease Regeneration by 30 / 35 % .
	void Regeneration() override;

	//Fire Armor : buff an ally with Fire Armor, increase Defense by 25 / 30 and reflect 25 / 30 % damage to whoever attacks them. (Duration : 9s, Cooldown : 10s)
	float fireArmorReady = Tool::currentIngameTime;
	
};