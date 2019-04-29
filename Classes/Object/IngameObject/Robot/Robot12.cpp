#include "Robot12.h"


Robot12::Robot12(int line, bool isLeft, int id) {
	// thông số cơ bản
	objectName = "Robot12";
	levelRequired = 3;
	description = "Multi-target helicopter";
	cost = 125;
	maxHealth = 500;
	currentHealth = maxHealth;
	attack = 150;
	defense = 50;
	speed = 8;
	attackRate = 2.0;
	range = 700;
	regeneration = 0;
	special = "Keen Eyes: Attack upto 2 targets, can attack all lines";

	upgradeTo = "";
	upgradeGold = 0;
	upgradeEnergy = 0;
	upgradeLevelRequired = 1;

	// thông tin trong game
	this->id = id;
	animateName = "Robot12";
	this->line = line;
	this->isLeft = isLeft;
	this->UpdateIngameInfo("Sprites/robot12/run/run (1).png", false);




}

// Special: Attack 2 targets, can attack all line.
vector<BaseObjectClass*> Robot12::FindTargets(vector<BaseObjectClass*>& targets) {
	vector<BaseObjectClass*> result;
	vector<BaseObjectClass*> shotableTargets;

	//Tìm danh sách địch có thể bắn tới
	for (auto target : targets) {
		//Xem target còn sống không
		if (target->currentHealth > 0) {
			if (abs(target->root->getPositionX() - this->root->getPositionX()) < this->range) {
				shotableTargets.push_back(target);
			}
		}
	}
	//Sắp xếp theo máu tăng dần
	sort(shotableTargets.begin(), shotableTargets.end(), BaseObjectClass::SortByHealth);

	//Lấy thằng máu thấp nhất
	if (shotableTargets.size() > 0) result.push_back(shotableTargets[0]);
	if (shotableTargets.size() > 1) result.push_back(shotableTargets[1]);
	return result;

}



Robot12::~Robot12()
{
}
