#include "LiquidAssassin_1.h"

LiquidAssassin_1::LiquidAssassin_1(int line, bool isOwned, int unitId, int playerId)
{
	name = "Liquid Assassin 1";
	description = "An assassin loves to knock out some squishy opponent.";
	goldCost = 175;
	levelRequired = 1;
	maxHealth = 650;
	currentHealth = maxHealth;
	baseAttack = 56;
	baseDefense = 20;
	baseMoveSpeed = 60;
	baseAttackSpeed = 30;
	range = 0;
	baseRegeneration = 2;

	upgradeName = "Liquid Assassin 2";
	upgradeGoldCost = 400;
	upgradeKnowledgeCost = 1;
	upgradeLevelRequired = 2;

	delayTimeAfterAttack = 0;
	animationIndexOnTriggerAttack = 9;
	
	this->UpdateIngameInfo("Sprites/Liquid Assassin/attack/attack (1).png", unitId, playerId, isOwned, "Liquid Assassin", line);
}

LiquidAssassin_1::~LiquidAssassin_1()
{
}

//Death Scratch : blink toward an enemy on any line and attack, dealt 100 / 175 / 250 bonus damage on attack.
//This ability has 1 charge and will be restored when an enemy dies within 550 / 650 / 750 range around Assassin, cooldown 5s
void LiquidAssassin_1::Update()
{
	if (this->cooldownTime < Tool::currentIngameTime && !this->isDeathStrikeReady) {
		for (auto unit : BaseUnitClass::AllIngameUnit_Vector) {
			if (
				unit->action == "Die"
				&& unit->isOwned != this->isOwned
				&& abs(unit->root->getPositionX() - this->root->getPositionX()) < 550
				) {
				this->isDeathStrikeReady = true;
				break;
			}
		}
	}

	BaseUnitClass::Update();
}

void LiquidAssassin_1::Attack(vector<BaseUnitClass*>& targets)
{
	if (this->isDeathStrikeReady) {
		float currentAttack = this->attack;
		if(targets[0]->description != "Kingdom") this->attack += 100;
		this->cooldownTime = Tool::currentIngameTime + 5;
		this->isDeathStrikeReady = false;
		this->root->runAction(MoveTo::create(0.5, targets[0]->root->getPosition()));
		this->line = targets[0]->line;

		this->action = "Attack";
		auto animate = IngameObject::animate[this->animateName + "_attack"]->clone();
		animate->setDuration(60 / this->attackSpeed * (1 - this->delayTimeAfterAttack));
		this->sprite->runAction(Sequence::create(
			animate,
			DelayTime::create(delayTimeAfterAttack),
			CallFunc::create([&]() {	this->action = "Idle"; }),
			nullptr
		))->setFlags(1);

		auto delayShootTime = 0.5;
		for (auto target : targets) {
			float damage = this->attack;
			//string animateName = this->animateName + "_explosion";
			string animateName = "_explosion"; // Không có sprite nên ai bắn cũng nổ như nhau
			float distance = abs(this->root->getPositionX() - target->root->getPositionX());
			float triggerTime = Tool::currentIngameTime + delayShootTime;
			target->damageReceive.push_back(DamageReceive(this->unitId, damage, triggerTime, animateName, ""));
		}
		this->attack = currentAttack;
		return;
	}
	BaseUnitClass::Attack(targets);
}

vector<BaseUnitClass*> LiquidAssassin_1::FindTargets()
{
	vector<BaseUnitClass*> result;
	if (this->isDeathStrikeReady) {
		vector<BaseUnitClass*> shotableTargets;
		for (auto target : BaseUnitClass::AllIngameUnit_Vector) {
			if (
				(this->isOwned != target->isOwned)									
				&& (target->isAlive && target->action != "Die")
				&& abs(target->root->getPositionX() - this->root->getPositionX()) < 550
				) {
					shotableTargets.push_back(target);
			}
		}
		//Sắp xếp theo máu tăng dần
		std::sort(shotableTargets.begin(), shotableTargets.end(), BaseUnitClass::SortByHealth);

		if (shotableTargets.size() > 0) result.push_back(shotableTargets[0]);
	}
	else result = BaseUnitClass::FindTargets();
	return result;
}


