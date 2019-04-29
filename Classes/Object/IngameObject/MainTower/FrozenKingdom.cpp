#include "FrozenKingdom.h"


FrozenKingdom::FrozenKingdom(bool isLeft, int id) {
	// thông số cơ bản
	objectName = "FrozenKingdom";
	description = "Main tower";
	maxHealth = 1000;
	currentHealth = 999;
	attack = 100;
	defense = 50;
	attackRate = 1;
	range = 800;
	regeneration = 1;

	string upgradeTo = "FrozenKingdom_2";
	int upgradeGold = 200;
	int upgradeEnergy = 3;
	int upgradeLevelRequired = 1;

	// thông tin trong game
	this->id = id;
	animateName = "Robot2";
	this->line = 2;
	this->isLeft = isLeft;
	this->UpdateIngameInfo("Sprites/mainTower1/default.png", true);
	this->sprite->setColor(IngameObject::elementColor["Ice"]);
}

//MainTower can attack all line
vector<BaseObjectClass*> FrozenKingdom::FindTargets(vector<BaseObjectClass*>& targets) {
	vector<BaseObjectClass*> result;
	vector<BaseObjectClass*> shotableTargets;

	//Tìm danh sách địch có thể bắn tới
	for (auto target : targets) {
		if (target->currentHealth > 0 && target->action != "Die") {
			if (abs(target->root->getPositionX() - this->root->getPositionX()) < this->range) {
				shotableTargets.push_back(target);
			}
		}
	}

	//Frozen Aura: Whoever entered this tower range will be cold, decrease Attack Rate by 25%
	for (auto target : shotableTargets) {
		bool isAffected = false;
		for (auto status : target->statusReceive) {
			if (status.statusName == "FrozenAura") {
				status.endTime = Tool::currentIngameTime + 10;
				isAffected = true;
				break;
			}
		}
		if (!isAffected) {
			target->attackRate /= 0.75;
			target->statusReceive.push_back(StatusReceive(this->id, "FrozenAura", Tool::currentIngameTime + 10));
		}
	}

	//Sắp xếp theo máu tăng dần
	sort(shotableTargets.begin(), shotableTargets.end(), BaseObjectClass::SortByHealth);

	//Lấy 1 thằng máu thấp nhất
	if (shotableTargets.size() > 0) result.push_back(shotableTargets[0]);
	return result;
}

FrozenKingdom::~FrozenKingdom()
{
}
