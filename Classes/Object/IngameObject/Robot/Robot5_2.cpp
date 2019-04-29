#include "Robot5_2.h"

Robot5_2::Robot5_2(int line, bool isLeft, int id) {
	// thông số cơ bản
	objectName = "Robot5_2";
	description = "Normal and cheapest unit, but level 2 :V";
	cost = 50;
	maxHealth = 500;
	currentHealth = maxHealth;
	attack = 25;
	defense = 50;
	speed = 10;
	attackRate = 0.75;
	range = 500;
	regeneration = 0;
	special = "";

	upgradeTo = "Robot5_3";
	upgradeGold = 350;
	upgradeEnergy = 1;
	upgradeLevelRequired = 2;

	// thông tin trong game
	this->id = id;
	animateName = "Robot5";
	this->line = line;
	this->isLeft = isLeft;
	this->UpdateIngameInfo("Sprites/robot5/run/run (1).png", false);




}

Robot5_2::~Robot5_2()
{
}
