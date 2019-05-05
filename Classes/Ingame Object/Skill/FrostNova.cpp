#include "FrostNova.h"


FrostNova::FrostNova(Vec2 position, int line, float damage, float triggerTime, bool isOwned)
{
	this->root = Node::create();
	this->root->setPosition(position);
	this->lineOfEffect = line;
	this->damage = damage;
	this->nextTriggerTime = triggerTime;
	this->areaOfEffect = 100;
	this->isOwned = isOwned;
	BaseSkillClass::AllIngameSkill_Vector.push_back(this);
}

FrostNova::~FrostNova()
{
}
//Frost Nova : Launch a snowball toward enemy, dealing 75 / 100 / 150 splash damage in 100 range,
//pierce 25 Defense(Cooldown 7 / 6 / 4 seconds)
void FrostNova::Update()
{
	if (this->isReleased) { delete this; return; }
	if (this->nextTriggerTime < Tool::currentIngameTime) this->onTrigger();
}

void FrostNova::onTrigger()
{
	//Label cho đẹp
	auto label = Tool::CreateLabel("Frost Nova !!");
	this->root->addChild(label);
	label->runAction(MoveBy::create(1, Vec2(0, 40)));

	for (auto target : BaseUnitClass::AllIngameUnit_Vector) {
		if (
			(this->isOwned != target->isOwned)				// Xem có phải đối thủ không
			&& (target->isAlive && target->action != "Die")	//Xem target còn sống không
			&& (this->lineOfEffect == target->line)			//Xem có cùng hàng không
			&& (abs(target->root->getPositionX() - this->root->getPositionX()) < this->areaOfEffect) // Xem có trong range không
			) {
			target->damageReceive.push_back(DamageReceive(0, this->damage, Tool::currentIngameTime, "","Frost Nova"));
		}
	}
	this->nextTriggerTime += 6969;
	this->root->runAction(Sequence::create(
		DelayTime::create(1.5),
		RemoveSelf::create(),
		CallFunc::create([&]() {	this->isReleased = true; }),
		nullptr
	));
	
}

