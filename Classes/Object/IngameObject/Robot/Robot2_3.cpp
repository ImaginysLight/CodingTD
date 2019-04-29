#include "Robot2_3.h"

Robot2_3::Robot2_3(int line, bool isLeft, int id) {
	// thông số cơ bản
	objectName = "Robot2_3";
	description = "Long-range unit";
	cost = 75;
	maxHealth = 500;
	currentHealth = maxHealth;
	attack = 60;
	defense = 50;
	speed = 8;
	attackRate = 0.7;
	range = 800;
	regeneration = 0;
	special = "Lucky Shot: The 3th shot will deal x2 damage";

	upgradeTo = "";
	upgradeGold = 0;
	upgradeEnergy = 0;
	upgradeLevelRequired = 0;

	// thông tin trong game
	this->id = id;
	animateName = "Robot2";
	this->line = line;
	this->isLeft = isLeft;
	this->UpdateIngameInfo("Sprites/robot2/run/run (1).png", false);




}

Robot2_3::~Robot2_3()
{
}

//Special: Lucky Shot: The 5 / 4 / 3th shot will deal x1.5 / 1.75 / 2 damage
void Robot2_3::Attack(BaseObjectClass *& target)
{
	this->numOfShot++;
	if (this->numOfShot == 3) {
		this->numOfShot = 0;
		auto oldAttack = this->attack;
		this->attack *= 2;
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

