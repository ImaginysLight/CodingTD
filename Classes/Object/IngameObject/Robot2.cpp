#include "Robot2.h"

Robot2::Robot2(int line, bool isLeft) {
	// thông số cơ bản
	objectName = "Robot2";
	description = "Long-range unit";
	cost = 75;
	maxHealth = 300;
	currentHealth = maxHealth;
	attack = 30;
	defense = 20;
	speed = 8;
	attackRate = 0.9;
	range = 700;
	regeneration = 0;
	special = "Lucky Shot: The 5th shot will deal x1.5 damage";

	upgradeTo = "Robot2_2";
	upgradeGold = 350;
	upgradeEnergy = 2;
	upgradeLevelRequired = 2;

	// thông tin trong game
	animateName = "Robot2";
	this->line = line;
	this->isLeft = isLeft;
	this->UpdateIngameInfo("Sprites/robot2/run/run (1).png", false);




}

Robot2::~Robot2()
{
}

//Special: Lucky Shot: The 5 / 4 / 3th shot will deal x1.5 / 1.75 / 2 damage
void Robot2::Attack(BaseObjectClass *& target)
{
	this->numOfShot++;
	if (this->numOfShot == 5) {
		this->numOfShot = 0;
		auto oldAttack = this->attack;
		this->attack *= 1.5;
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

