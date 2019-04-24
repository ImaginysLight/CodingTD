#include "Robot5.h"

Robot5::Robot5(int line, bool isLeft) {
	// thông số cơ bản
	objectName = "Robot5";
	description = "Normal and cheapest unit";
	cost = 50;
	maxHealth = 300;
	currentHealth = maxHealth;
	attack = 20;
	defense = 50;
	speed = 10;
	attackRate = 1.0;
	range = 450;
	regeneration = 0;
	special = "";

	upgradeTo = "Robot5_2";
	upgradeGold = 200;
	upgradeEnergy = 1;
	upgradeLevelRequired = 1;

	// thông tin trong game
	animateName = "Robot5";
	this->line = line;
	this->isLeft = isLeft;
	this->UpdateIngameInfo("Sprites/robot5/run/run (1).png", false);
	


	
}

Robot5::~Robot5()
{
}
