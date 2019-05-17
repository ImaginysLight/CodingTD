#pragma once
#include "cocos2d.h"
#include"..\..\Global Class\Tool.h"
#include"BaseUnitClass.h"
#include"../Skill/FrostNova.h"

USING_NS_CC;
using namespace std;

class FrostWyvern : public BaseUnitClass {
public:
	FrostWyvern(int line, bool isOwned, int unitId, int playerId);
	~FrostWyvern();
	//Frost Nova: Launch a snowball toward enemy, dealing 60 / 75 / 100 splash damage in 100 range,
	//pierce 25 / 35 / 50 Defense (Cooldown 7 / 6 / 4 seconds)
	//Thực hiện skill này chung với Attack nếu nó ready
	//Làm cooldown = cách Tool::currentIngameTime + 7 khi trigger
	float snowballReady = Tool::currentIngameTime;
	void Attack(vector<BaseUnitClass*> &targets) override;

	////The Presence of Ice: Slow all enemies on the line, decrease Move Speed by 10 / 15 / 20 and Attack Speed by 10 / 17 / 25%
	//Kiểm tra skill này mỗi giây qua hàm Regeneration, xem đối thủ trên line nếu chưa có status thì add
	void Regeneration() override;
};