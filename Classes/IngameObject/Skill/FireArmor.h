#pragma once
#include"BaseSkillClass.h"
#include "cocos2d.h"


USING_NS_CC;
using namespace std;

//Fire Armor: buff an ally with Fire Armor, reflect 15 / 20% damage to whoever attacks them. (Duration: 10s, Cooldown: 10s)

class FireArmor : public BaseSkillClass {
public:
	FireArmor(int targetId, int reflectPercent, float expiredTime);
	~FireArmor();

	int targetId = 0;
	int reflectPercent = 0;
	vector<DamageReceive> damageReflected;
	void AddNewDamageReflect(DamageReceive dmg);
	void Update() override;
};