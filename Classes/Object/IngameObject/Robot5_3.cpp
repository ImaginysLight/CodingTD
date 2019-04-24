#include "Robot5_3.h"

Robot5_3::Robot5_3(int line, bool isLeft) {
	// thông số cơ bản
	objectName = "Robot5_3";
	description = "Normal and cheapest unit, but level 3 :V";
	cost = 50;
	maxHealth = 700;
	currentHealth = maxHealth;
	attack = 30;
	defense = 75;
	speed = 10;
	attackRate = 0.75;
	range = 500;
	regeneration = 0;
	special = "";

	upgradeTo = "";
	upgradeGold = 0;
	upgradeEnergy = 0;
	upgradeLevelRequired = 0;

	// thông tin trong game
	animateName = "Robot5";
	this->line = line;
	this->isLeft = isLeft;
	this->UpdateIngameInfo("Sprites/robot5/run/run (1).png", false);




}

Robot5_3::~Robot5_3()
{
}
