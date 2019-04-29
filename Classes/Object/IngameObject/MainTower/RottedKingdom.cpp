#include "RottedKingdom.h"


RottedKingdom::RottedKingdom(bool isLeft, int id) {
	// thông số cơ bản
	objectName = "RottedKingdom";
	description = "Main tower";
	maxHealth = 1000;
	currentHealth = 999;
	attack = 100;
	defense = 50;
	attackRate = 1;
	range = 800;
	regeneration = 1;

	string upgradeTo = "RottedKingdom_2";
	int upgradeGold = 200;
	int upgradeEnergy = 3;
	int upgradeLevelRequired = 1;

	// thông tin trong game
	this->id = id;
	animateName = "Robot2";
	this->line = 2;
	this->isLeft = isLeft;
	this->UpdateIngameInfo("Sprites/mainTower1/default.png", true);
	this->sprite->setColor(IngameObject::elementColor["Poison"]);
}

//MainTower can attack all line
vector<BaseObjectClass*> RottedKingdom::FindTargets(vector<BaseObjectClass*>& targets) {
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

	//Sắp xếp theo máu tăng dần
	sort(shotableTargets.begin(), shotableTargets.end(), BaseObjectClass::SortByHealth);

	//Lấy 1 thằng máu thấp nhất
	if (shotableTargets.size() > 0) result.push_back(shotableTargets[0]);
	return result;
}

RottedKingdom::~RottedKingdom()
{
}

void RottedKingdom::Regeneration()
{
	//Rotted Aura: Whoever entered this tower range will be rotted, decrease 8% Health per second.
	vector<BaseObjectClass*> targets;
	if (this->isLeft) targets = BaseObjectClass::player2_Object;
	else targets = BaseObjectClass::player1_Object;
	for (auto target : targets) {
		if (target->currentHealth > 0 && target->action != "Die") {
			if (abs(target->root->getPositionX() - this->root->getPositionX()) < this->range) {
				float healthLose = target->maxHealth*0.08;
				//string animateName = this->animateName + "_explosion";
				string animateName = "_explosion"; // Không có sprite nên ai bắn cũng nổ như nhau
				target->damageReceive.push_back(DamageReceive(healthLose, Tool::currentIngameTime, animateName, this->id));
			}
		}
	}
	
	BaseObjectClass::Regeneration();
}
