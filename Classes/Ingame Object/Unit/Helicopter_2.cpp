#include "Helicopter_2.h"

Helicopter_2::Helicopter_2(int line, bool isOwned, int unitId, int playerId)
{
	name = "Helicopter 2";
	description = "A multi-target Helicopter, slow but can attack every line.";
	goldCost = 125;
	levelRequired = 2;
	maxHealth = 300;
	currentHealth = maxHealth;
	baseAttack = 100;
	baseDefense = 50;
	baseMoveSpeed = 45;
	baseAttackSpeed = 20;
	range = 625;
	baseRegeneration = 1;

	animationIndexOnTriggerAttack = 5;

	this->UpdateIngameInfo("Sprites/Helicopter/attack/attack (1).png", unitId, playerId, isOwned, "Helicopter", line);
}

Helicopter_2::~Helicopter_2()
{
}

//	//Keen Eyes: attack upto 2 targets in all lines.
vector<BaseUnitClass*> Helicopter_2::FindTargets()
{

	vector<BaseUnitClass*> result;
	vector<BaseUnitClass*> shotableTargets;
	//Tìm danh sách địch có thể bắn tới
	for (auto target : BaseUnitClass::AllIngameUnit_Vector) {
		if (
			this->isOwned != target->isOwned							// Xem có phải đối thủ không
			&& target->isAlive && target->action != "Die"				//Xem target còn sống không
			) {
			auto frontDistance = (this->isOwned ? 1 : -1)*(target->root->getPositionX() - this->root->getPositionX());
			if (frontDistance < this->range && frontDistance > -50)
				shotableTargets.push_back(target);
		}
	}
	//Sắp xếp theo máu tăng dần
	std::sort(shotableTargets.begin(), shotableTargets.end(), BaseUnitClass::SortByHealth);

	//Lấy 3 thằng máu thấp nhất
	if (shotableTargets.size() > 0) result.push_back(shotableTargets[0]);
	if (shotableTargets.size() > 1) result.push_back(shotableTargets[1]);
	if (shotableTargets.size() > 2) result.push_back(shotableTargets[2]);
	return result;
}

