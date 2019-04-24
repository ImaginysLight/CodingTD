#include "Robot2_2.h"

Robot2_2::Robot2_2(int line, bool isLeft) {
	// thông số cơ bản
	objectName = "Robot2_2";
	description = "Long-range unit";
	cost = 75;
	maxHealth = 400;
	currentHealth = maxHealth;
	attack = 45;
	defense = 35;
	speed = 8;
	attackRate = 0.8;
	range = 750;
	regeneration = 0;
	special = "Lucky Shot: The 4th shot will deal x1.75 damage";

	upgradeTo = "Robot2_3";
	upgradeGold = 650;
	upgradeEnergy = 3;
	upgradeLevelRequired = 3;

	// thông tin trong game
	animateName = "Robot2";
	this->line = line;
	this->isLeft = isLeft;
	this->UpdateIngameInfo("Sprites/robot2/run/run (1).png", false);




}

Robot2_2::~Robot2_2()
{
}

//Special: Lucky Shot: The 5 / 4 / 3th shot will deal x1.5 / 1.75 / 2 damage
void Robot2_2::Attack(BaseObjectClass *& target)
{
	this->numOfShot++;
	if (this->numOfShot == 4) {
		this->numOfShot = 0;
		auto oldAttack = this->attack;
		this->attack *= 1.75;
		BaseObjectClass::Attack(target);
		this->attack = oldAttack;
		Label* lbl_LuckyShot = Tool::CreateLabel("Lucky!", Tool::defaultTextSize, Color4B::YELLOW);
		this->root->addChild(lbl_LuckyShot);
		if (this->isLeft) lbl_LuckyShot->setRotation3D(Vec3(0, 180, 0));
		lbl_LuckyShot->setPosition(Vec2(0, 30));
		lbl_LuckyShot->runAction(Sequence::create(FadeOut::create(1), RemoveSelf::create(), nullptr));
	}
	else BaseObjectClass::Attack(target);
	
}

