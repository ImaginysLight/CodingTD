#include "FlamedKingdom.h"


FlamedKingdom::FlamedKingdom(bool isLeft, int id) {
	// thông số cơ bản
	objectName = "FlamedKingdom";
	description = "Main tower";
	maxHealth = 1000;
	currentHealth = 999;
	attack = 100;
	defense = 50;
	attackRate = 1;
	range = 800;
	regeneration = 1;

	string upgradeTo = "FlamedKingdom_2";
	int upgradeGold = 200;
	int upgradeEnergy = 3;
	int upgradeLevelRequired = 1;

	// thông tin trong game
	this->id = id;
	animateName = "Robot2";
	this->line = 2;
	this->isLeft = isLeft;
	this->UpdateIngameInfo("Sprites/mainTower1/default.png", true);
	this->sprite->setColor(IngameObject::elementColor["Fire"]);
}

//MainTower can attack all line
vector<BaseObjectClass*> FlamedKingdom::FindTargets(vector<BaseObjectClass*>& targets) {
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

FlamedKingdom::~FlamedKingdom()
{
}

void FlamedKingdom::ExcuteDamageReceive(DamageReceive dmg)
{
	//Flamed Aura: Whoever attacked this tower will be burned, receiving 25% of the attacking tower's damage.
	auto sourceObject = this->GetObjectById(dmg.sourceId);
	float healthLose = ((float)this->attack*0.25 / (0.5 + sourceObject->defense / 100.0)); // defense >= 0
	//string animateName = this->animateName + "_explosion";
	string animateName = "_explosion"; // Không có sprite nên ai bắn cũng nổ như nhau
	float triggerTime = Tool::currentIngameTime;
	sourceObject->damageReceive.push_back(DamageReceive(healthLose, triggerTime, animateName, this->id));

	BaseObjectClass::ExcuteDamageReceive(dmg);
}
