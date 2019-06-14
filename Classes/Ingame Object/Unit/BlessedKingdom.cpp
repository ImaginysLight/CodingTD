#include "BlessedKingdom.h"

BlessedKingdom::BlessedKingdom(int line, bool isOwned, int unitId, int playerId)
{
	name = "Blessed Kingdom";
	description = "Kingdom";
	maxHealth = 2000;
	currentHealth = maxHealth;
	baseAttack = 30;
	baseDefense = 50;
	baseAttackSpeed = 60;
	range = 600;
	baseRegeneration = 2;

	upgradeName = "Blessed Kingdom 2";
	upgradeGoldCost = 200;
	upgradeKnowledgeCost = 3;
	upgradeLevelRequired = 0;

	this->UpdateIngameInfo("Sprites/Blessed Kingdom/default_315x300.png", unitId, playerId, isOwned, "Blessed Kingdom", line);
	if (this->isOwned) this->root->setPosition(Vec2(-50, 50));
	else this->root->setPosition(Vec2(3050,50));
}

BlessedKingdom::~BlessedKingdom()
{
}

void BlessedKingdom::Die()
{
	this->StotpAction("All");
	this->isAlive = false;
	this->root->runAction(RemoveSelf::create());
	this->action = "Idle";
}


void BlessedKingdom::Update()
{
	for (auto unit : BaseUnitClass::AllIngameUnit_Vector) {
		if (unit->isOwned == this->isOwned && unit->isAlive && unit->action != "Die") {
			if (unit->root->getPositionX() < -100)
				unit->root->runAction(MoveTo::create(0.2, Vec2(0, unit->root->getPositionY())));
			if (unit->root->getPositionX() > 3100)
				unit->root->runAction(MoveTo::create(0.2, Vec2(3000, unit->root->getPositionY())));
		}
	}

	//Nếu chết rồi thì hủy đối tượng
	if (!this->isAlive) {
		//Xử lý victory...
		delete this;
		return;
	}

	//Kiểm tra trigger damage
	for (int i = 0; i < damageReceive.size(); i++) {
		if (damageReceive[i].triggerTime <= Tool::currentIngameTime) {
			this->onDamageReceive(damageReceive[i]);
			damageReceive.erase(damageReceive.begin() + i);
		}
	}

	//Kiểm tra release status
	for (int i = 0; i < statusReceive.size(); i++) {
		if (statusReceive[i].releaseStatusTime <= Tool::currentIngameTime) {
			string influence = statusReceive[i].statusInfluence;
			statusReceive.erase(statusReceive.begin() + i);
			this->ReprocessAllStatus(influence);
		}
	}

	//Regeneration
	if (this->nextRegenerationTriggerTime < Tool::currentIngameTime) {
		this->Regeneration();
		this->nextRegenerationTriggerTime++;
	}
	
	//Action Die
	if (this->currentHealth < 1 && this->action != "Die") {
		this->Die();
		return;
	}

	//Action Attack
	if (this->action == "Idle") {
		vector<BaseUnitClass*> targetList = this->FindTargets();
		if (targetList.size() > 0) {
			this->Attack(targetList);
			return;
		}

	}

}

void BlessedKingdom::Attack(vector<BaseUnitClass*>& targets)
{
	this->action = "Attack";
	this->sprite->runAction(Sequence::create(
		DelayTime::create(60.0 / this->attackSpeed),
		CallFunc::create([&]() {	this->action = "Idle"; }),
		nullptr
	))->setFlags(1);
	for (auto target : targets) {
		float damage = this->attack;
		//string animateName = this->animateName + "_explosion";
		string animateName = "_explosion"; // Không có sprite nên ai bắn cũng nổ như nhau
		float distance = abs(this->root->getPositionX() - target->root->getPositionX());
		float triggerTime = Tool::currentIngameTime + distance * 0.002;
		target->damageReceive.push_back(DamageReceive(this->unitId, damage, triggerTime, animateName, ""));
	}
}

//Special: Blessing Aura: All allies within this tower range will be blessed, restoring 2 / 2.75 / 3.5% hps.
vector<BaseUnitClass*> BlessedKingdom::FindTargets()
{
	vector<BaseUnitClass*> result;
	vector<BaseUnitClass*> shotableTargets;
	//Tìm danh sách địch có thể bắn tới
	for (auto target : BaseUnitClass::AllIngameUnit_Vector) {
		if (this->isOwned != target->isOwned
			&& (target->isAlive && target->action != "Die")
			&& (abs(target->root->getPositionX() - this->root->getPositionX()) < this->range)
			)
			shotableTargets.push_back(target);


		if (this->isOwned == target->isOwned
			&& target->description != "Kingdom"
			&& (target->isAlive && target->action != "Die")
			&& abs(target->root->getPositionX() - this->root->getPositionX()) < this->range) {
			bool isAffected = false;
			for (int i = 0; i < target->statusReceive.size(); i++) {
				if (target->statusReceive[i].statusName == "Blessing Aura") {
					target->statusReceive[i].releaseStatusTime = Tool::currentIngameTime + 2;
					isAffected = true;
					break;
				}
			}
			float healMultiply = 2.0;
			if (level == 2)healMultiply = 2.75;
			if (level == 3)healMultiply = 3.5;
			if (!isAffected)
				target->ApplyStatus(StatusReceive("Blessing Aura", "Regeneration", healMultiply*target->maxHealth / 100.0, Tool::currentIngameTime + 2, 1));
		}
	}
	//Sắp xếp theo máu tăng dần
	std::sort(shotableTargets.begin(), shotableTargets.end(), BaseUnitClass::SortByHealth);

	//Lấy 1 thằng máu thấp nhất
	if (shotableTargets.size() > 0) result.push_back(shotableTargets[0]);
	return result;
}

void BlessedKingdom::Upgrade()
{
	level++;
	if (level == 2) {
		float currentHealthPercent = (float)currentHealth / maxHealth;
		name = "Blessed Kingdom 2";
		description = "Kingdom";
		maxHealth = 2000;
		currentHealth = maxHealth*currentHealthPercent;
		baseAttack = 40;
		baseDefense = 75;
		baseAttackSpeed = 60;
		range = 650;
		baseRegeneration = 4;

		upgradeName = "Blessed Kingdom 3";
		upgradeGoldCost = 500;
		upgradeKnowledgeCost = 5;
		this->root->setScale(1);
		this->ReprocessAllStatus("Attack");
		this->ReprocessAllStatus("Defense");
		this->ReprocessAllStatus("MoveSpeed");
		this->ReprocessAllStatus("AttackSpeed");
		this->ReprocessAllStatus("Regeneration");
	}
	else if (level == 3) {
		float currentHealthPercent = (float)currentHealth / maxHealth;
		name = "Blessed Kingdom 3";
		description = "Kingdom";
		maxHealth = 2000;
		currentHealth = maxHealth * currentHealthPercent;
		baseAttack = 50;
		baseDefense = 100;
		baseAttackSpeed = 60;
		range = 700;
		baseRegeneration = 8;

		upgradeName = "";
		this->root->setScale(1.1);
		this->ReprocessAllStatus("Attack");
		this->ReprocessAllStatus("Defense");
		this->ReprocessAllStatus("MoveSpeed");
		this->ReprocessAllStatus("AttackSpeed");
		this->ReprocessAllStatus("Regeneration");
	}
}



