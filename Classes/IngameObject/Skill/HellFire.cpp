#include "HellFire.h"

HellFire::HellFire(int playerId)
{
	this->playerId = playerId;
	this->name = "Hell Fire";
	this->description = "burn down all enemies with hell fire, dealt damage proportional to your army's Attack each second.";
	this->nextTriggerTime = Tool::currentIngameTime + 0.96;
	this->expiredTime = Tool::currentIngameTime + 4;
	this->isAddedChild = true;
	BaseSkillClass::AllIngameSkill_Vector.push_back(this);
	IngameObject::animate["Hell Fire_fire"]->setDuration(2.3);
	//Animation
	for (int i = 0; i < 20; i++) {
		auto sp1 = Sprite::create("Sprites/Hell Fire/fire/fire (1).png");
		BaseUnitClass::AllIngameUnit_Vector[0]->root->addChild(sp1);
		sp1->setPosition(Vec2(-i * 150, 50));
		sp1->runAction(Sequence::create(IngameObject::animate["Hell Fire_fire"]->clone(), DelayTime::create(1), IngameObject::animate["Hell Fire_fire"]->clone(), RemoveSelf::create(), nullptr));

		auto sp2 = Sprite::create("Sprites/Hell Fire/fire/fire (1).png");
		BaseUnitClass::AllIngameUnit_Vector[0]->root->addChild(sp2);
		sp2->setPosition(Vec2(-i * 150, 200));
		sp2->runAction(Sequence::create(IngameObject::animate["Hell Fire_fire"]->clone(), DelayTime::create(1), IngameObject::animate["Hell Fire_fire"]->clone(), RemoveSelf::create(), nullptr));

		auto sp3 = Sprite::create("Sprites/Hell Fire/fire/fire (1).png");
		BaseUnitClass::AllIngameUnit_Vector[0]->root->addChild(sp3);
		sp3->setPosition(Vec2(-i * 150, 350));
		sp3->runAction(Sequence::create(IngameObject::animate["Hell Fire_fire"]->clone(), DelayTime::create(1), IngameObject::animate["Hell Fire_fire"]->clone(), RemoveSelf::create(), nullptr));
	}
}
HellFire::~HellFire()
{
}

void HellFire::Update()
{
	if (this->expiredTime < Tool::currentIngameTime) {
		this->isReleased = true;
		return;
	}
	if (this->nextTriggerTime < Tool::currentIngameTime) {
		this->nextTriggerTime = Tool::currentIngameTime + 0.96;
		int count = 0;
		this->damage = 0;
		for (auto ally : BaseUnitClass::AllIngameUnit_Vector) {
			if (this->playerId == ally->ownerPlayerId) {
				damage += (ally->attack*1.1);
				count++;
			}
		}
		this->damage /= count;
		for (auto enemy : BaseUnitClass::AllIngameUnit_Vector) {
			if (this->playerId != enemy->ownerPlayerId
				&& enemy->description != "Kingdom") {
				enemy->damageReceive.push_back(DamageReceive(0, this->damage, Tool::currentIngameTime, "", ""));
			}
		}
	}
}
